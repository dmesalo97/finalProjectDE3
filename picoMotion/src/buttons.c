/**
 * @file buttons.c
 * @brief Implementación de botones con interrupciones en GPIO.
 */

#include "buttons.h"

#define BTN_ONOFF   6
#define BTN_DIR     7
#define BTN_SPEED   8

ButtonFlags button_flags = {false, false, false};

// Tiempos para antirebote (uno por botón)
static absolute_time_t last_press_on;
static absolute_time_t last_press_dir;
static absolute_time_t last_press_vel;

static void gpio_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) {
        absolute_time_t now = get_absolute_time();

        switch (gpio) {
            case BTN_ONOFF:
                if (absolute_time_diff_us(last_press_on, now) > 300000) {
                    last_press_on = now;
                    button_flags.pressed_on = true;
                }
                break;

            case BTN_DIR:
                if (absolute_time_diff_us(last_press_dir, now) > 300000) {
                    last_press_dir = now;
                    button_flags.pressed_dir = true;
                }
                break;

            case BTN_SPEED:
                if (absolute_time_diff_us(last_press_vel, now) > 300000) {
                    last_press_vel = now;
                    button_flags.pressed_vel = true;
                }
                break;
        }
    }
}

void buttons_init_interrupts() {
    // Configuración básica de los botones
    for (uint gpio = BTN_ONOFF; gpio <= BTN_SPEED; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);
        gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_FALL, true);
    }

    // Registrar el callback global (una sola vez)
    gpio_set_irq_callback(gpio_callback);
    irq_set_enabled(IO_IRQ_BANK0, true);
}
