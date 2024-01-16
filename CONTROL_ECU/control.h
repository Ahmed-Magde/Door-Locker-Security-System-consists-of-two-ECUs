/******************************************************************************
 *
 * Module: control MC1
 *
 * File Name: control.h
 *
 * Description: Header file for control_ecu_MC2 function.
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/


#ifndef CONTROL_H_
#define CONTROL_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define	UART_BAUD_RATE 					9600

#define PASS_SIZE  	5
#define ENTER		13
#define NUMBER_OF_WRONG_PASSWORD_TRY	3

/*some of command to handle the communication between MC1 & MC2 */
#define 	OPEN_DOOR_COMMAND  					 1
#define 	CHECK_PASS_COMMAND  				 2
#define 	SAVE_PASS_COMMAND   				 3
#define 	BUZZER_COMMAND 	  					 4
#define 	FIRST_TIME_PASS_COMMAND 	  		 5


#define UARET_READY					0XFF
#define NOT_FIRST_TIME				0X55
#define YES_FIRST_TIME				0x11

/*address in the eeprom to save the system status */
#define FIRST_TIME_PASS_state_ADDRESS		0X0200

/*address of the first location of password*/
#define PASS_ADDRESS						0X0300



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/************************************************************************
 *[Description]: function to initialize the modules and driver in the control_ecu
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ***********************************************************************/
void CONTROL_init(void);

/************************************************************************
 *[Description]: function to handle the communication between to MC1 & MC2
 * 				 used to send data to hmi_MC1.
 *[arguments]: the function take uint8 data the wanted to send.
 *
 *[return]: the function return void
 ***********************************************************************/
void SEND_controlData(uint8 command);

/************************************************************************
 *[Description]: function to handle the communication between to MC1 & MC2
 * 				 used to receive data to hmi_MC1.
 *
 *[arguments]: the function take void
 *
 *[return]: the function return uint8 / return the data received from MC1
 ************************************************************************/
uint8 RECEIVE_controlCommand(void);

/************************************************************************
 *[Description]: function to get the password from hmi_mc1
 * 				 and save it in the passed address.
 *
 *[arguments]: the function take the address of the array that you want to save pass in it.
 *
 *[return]: the function return void.
 ************************************************************************/
void PASS_getFromHmi(uint8 *ptr);

/************************************************************************
 *[Description]: function to save the password in the external eeprom.
 *
 *[arguments]: the function take the address of the array that has the password you wont to save.
 *
 *[return]: the function return void.
 ************************************************************************/
void PASS_saveToEeprom(uint8 *ptr);

/************************************************************************
 *[Description]: function to read the password from the external eeprom.
 *
 *[arguments]: the function take the address of the array that you want to but read data in it.
 *
 *[return]: the function return void.
 ************************************************************************/
void PASS_readFromEeprom(uint8 *ptr);

/************************************************************************/

/***********************************************************************
 * [Description]: function to compare two arrays two password
 *				 the function compare between the passed password with the password that in the
 *				 external eeprom.
 *
 *[arguments]: the function take the address of the array(password) that you want to check it.
 *
 *[return]: the function return result of check (TRUE | FALSE).
 ***********************************************************************/
uint8 PASS_check(uint8 *ptr);


/************************************************************************
 *[Description]: function used to set password in the first time to use
 * 				 the system,and  (execute for one time).
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void PASS_firstTime(void);


/************************************************************************
 *[Description]: function used to pass the call back function to timer module.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void OPEN_doorCallBack(void);


/************************************************************************
 *[Description]: function to drive the motor(cw ,a_ce,stop)
 *				 and used to set time for each state.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void OPEN_doorAction(void);


/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while opening the door.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void OPEN_door(void);

/************************************************************************
 *[Description]:  function used to pass the call back function to timer module..
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void BUZZER_callBack(void);

/************************************************************************
 *[Description]: function to drive the buzzer(start,stop)
 *				 and used to set time for each state.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void BUZZER_action(void);

/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while alarm(buzzer).
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void BUZZER(void);




#endif /* CONTROL_H_ */
