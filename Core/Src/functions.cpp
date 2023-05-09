#include "functions.h"

#include "main.h"

uint8_t is_close(int32_t value, int32_t objective, uint8_t tolerance) {
    return (abs(value - objective) <= tolerance) ? 1 : 0;
}

void print_encoder() {
    lcd_cursor(0, 0);
    lcd_int(encoder_position);
    lcd_string("    ");
}

void bend(int angle, void (*to_do)(void)) {
    bend_objective = angle;
    HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
    if (angle > encoder_position) {
        HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_SET);

        HAL_GPIO_WritePin(rele2_GPIO_Port, rele2_Pin, GPIO_PIN_RESET);
        TIM1->CCR1 = 0;
    } else {
        HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(rele2_GPIO_Port, rele2_Pin, GPIO_PIN_SET);
        TIM1->CCR1 = 1000;
    }
    while (!bended) {
        if (to_do != NULL) {
            to_do();
        }
        if (is_close((int32_t)encoder_position, (int32_t)bend_objective, 30) && (TIM1->CCR1 > 10)) {
            TIM1->CCR1 = 650;  // get the relay closer to disarming
        }
    }
    TIM1->CCR1 = 1000;  // make sure the relay is disarmed
    HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
    bended = 0;
}
