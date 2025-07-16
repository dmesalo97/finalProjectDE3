/**
 * @file buttons.h
 * @brief Manejo de botones para control de motor.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"

void buttons_init();
bool button_pressed(uint gpio);

#endif
