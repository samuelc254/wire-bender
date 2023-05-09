#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <math.h>

#include "i2c-lcd.h"
#include "stm32f1xx_hal.h"

void refresh_display_text();
void refresh_display_vars();
void convert_to_angle(int encoder_value);
void print_encoder();
void bend(int angle, void (*to_do)(void));

extern volatile int encoder_position, bend_objective, maximum;
extern volatile char bended;
extern char key;
extern char angle_string[];

#endif /* INC_FUNCTIONS_H_ */
