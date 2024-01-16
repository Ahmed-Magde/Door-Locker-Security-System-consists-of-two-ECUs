/*
 * hmi_ecu.c
 *
 *  Created on: Oct 22, 2021
 *      Author: Ahmed Magdy
 */

#include "hmi.h"
#include <avr/interrupt.h>


int main()
{
	uint8 select=0;

	HMI_init();
	SREG |=(1<<7);
	//_delay_ms(2000);

	PASS_firstTime();

	while(1)
	{

		select = 0;
		select = MAIN_option();

		PASSWORD();

		switch(select)
		{
		case '+':

			SEND_controlCommand(OPEN_DOOR_COMMAND);
			OPEN_door();

			break;
		case '-':

			PASS_new();

			break;

		}


	}//end while loop

}//end main function


