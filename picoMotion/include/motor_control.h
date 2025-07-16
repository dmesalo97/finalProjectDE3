/**
 * @file motor_control.h
 * @brief Controlador para motor paso a paso 28BYJ-48 con ULN2003A.
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pico/stdlib.h"

/// Sentido de rotación del motor
typedef enum {
    CLOCKWISE,
    COUNTERCLOCKWISE
} StepperDirection;

void motor_init();
void motor_step(StepperDirection direction);
void motor_step_n(StepperDirection direction, uint32_t steps);

#endif
