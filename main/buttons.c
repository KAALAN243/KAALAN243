#include "buttons.h"
#include "driver/gpio.h"

void buttons_init(void) {
    gpio_config_t io = {
        .intr_type = GPIO_INTR_NEGEDGE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL<<BTN_PLAY)|(1ULL<<BTN_NEXT)|(1ULL<<BTN_PREV)|(1ULL<<BTN_VOLUP)|(1ULL<<BTN_VOLDN),
        .pull_down_en = 0,
        .pull_up_en = 1
    };
    gpio_config(&io);
}