/*
 * pwm.h
 *
 *  Created on: Oct 6, 2021
 *      Author: Ahmed Magdy
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

#define PWM_PORT_NUM 		PORTB_ID
#define PWM_PIN_NUM 		PIN3_ID


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}PWM_Clock;


void PWM_Init(PWM_Clock clock);

void PWM_setDuty(uint8 duty);


#endif /* PWM_H_ */
