/******************************************************************************
 *
 * Module: HMI_Driver
 *
 * File Name: hmi.c
 *
 * Description: source file for the hmi driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/

#include "hmi.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include <util/delay.h> /* For the delay functions */
#include <avr/interrupt.h>



static uint8  pass[PASS_SIZE]={0};
static uint8  tick=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/************************************************************************
 *[Description]: function to initialize the modules and driver in the HMI_ecu
 ***********************************************************************/
void HMI_init(void)
{
	UART_ConfigType	UART_Config = {UART_BAUD_RATE,Disabled,One_Bit,Bit_8};

	UART_init(&UART_Config);
	LCD_init();

}


/************************************************************************
 *[Description]: function to send command to the control_ecu
 ************************************************************************/
void SEND_controlCommand(uint8 command)
{
	//Waiting the second microcontroller to be ready to send command
	while(UART_recieveByte() != UARET_READY ){}
	//send command
	UART_sendByte(command);
}


/************************************************************************
 *[Description]: function to receive data from the control_ecu
 ************************************************************************/
uint8 RECEIVE_controlData(void)
{
	//send ready command first to receive data
	UART_sendByte(UARET_READY);
	//return the received data
	return UART_recieveByte();
}


/************************************************************************
 *[Description]: function to send the password to control_ecu
 * 				and send a command to choose the operation that will do
 * 				in the password.
 ************************************************************************/
void PASS_sendToController(uint8 command)
{
	uint8 i ;

	SEND_controlCommand(command);

	for(i=0;i<PASS_SIZE;i++)
	{
		//receive the password and save it in the global pass
		SEND_controlCommand(pass[i]);
	}//end loop of receiving the password

}



/************************************************************************
 *[Description]: function to save the password in the passed array and
 *				 display as '*' in the lcd
 ***********************************************************************/
void PASS_enter(uint8 *ptr)
{
	uint8 i;

	//for loop to get pass from user
	for(i=0;i<PASS_SIZE;i++)
	{
		//write on the number *
		LCD_displayStringRowColumn(1, i-1, "*");

		while(KEYPAD_getPressedKey() > 9);//waiting until press any number.

		ptr[i] = KEYPAD_getPressedKey(); //save the pressed key in the array
		LCD_moveCursor(1, i);
		//write the password in the passed array
		LCD_intgerToString(ptr[i]);
		_delay_ms(1500);

	}//end loop of getting the password from user
	//write on the number *
	LCD_displayStringRowColumn(1, i-1, "*");
	while(KEYPAD_getPressedKey()!= ENTER);//wait until user press enter

}


/************************************************************************
 *[Description]: function to  crate new password for the first time use system.
 ***********************************************************************/
void PASS_firstTime(void)
{
	uint8  state=0;

	/*send command to control_ecu to check if that is the first time
	 * to use the system or not
	 */
	SEND_controlCommand(FIRST_TIME_PASS_COMMAND);

	state = RECEIVE_controlData();

	if(state == YES_FIRST_TIME)//if it is first time make new password.
	{
		LCD_displayStringRowColumn(0,5,"Hello");
		_delay_ms(5000);
		PASS_new();
	}

}

/************************************************************************
 *[Description]: function to used to crate new password
 *				 or when change the password.
 ***********************************************************************/
void PASS_new(void)
{
	//two temporary array to get the password from user and check them
	uint8 temp1[PASS_SIZE]= {0} , temp2[PASS_SIZE]= {0};
	uint8 i,check_flag=FALSE;



	while(!check_flag)//while loop to make sure that user enter two identical password.
	{

		LCD_clearScreen();//clear the lcd
		LCD_displayStringRowColumn(0,0,"Enter new pass:");
		//put the first entered pass in the temp1
		PASS_enter(temp1);


		LCD_clearScreen();//clear the lcd
		LCD_displayStringRowColumn(0,0,"Re_enter pass:");
		//put the second entered pass in the temp2
		PASS_enter(temp2);


		for(i=0;i<PASS_SIZE;i++)//for loop to check if the password is identical or not.
		{
			//check if the password is identical or not.
			if(temp1[i]==temp2[i])
			{
				//if the number is identical put it in the global pass
				pass[i]=temp1[i];
				check_flag=TRUE;
			}
			else
			{

				check_flag=FALSE;

				LCD_clearScreen();//clear the lcd
				LCD_displayStringRowColumn(0,0,"NOT IDENTICAL");
				LCD_displayStringRowColumn(1,5,"PASS");
				_delay_ms(3000);

				break;
			}//end check

		}//end check loop

	}//end enter loop

	//send save command to control_ecu to save the password in the eeprom
	PASS_sendToController(SAVE_PASS_COMMAND);

}//end NEW_pass function


/************************************************************************
 *[Description]: function to  get the password from user and check it.
 ************************************************************************/
void PASSWORD(void)
{
	uint8 check_result=0;
	uint8 error_counter=0;

	while(!check_result)//while loop to make sure that user is enter the correct pass.
	{
		LCD_clearScreen();//clear the lcd
		LCD_displayStringRowColumn(0,0,"Enter the pass:");

		//get the password from user.
		PASS_enter(pass);

		//send check command to control_ecu to check if password is correct or not.
		PASS_sendToController(CHECK_PASS_COMMAND);
		check_result = RECEIVE_controlData();

		if(check_result == FALSE)//if the password is false increment the error counter
		{
			error_counter++;
			LCD_clearScreen();//clear the lcd
			LCD_displayStringRowColumn(0,0,"ERROR");
			LCD_displayStringRowColumn(1,0,"TRY AGAIN");
			_delay_ms(3000);
			LCD_clearScreen();//clear the lcd

			//if error counter is equal to maximum turn on buzzer
			if(error_counter == NUMBER_OF_WRONG_PASSWORD_TRY)
			{
				error_counter=0;

				SEND_controlCommand(BUZZER_COMMAND);
				BUZZER();
			}//end buzzer check.

		}//end result check.
	}//end password enter loop.

}//end password function

/************************************************************************
 *[Description]:  function used to pass the call back function to timer module.
 ************************************************************************/
void OPEN_doorCallBack(void)
{
	tick++;//tick increment every 1s
}

/************************************************************************
 *[Description]: function to display the motor status(open door ,close door)
 *				 and used to set time for each state.
 ************************************************************************/
void OPEN_doorActionDisplay(void)
{
	if(tick >= 0 && tick < 15)
	{
		LCD_displayStringRowColumn(0,0,"DOOR IS OPENING ");
		LCD_displayStringRowColumn(1,0,"PLEASE WAIT..   ");
		LCD_moveCursor(1,13);
		LCD_intgerToString(tick);//to display time per second

	}
	else if(tick >= 15 && tick < 18)
	{
		LCD_displayStringRowColumn(0,0,"DOOR OPENED YOU");
		LCD_displayStringRowColumn(1,0,"CAN ENTER      ");
		LCD_moveCursor(1,13);
		LCD_intgerToString(tick-15);


	}
	else if(tick >= 18 && tick < 33)
	{
		LCD_displayStringRowColumn(0,0,"DOOR IS CLOSING ");
		LCD_displayStringRowColumn(1,0,"                ");
		LCD_moveCursor(1,13);
		LCD_intgerToString(tick-18);

	}
	else if(tick >= 33)
	{
		LCD_displayStringRowColumn(0,0,"DOOR IS CLOSED ");
		_delay_ms(3000);

	}

}

/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while displaying status of
 *				 the door.
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
	//pass the call back function to timer module.
	TIMER_setCallBack(OPEN_doorCallBack, TIMER1);
	//initialize the timer
	TIMER_init(&TIMER_Config);


	while(1)//hold the system while opening and closing door.
	{
		OPEN_doorActionDisplay();

		if(tick > 33)
		{
			TIMER_DeInit(TIMER1);
			tick=0;
			return;
		}

	}//end of holding system


}

/************************************************************************
 *[Description]:  function used to pass the call back function to timer module.
 ************************************************************************/
void BUZZER_callBack(void)
{
	tick++;//tick increment every 1s
}


/************************************************************************
 *[Description]: function to display the buzzer status
 *				 and used to set time for each state.
 ************************************************************************/
void BUZZER_actionDisplay(void)
{

	if(tick >= 0)
	{
		LCD_displayStringRowColumn(0,0,"WATCH OUT THERE ");
		LCD_displayStringRowColumn(1,0,"IS THIEF        ");
		LCD_moveCursor(1, 13);
		LCD_intgerToString(tick);
	}

}

/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while displaying status of
 *				 the buzzer.
 ************************************************************************/
void BUZZER(void)
{
	uint16 ctc_val=7815;//the initial value for OCR for 1 tick for 1s

	/*initialize the timer:
	 * 		using timer1
	 * 		tcnt1=0
	 * 		compare mode
	 * 		using 1024 prescaler
	 */
	TIMER_ConfigType  TIMER_Config = {TIMER1,0,ctc_val,CTC,T1_clk_1024};

	//pass the call back function to timer module.
	TIMER_setCallBack(BUZZER_callBack, TIMER1);
	//initialize the timer.
	TIMER_init(&TIMER_Config);


	while(1)//holding the system while buzzer
	{
		BUZZER_actionDisplay();

		if(tick > 60)
		{
			TIMER_DeInit(TIMER1);
			tick=0;
			return;
		}
	}//end of holding system
}


/************************************************************************
 *[Description]: function to display the option in the lcd
 *				 to user:(1:open door  2:change pass)
 ************************************************************************/
uint8 MAIN_option(void)
{
	LCD_clearScreen();//clear the lcd
	LCD_displayStringRowColumn(0,0,"+: Open Door  ");
	LCD_displayStringRowColumn(1,0,"-: Change Pass");

	//while loop to make sure that user select from (+or-).
	while( ( KEYPAD_getPressedKey() != '+') && ((KEYPAD_getPressedKey()!= '-') ));

	return ( KEYPAD_getPressedKey());//return the pressed key.
}









