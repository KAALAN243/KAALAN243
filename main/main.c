// main.c - On_DAc Firmware (ESP-IDF)
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "display_driver.h"
#include "logo_animation.h"
#include "audio_control.h"
#include "buttons.h"

static const char *TAG = "ON_DAc_FW";

void app_main(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    spi_device_handle_t spi = display_init();
    play_boot_animation(spi);

    audio_init();   // sets up I2S->DAC
    bt_init();      // basic A2DP sink init (stubs in audio_control.c)
    buttons_init();

    ESP_LOGI(TAG, "On_DAc ready");
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}