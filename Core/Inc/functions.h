#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "stm32f1xx_hal.h"
#include "i2c-lcd.h"

void bend(int angle);
void bend(int angle, void (*to_do)(void));
void feed(int amount);
void print_encoder();

extern volatile int encoder_position, bend_objective;
extern volatile char bended;

#endif /* INC_FUNCTIONS_H_ */
