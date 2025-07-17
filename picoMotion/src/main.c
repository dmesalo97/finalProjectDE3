#include "pico/stdlib.h"
#include "lcd_display.h"
#include "motor_control.h"
#include "buttons.h"

typedef enum {LOW, MEDIUM, HIGH} SpeedLevel;
bool motor_on = false;
StepperDirection direction = CLOCKWISE;
SpeedLevel speed = MEDIUM;

uint get_delay_us(SpeedLevel s) {
    switch(s) {
        case LOW: return 8000;
        case MEDIUM: return 4000;
        case HIGH: return 200;
        default: return 2000;
    }
}

void update_lcd() {
    LiquidCrystal_I2C* lcd_ptr = lcd_get();
    lcd_set_cursor(lcd_ptr, 0, 0);
    lcd_print(lcd_ptr, motor_on ? "Motor: ON       " : "Motor: OFF      ");
    lcd_set_cursor(lcd_ptr, 0, 1);
    lcd_print(lcd_ptr, direction == CLOCKWISE ? "Dir: CW " : "Dir: CCW");
    lcd_print(lcd_ptr, " Vel: ");
    lcd_print(lcd_ptr, speed == LOW ? "L" : (speed == MEDIUM ? "M" : "H"));
    lcd_print(lcd_ptr, " ");
}

void show_splash_screen(LiquidCrystal_I2C* lcd) {
    lcd_set_cursor(lcd, 0, 0);
    lcd_print(lcd, "Iniciando:");
    lcd_set_cursor(lcd, 0, 1);
    lcd_print(lcd, "PicoMotion");  
    sleep_ms(2000);
    lcd_set_cursor(lcd, 0, 0);
    lcd_print(lcd, "                ");
    lcd_set_cursor(lcd, 0, 1);
    lcd_print(lcd, "                ");
}


int main() {
    stdio_init_all();
    lcd_init_custom();
    LiquidCrystal_I2C* lcd = lcd_get();
    show_splash_screen(lcd);
    buttons_init_interrupts();
    motor_init();
    update_lcd();
    

    while (true) {
        if (button_flags.pressed_on) {
            button_flags.pressed_on = false;
            motor_on = !motor_on;
            update_lcd(lcd);
        }

        if (button_flags.pressed_dir) {
            button_flags.pressed_dir = false;
            direction = direction == CLOCKWISE ? COUNTERCLOCKWISE : CLOCKWISE;
            update_lcd(lcd);
        }

        if (button_flags.pressed_vel) {
            button_flags.pressed_vel = false;
            speed = (speed + 1) % 3;
            update_lcd(lcd);
        }

        if (motor_on) {
            motor_step(direction);
            sleep_us(get_delay_us(speed));
        } else {
            sleep_ms(50);  // Espera pasiva
        }
    }

    return 0;
}
