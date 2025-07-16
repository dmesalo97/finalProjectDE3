// include/lcd_display.h
#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "LiquidCrystal_I2C.h"

void lcd_init_custom();
LiquidCrystal_I2C* lcd_get();

#endif
