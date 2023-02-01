#include "functions.h"
#include "main.h"

void print_encoder() {
	lcd_cursor(0, 0);
	lcd_int(encoder_position);
	lcd_string("    ");
}

void bend(int angle) {
	bend_objective = angle;
	HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
	if (angle > encoder_position) {
		HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_RESET);
	}
	while (!bended) {
	}
	HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
	bended = 0;
}

void bend(int angle, void (*to_do)(void)) {
	bend_objective = angle;
	HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
	if (angle > encoder_position) {
		HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(motor_a_GPIO_Port, motor_a_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor_b_GPIO_Port, motor_b_Pin, GPIO_PIN_RESET);
	}
	while (!bended) {
		to_do();
	}
	HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
	bended = 0;
}

void feed(int amount) {
	if (amount < 0)
		HAL_GPIO_WritePin(dir_GPIO_Port, dir_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(dir_GPIO_Port, dir_Pin, GPIO_PIN_RESET);
	for (int i = 0; i < (amount * 2); i++) {
		HAL_GPIO_TogglePin(step_GPIO_Port, step_Pin);
		HAL_Delay(0);
	}
}
