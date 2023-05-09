#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <math.h>

#include "i2c-lcd.h"
#include "stm32f1xx_hal.h"

uint8_t is_close(uint32_t a, uint32_t b, uint8_t tolerance);
void print_encoder();
void bend(int angle, void (*to_do)(void));

extern volatile int encoder_position, bend_objective;
extern volatile char bended;

#endif /* INC_FUNCTIONS_H_ */
