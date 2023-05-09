#include "functions.h"

#include "main.h"

void refresh_display_text() {
    lcd_cursor(0, 0);
    lcd_string("Dobradeira de Tubos");
    lcd_cursor(1, 0);
    lcd_string("Atual:");
    lcd_cursor(3, 0);
    lcd_string("Tecla:  Sensor:");
}

void refresh_display_vars() {
    lcd_cursor(1, 7);
    convert_to_angle(encoder_position);
    lcd_string(angle_string);
    lcd_string("  ");
    lcd_cursor(3, 6);
    if (key != ' ') {
        lcd_send_data(key);
    }
    lcd_cursor(3, 15);
    lcd_int(!HAL_GPIO_ReadPin(end_stop_GPIO_Port, end_stop_Pin));
}

void convert_to_angle(int encoder_value) {
    int angle = encoder_value * 36000 / 3400;
    if (angle >= 0) {
        sprintf(angle_string, "%d.%d", abs(angle / 100), abs(angle % 100));
    } else {
        sprintf(angle_string, "-%d.%d", abs(angle / 100), abs(angle % 100));
    }
}

void print_encoder() {
    lcd_cursor(0, 0);
    lcd_int(encoder_position);
    lcd_string("    ");
}

void bend(int angle, void (*to_do)(void)) {
    bend_objective = angle;
    HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
    if (bend_objective > encoder_position) {
        HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_RESET);
    }
    while (!bended) {
        if (to_do != NULL) {
            to_do();
        }
    }
    HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
    bended = 0;
}