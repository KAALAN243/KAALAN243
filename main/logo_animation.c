#include "logo_animation.h"
#include "display_driver.h"
#include <stdlib.h>

void play_boot_animation(spi_device_handle_t spi) {
    extern const unsigned short logo_pixels[];
    for (int step = 0; step <= 16; ++step) {
        float a = (float)step / 16.0f;
        uint16_t *frame = malloc(LOGO_W * LOGO_H * sizeof(uint16_t));
        if (!frame) return;
        for (int i = 0; i < LOGO_W * LOGO_H; ++i) {
            uint16_t pix = logo_pixels[i];
            uint8_t r5 = (pix >> 11) & 0x1F;
            uint8_t g6 = (pix >> 5) & 0x3F;
            uint8_t b5 = pix & 0x1F;
            uint8_t r8 = (r5 << 3) | (r5 >> 2);
            uint8_t g8 = (g6 << 2) | (g6 >> 4);
            uint8_t b8 = (b5 << 3) | (b5 >> 2);
            uint8_t rr = (uint8_t)(r8 * a);
            uint8_t gg = (uint8_t)(g8 * a);
            uint8_t bb = (uint8_t)(b8 * a);
            uint16_t out = ((rr & 0xF8) << 8) | ((gg & 0xFC) << 3) | (bb >> 3);
            frame[i] = out;
        }
        draw_frame(spi, frame);
        free(frame);
        vTaskDelay(pdMS_TO_TICKS(80));
    }
}