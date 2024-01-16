/*
 * dc_motor.h
 *
 *  Created on: Oct 7, 2021
 *      Author: Ahmed Magdy
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

#define ON 			CW
#define R_ON 		A_CW
#define OFF			STOP

#define DcMotor_IN_PORT			 PORTB_ID
#define DcMotor_IN1_PIN 		 PIN0_ID
#define DcMotor_IN2_PIN			 PIN1_ID

#define DcMotor_EN_PORT			 PORTB_ID
#define DcMotor_EN_PIN			 PIN3_ID



typedef enum
{
	STOP,CW,A_CW

}DcMotor_State;






//Description
//The Function responsible for setup the direction for the two
//motor pins through the GPIO driver.
//Stop at the DC-Motor at the beginning through the GPIO driver.

void DcMotor_Init(void);

// Description:
//The function responsible for rotate the DC Motor CW/ or A-CW or
//stop the motor based on the state input state value.
//Send the required duty cycle to the PWM driver based on the
//required speed value.

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
