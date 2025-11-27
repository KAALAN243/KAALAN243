#pragma once
#include "driver/gpio.h"
#define BTN_PLAY GPIO_NUM_13
#define BTN_NEXT GPIO_NUM_12
#define BTN_PREV GPIO_NUM_14
#define BTN_VOLUP GPIO_NUM_27
#define BTN_VOLDN GPIO_NUM_26
void buttons_init(void);