/*
 * pwm.c
 *
 *  Created on: Oct 6, 2021
 *      Author: Ahmed Magdy
 */

#include "pwm.h"
#include "gpio.h"
#include <avr/io.h>

void PWM_Init(PWM_Clock clock)
{
	TCNT0 = 0;

	/* configure the timer
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) ;
	TCCR0 = (TCCR0 & 0XF8) | (clock );
	GPIO_setupPinDirection( PWM_PORT_NUM, PWM_PIN_NUM,PIN_OUTPUT);

}

void PWM_setDuty(uint8 duty_precent)
{
	uint8 ocr_val=0;

	ocr_val=(uint8)(((float32)duty_precent/100.0)*255.0);
	OCR0  = ocr_val;

}








