#pragma once
#include "driver/spi_master.h"
#include <stdint.h>
#include "logo.h"

#define PIN_MOSI 23
#define PIN_CLK 18
#define PIN_CS 5
#define PIN_DC 16
#define PIN_RST 17
#define PIN_BL 4
#define SPI_HOST_USED HSPI_HOST

spi_device_handle_t display_init(void);
void draw_frame(spi_device_handle_t spi, const uint16_t *pixels);