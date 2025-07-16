/**
 * @file LiquidCrystal_I2C.h
 * @brief Controlador LCD 16x2 vía I2C para Raspberry Pi Pico
 */

#ifndef LIQUIDCRYSTAL_I2C_H
#define LIQUIDCRYSTAL_I2C_H

#include "hardware/i2c.h"
#include <stdint.h>

/**
 * @struct LiquidCrystal_I2C
 * @brief Estructura base del LCD controlado vía I2C
 */
typedef struct {
    uint8_t addr;    ///< Dirección I2C del LCD (usualmente 0x27 o 0x3F)
    uint8_t cols;    ///< Columnas del LCD
    uint8_t rows;    ///< Filas del LCD
} LiquidCrystal_I2C;

LiquidCrystal_I2C lcd_init(uint8_t address, uint8_t cols, uint8_t rows);
void lcd_begin(LiquidCrystal_I2C *lcd);
void lcd_backlight(LiquidCrystal_I2C *lcd);
void lcd_set_cursor(LiquidCrystal_I2C *lcd, uint8_t col, uint8_t row);
void lcd_print(LiquidCrystal_I2C *lcd, const char *str);

#endif
