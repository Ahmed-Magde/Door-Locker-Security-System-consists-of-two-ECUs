/*
 * dc_motor.c
 *
 *  Created on: Oct 7, 2021
 *      Author: Ahmed Magdy
 */

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

void DcMotor_Init(void)
{
	PWM_Clock pwm_clock = {F_CPU_1024};

	PWM_Init(pwm_clock);


	GPIO_setupPinDirection( DcMotor_IN_PORT, DcMotor_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection( DcMotor_IN_PORT, DcMotor_IN2_PIN, PIN_OUTPUT);

	GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN1_PIN, LOGIC_LOW);
	GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN2_PIN, LOGIC_LOW);


	GPIO_setupPinDirection( DcMotor_EN_PORT, DcMotor_EN_PIN, PIN_OUTPUT);
	PWM_setDuty(0);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state==CW)
	{
		GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN1_PIN, LOGIC_HIGH);
		GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN2_PIN, LOGIC_LOW);

		PWM_setDuty(speed);
	}
	else if(state==A_CW)
	{
		GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN1_PIN, LOGIC_LOW);
		GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN2_PIN, LOGIC_HIGH);

		PWM_setDuty(speed);
	}
	else if(state==STOP)
	{
		GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN1_PIN, LOGIC_LOW);
		GPIO_writePin( DcMotor_IN_PORT, DcMotor_IN2_PIN, LOGIC_LOW);

		PWM_setDuty(0);
	}

}















