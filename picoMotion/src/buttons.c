/**
 * @file buttons.c
 * @brief Implementación de botones con detección de flanco descendente.
 */

#include "buttons.h"

void buttons_init() {
    for (uint gpio = 6; gpio <= 8; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);  // Habilita pull-up interno
    }
}

bool button_pressed(uint gpio) {
    static absolute_time_t last_press[32] = {0};  // antirebote
    if (!gpio_get(gpio)) {
        if (absolute_time_diff_us(last_press[gpio], get_absolute_time()) > 300000) {
            last_press[gpio] = get_absolute_time();
            return true;
        }
    }
    return false;
}
