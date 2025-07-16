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
        case LOW: return 4000;
        case MEDIUM: return 2000;
        case HIGH: return 800;
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

int main() {
    stdio_init_all();
    lcd_init_custom();
    buttons_init();
    motor_init();

    update_lcd();

    while (true) {
        if (button_pressed(6)) {
            motor_on = !motor_on;
            update_lcd();
        }
        if (button_pressed(7)) {
            direction = direction == CLOCKWISE ? COUNTERCLOCKWISE : CLOCKWISE;
            update_lcd();
        }
        if (button_pressed(8)) {
            speed = (speed + 1) % 3;
            update_lcd();
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
