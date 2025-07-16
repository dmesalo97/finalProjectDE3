#include "LiquidCrystal_I2C.h"
#include "pico/stdlib.h"
#include <string.h>
#include <stdio.h>

#define LCD_CHR 1
#define LCD_CMD 0

#define LCD_LINE_1 0x80
#define LCD_LINE_2 0xC0

#define ENABLE 0b00000100
#define BACKLIGHT 0x08

static void lcd_toggle_enable(LiquidCrystal_I2C *lcd, uint8_t val);
static void lcd_send_byte(LiquidCrystal_I2C *lcd, uint8_t val, uint8_t mode);

LiquidCrystal_I2C lcd_init(uint8_t address, uint8_t cols, uint8_t rows) {
    LiquidCrystal_I2C lcd;
    lcd.addr = address;
    lcd.cols = cols;
    lcd.rows = rows;
    return lcd;
}

void lcd_toggle_enable(LiquidCrystal_I2C *lcd, uint8_t val) {
    sleep_us(500);
    uint8_t data = val | ENABLE | BACKLIGHT;
    i2c_write_blocking(i2c0, lcd->addr, &data, 1, false);
    sleep_us(500);
    data = (val & ~ENABLE) | BACKLIGHT;
    i2c_write_blocking(i2c0, lcd->addr, &data, 1, false);
    sleep_us(500);
}

void lcd_send_byte(LiquidCrystal_I2C *lcd, uint8_t val, uint8_t mode) {
    uint8_t high = (val & 0xF0) | mode | BACKLIGHT;
    uint8_t low = ((val << 4) & 0xF0) | mode | BACKLIGHT;

    i2c_write_blocking(i2c0, lcd->addr, &high, 1, false);
    lcd_toggle_enable(lcd, high);

    i2c_write_blocking(i2c0, lcd->addr, &low, 1, false);
    lcd_toggle_enable(lcd, low);
}

void lcd_send_command(LiquidCrystal_I2C *lcd, uint8_t cmd) {
    lcd_send_byte(lcd, cmd, LCD_CMD);
}

void lcd_send_data(LiquidCrystal_I2C *lcd, uint8_t data) {
    lcd_send_byte(lcd, data, LCD_CHR);
}

void lcd_begin(LiquidCrystal_I2C *lcd) {
    sleep_ms(50);
    lcd_send_command(lcd, 0x33);
    lcd_send_command(lcd, 0x32);
    lcd_send_command(lcd, 0x28);
    lcd_send_command(lcd, 0x0C);
    lcd_send_command(lcd, 0x06);
    lcd_send_command(lcd, 0x01);
    sleep_ms(5);
}

void lcd_backlight(LiquidCrystal_I2C *lcd) {
    uint8_t val = BACKLIGHT;
    i2c_write_blocking(i2c0, lcd->addr, &val, 1, false);
}

void lcd_set_cursor(LiquidCrystal_I2C *lcd, uint8_t col, uint8_t row) {
    uint8_t pos = (row == 0) ? LCD_LINE_1 : LCD_LINE_2;
    lcd_send_command(lcd, pos + col);
}

void lcd_print(LiquidCrystal_I2C *lcd, const char *str) {
    while (*str) {
        lcd_send_data(lcd, *str++);
    }
}
