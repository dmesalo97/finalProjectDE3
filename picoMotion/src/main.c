/**
 * @file main.c
 * @brief Prueba inicial de pantalla LCD para proyecto PicoMotion.
 */

#include "pico/stdlib.h"
#include "lcd_display.h"
#include "motor_control.h"

/**
 * @brief Función principal del programa.
 *
 * Inicializa la LCD y muestra un mensaje de prueba.
 */
int main() {
    stdio_init_all();

    lcd_init_custom();  ///< Inicialización de la pantalla LCD
    motor_init();
    motor_step_n(CLOCKWISE, 512);  // Da una vuelta completa aproximada
    sleep_ms(1000);
    motor_step_n(COUNTERCLOCKWISE, 512);

    while (true) {
        tight_loop_contents();  ///< Bucle vacío (polling base)
    }

    return 0;
}
