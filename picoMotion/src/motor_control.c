/**
 * @file motor_control.c
 * @brief Implementación del controlador del motor paso a paso 28BYJ-48.
 */

#include "motor_control.h"

// Pines conectados al ULN2003
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

// Secuencia de pasos en media fase
static const uint8_t step_sequence[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

#define STEP_DELAY_US 2000  // Ajusta velocidad del motor

void motor_init() {
    gpio_init(IN1); gpio_set_dir(IN1, GPIO_OUT);
    gpio_init(IN2); gpio_set_dir(IN2, GPIO_OUT);
    gpio_init(IN3); gpio_set_dir(IN3, GPIO_OUT);
    gpio_init(IN4); gpio_set_dir(IN4, GPIO_OUT);
}

void motor_step(StepperDirection direction) {
    for (int step = 0; step < 8; step++) {
        int idx = (direction == CLOCKWISE) ? step : (7 - step);
        gpio_put(IN1, step_sequence[idx][0]);
        gpio_put(IN2, step_sequence[idx][1]);
        gpio_put(IN3, step_sequence[idx][2]);
        gpio_put(IN4, step_sequence[idx][3]);
        sleep_us(STEP_DELAY_US);
    }
}

void motor_step_n(StepperDirection direction, uint32_t steps) {
    for (uint32_t i = 0; i < steps; i++) {
        motor_step(direction);
    }
}
