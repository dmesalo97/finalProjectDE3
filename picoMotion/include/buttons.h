/**
 * @file buttons.h
 * @brief Manejo de botones con interrupciones GPIO.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"

typedef struct {
    volatile bool pressed_on;
    volatile bool pressed_dir;
    volatile bool pressed_vel;
} ButtonFlags;

extern ButtonFlags button_flags;

void buttons_init_interrupts();

#endif
