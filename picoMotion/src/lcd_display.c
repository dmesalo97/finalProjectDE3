#include "lcd_display.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "LiquidCrystal_I2C.h"

#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1
#define LCD_ADDR 0x27

static LiquidCrystal_I2C lcd;

void lcd_init_custom() {
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    lcd = lcd_init(LCD_ADDR, 16, 2);
    lcd_begin(&lcd);
    lcd_backlight(&lcd);
    lcd_set_cursor(&lcd, 0, 0);
    lcd_print(&lcd, "Iniciando:");
}

LiquidCrystal_I2C* lcd_get() {
    return &lcd;
}
