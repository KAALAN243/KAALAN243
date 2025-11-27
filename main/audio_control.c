#include "audio_control.h"
#include "driver/i2s.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_a2dp_api.h"

static const char *TAG = "AUDIO";

void audio_init(void) {
    i2s_config_t cfg = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 4,
        .dma_buf_len = 512,
        .use_apll = false
    };
    i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
    i2s_set_dac_mode(I2S_DAC_CHANNEL_LEFT_EN);
    ESP_LOGI(TAG, "I2S -> DAC1 initialized");
}

void bt_init(void) {
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    esp_bluedroid_init(); esp_bluedroid_enable();
    esp_bt_dev_set_device_name("On_DAc");
    esp_a2d_register_callback(NULL);
    esp_a2d_sink_register_data_callback(NULL);
    esp_a2d_sink_init();
}