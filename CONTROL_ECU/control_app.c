/*
 * control_app.c
 *
 *  Created on: Oct 23, 2021
 *      Author: Ahmed Magdy
 */

#include "control.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
	uint8 command = 0 ;
	uint8 password[PASS_SIZE]={0};

	SREG |=(1<<7);

	CONTROL_init();
	//_delay_ms(2000);



	while(1)
	{
		command= 0;
		command = RECEIVE_controlCommand();

		switch(command)
		{

		case OPEN_DOOR_COMMAND:

			OPEN_door();

			break;

		case CHECK_PASS_COMMAND:

			SEND_controlData(PASS_check(password));

			break;
		case SAVE_PASS_COMMAND:

			PASS_getFromHmi(password);
			PASS_saveToEeprom(password);

			break;
		case BUZZER_COMMAND:

			BUZZER();

			break;
		case FIRST_TIME_PASS_COMMAND:

			PASS_firstTime();

			break;

		}

	}
}

































