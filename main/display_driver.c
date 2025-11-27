#include "display_driver.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

static const char *TAG = "DISPLAY";
static spi_device_handle_t spi = NULL;

spi_device_handle_t display_init(void) {
    if (spi) return spi;
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = PIN_MOSI,
        .sclk_io_num = PIN_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LOGO_W * LOGO_H * 2
    };
    spi_bus_initialize(SPI_HOST_USED, &buscfg, SPI_DMA_CH_AUTO);

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 20*1000*1000,
        .mode = 0,
        .spics_io_num = PIN_CS,
        .queue_size = 7,
        .command_bits = 8,
        .address_bits = 0,
        .flags = SPI_DEVICE_HALFDUPLEX
    };
    spi_bus_add_device(SPI_HOST_USED, &devcfg, &spi);

    gpio_set_direction(PIN_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_BL, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_BL, 1);

    gpio_set_level(PIN_RST, 0); vTaskDelay(pdMS_TO_TICKS(50));
    gpio_set_level(PIN_RST, 1); vTaskDelay(pdMS_TO_TICKS(120));

    ESP_LOGI(TAG, "Display initialized");
    return spi;
}

void draw_frame(spi_device_handle_t spi, const uint16_t *pixels) {
    int total = LOGO_W * LOGO_H;
    const uint16_t *p = pixels;
    const int CHUNK = 256;
    uint8_t tx[CHUNK*2];
    while (total > 0) {
        int send = total > CHUNK ? CHUNK : total;
        for (int i = 0; i < send; ++i) {
            uint16_t v = *p++;
            tx[i*2] = v >> 8; tx[i*2+1] = v & 0xFF;
        }
        spi_transaction_t t = {0};
        t.length = send * 2 * 8;
        t.tx_buffer = tx;
        spi_device_transmit(spi, &t);
        total -= send;
    }
}