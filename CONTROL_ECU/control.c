/*
 * control.c
 *
 *  Created on: Oct 23, 2021
 *      Author: Ahmed Magdy
 */


#include "control.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "uart.h"
#include "timer.h"
#include <util/delay.h>
#include <avr/interrupt.h>

static uint8 tick=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/



/*******************************************************************************
 * [Description]: function to initialize the modules and driver in the control ecu
 *******************************************************************************/
void CONTROL_init(void)
{

	UART_ConfigType	UART_Config = {UART_BAUD_RATE,Disabled,One_Bit,Bit_8};

	UART_init(&UART_Config);//initialize the UART
	EEPROM_init();//initialize the external eeprom
	DcMotor_Init();//initialize the dc motor
	BUZZER_init();//initialize the buzzer
}


/*******************************************************************************
 * [Description]: function to handle the communication between to MC1 & MC2
 * 				  used to send data to hmi_MC1.
 *******************************************************************************/
void SEND_controlData(uint8 command)
{
	//Waiting the second microcontroller to be ready to send command
	while(UART_recieveByte() != UARET_READY );
	//send command
	UART_sendByte(command);

}

/*******************************************************************************
 * [Description]: function to handle the communication between to MC1 & MC2
 * 				 used to receive data to hmi_MC1.
 *******************************************************************************/
uint8 RECEIVE_controlCommand(void)
{
	//send ready command first to receive data
	UART_sendByte(UARET_READY);
	//return the received data
	return UART_recieveByte();
}


/*******************************************************************************
 * [Description]: function to get the password from hmi_mc1
 * 				 and save it in the global variable.
 *******************************************************************************/
void PASS_getFromHmi(uint8 *ptr)
{
	uint8 i ;

	for(i=0;i<PASS_SIZE;i++)
	{
		ptr[i] = RECEIVE_controlCommand();
	}

}

/*******************************************************************************
 * [Description]: function to save the password in the external eeprom.
 *******************************************************************************/
void PASS_saveToEeprom(uint8 *ptr)
{
	uint8 i;

	for(i=0;i<PASS_SIZE;i++)
	{
		//make loop to make sure the data is written correctly
		while(!(EEPROM_writeByte(PASS_ADDRESS+i, ptr[i])));
		//Waiting eeprom to write data
		_delay_ms(80);
	}

}

/*******************************************************************************
 * [Description]: function to read the password from the external eeprom.
 *******************************************************************************/
void PASS_readFromEeprom(uint8 *ptr)
{
	uint8 i;
	uint8 temp=0;
	for(i=0;i<PASS_SIZE;i++)
	{
		//make loop to make sure the data is read correct
		while(!(EEPROM_readByte(PASS_ADDRESS+i, &temp)));
		ptr[i] = temp;
	}//end reading loop
}

/***********************************************************************
 * [Description]: function to compare two arrays (two password)
 *				 the function compare between the passed password with the password that in the
 *				 external eeprom.
 ***********************************************************************/
uint8 PASS_check(uint8 *ptr)
{
	uint8 i;
	uint8 password1[PASS_SIZE]={0};


	//receive the password from HMI(from user) to check it
	PASS_getFromHmi(ptr);

	//get password from external eeprom
	PASS_readFromEeprom(password1);

	for(i=0;i<PASS_SIZE;i++)
	{
		if(password1[i] == ptr[i]) //check if entered pass is correct or not
		{
			//do nothing
		}
		else
		{
			return FALSE;
		}

	}//end check

	return TRUE;

}//end CHECK_PASS function


/************************************************************************
 *[Description]: function used to set password in the first time to use
 * 				 the system,and  (execute for one time).
 ************************************************************************/
void PASS_firstTime(void)
{
	uint8 first_time_state=0;

	//get the status value from external eeprom and make loop to make sure that data read from memory correct
	while( !(EEPROM_readByte(FIRST_TIME_PASS_state_ADDRESS, & first_time_state)) );


	if(first_time_state == NOT_FIRST_TIME)//check the status value
	{
		SEND_controlData(NOT_FIRST_TIME);

	}
	else
	{
		SEND_controlData(YES_FIRST_TIME);
		EEPROM_writeByte(FIRST_TIME_PASS_state_ADDRESS, NOT_FIRST_TIME);
		_delay_ms(10);

	}//end check
}//end function



/************************************************************************
 *[Description]: function used to passed to timer module.
 ************************************************************************/
void OPEN_doorCallBack(void)
{
	tick++;//tick increment every 1s
}



/************************************************************************
 *[Description]: function to drive the motor(cw ,a_ce,stop)
 *				 and used to set time for each state.
 ************************************************************************/
void OPEN_doorAction(void)
{
	if(tick >= 0 && tick < 15)
	{
		//make motor rotate CW for 15 s
		DcMotor_Rotate(CW,100);
	}
	else if(tick >= 15 && tick < 18)
	{
		//make motor stop for 3 s
		DcMotor_Rotate(STOP, 0);
	}
	else if(tick >= 18 && tick < 33)
	{
		//make motor rotate A_CW for 15 s
		DcMotor_Rotate(A_CW, 100);
	}
	else if(tick >= 33)
	{
		//STOP motor
		DcMotor_Rotate(STOP, 0);
	}

}


/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while opening the door.
 ************************************************************************/
void OPEN_door(void)
{

	uint16 ctc_val=7812;//the initial value for OCR for 1 tick for 1s

	/*initialize the timer:
	 * 		using timer1
	 * 		tcnt1=0
	 * 		compare mode
	 * 		using 1024 prescaler
	 */
	TIMER_ConfigType  TIMER_Config = {TIMER1,0,ctc_val,CTC,T1_clk_1024};

	//pass the call back function to timer module
	TIMER_setCallBack(OPEN_doorCallBack, TIMER1);
	//initialize the timer
	TIMER_init(&TIMER_Config);


	while(1)//hold the system while opening and closing door
	{
		OPEN_doorAction();

		if(tick > 33)
		{
			TIMER_DeInit(TIMER1);
			tick=0;
			return;
		}

	}//end of holding system


}

/************************************************************************
 *[Description]: function used to passed to timer module.
 ************************************************************************/
void BUZZER_callBack(void)
{
	tick++;//tick increment every 1s
}

/************************************************************************
 *[Description]: function to drive the buzzer(start,stop)
 *				 and used to set time for each state.
 ************************************************************************/
void BUZZER_action(void)
{

	if(tick == 0)
	{
		//switch buzzer on for 60s
		BUZZER_start();
	}
	else if(tick == 60)
	{
		//switch buzzer off after 60s
		BUZZER_stop();
	}

}


/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while alarm(buzzer).
 ************************************************************************/
void BUZZER(void)
{
	uint16 ctc_val=7812;//the initial value for OCR for 1 tick for 1s

	/*initialize the timer:
	 * 		using timer1
	 * 		tcnt1=0
	 * 		compare mode
	 * 		using 1024 prescaler
	 */
	TIMER_ConfigType  TIMER_Config = {TIMER1,0,ctc_val,CTC,T1_clk_1024};

	//pass the call back function to timer module
	TIMER_setCallBack(BUZZER_callBack, TIMER1);
	//initialize the timer
	TIMER_init(&TIMER_Config);

	while(1)//holding the system while buzzer
	{
		BUZZER_action();

		if(tick > 60)
		{
			TIMER_DeInit(TIMER1);
			tick=0;
			return;
		}
	}//end of holding system
}
