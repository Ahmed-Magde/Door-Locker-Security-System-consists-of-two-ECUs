 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: source file for the BUZZER driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"




/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/



/*[Description]:  Function to initialize the buzzer and set pin direction as output*/
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN  , PIN_OUTPUT);//make pin as output

	GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);//write initial value (zero)
}

/*[Description]:  Function to turn on the buzzer*/
void BUZZER_start(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_HIGH);

}

/*[Description]:  Function to turn off the buzzer*/
void BUZZER_stop(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);

}
