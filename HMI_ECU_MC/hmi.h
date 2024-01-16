/******************************************************************************
 *
 * Module: HMI_Driver
 *
 * File Name: hmi.h
 *
 * Description: Header file for the hmi driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/

#ifndef HMI_H_
#define HMI_H_

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





/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/************************************************************************
 *[Description]: function to initialize the modules and driver in the HMI_ecu
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ***********************************************************************/
void HMI_init(void);


/************************************************************************
 *[Description]: function to save the password in the passed array and
 *				 display as '*' in the lcd
 *
 *[arguments]: the function take address of the array
 *			   that want to save pass in it.
 *
 *[return]: the function return void.
 ***********************************************************************/
void PASS_enter(uint8 *ptr);

/************************************************************************
 *[Description]: function to  crate new password for the first time use system
 *
 *[arguments]: the function take void
 *
 *[return]: the function return void.
 ***********************************************************************/
void PASS_firstTime(void);

/************************************************************************
 *[Description]: function to used to crate new password
 *				 or when change the password
 *
 *[arguments]: the function take void
 *
 *[return]: the function return void.
 ***********************************************************************/
void PASS_new(void);

/************************************************************************
 *[Description]: function to send the password to control_ecu
 *
 *[arguments]: the function take the command
 *			   that you want to do in the pass
 * 			   (check or save)
 *
 *[return]: the function return void.
 ************************************************************************/
void PASS_sendToController(uint8 command);

/************************************************************************
 *[Description]: function to display the option in the lcd
 *				 to user:(1:open door  2:change pass)
 *
 *[arguments]: the function take void
 *
 *[return]: the function return user choose.
 ************************************************************************/
uint8 MAIN_option(void);

/************************************************************************
 *[Description]: function to  get the password from user and check it
 *
 *[arguments]: the function take void
 *
 *[return]: the function return void.
 ************************************************************************/
void PASSWORD(void);

/************************************************************************
 *[Description]: function to send command to the control_ecu
 *
 *[arguments]: the function take the command
 *
 *[return]: the function return void.
 ************************************************************************/
void SEND_controlCommand(uint8 command);

/************************************************************************
 *[Description]: function to receive data from the control_ecu
 *
 *[arguments]: the function take void
 *
 *[return]: the function return the received data.
 ************************************************************************/
uint8 RECEIVE_controlData(void);

/************************************************************************
 *[Description]:  function used to pass the call back function to timer module.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void OPEN_doorCallBack(void);

/************************************************************************
 *[Description]: function to display the motor status(open door ,close door)
 *				 and used to set time for each state.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void OPEN_doorActionDisplay(void);


/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while displaying status of
 *				 the door.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void OPEN_door(void);

/************************************************************************
 *[Description]:  function used to pass the call back function to timer module.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void BUZZER_callBack(void);


/************************************************************************
 *[Description]: function to display the buzzer status
 *				 and used to set time for each state.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void BUZZER_actionDisplay(void);


/************************************************************************
 *[Description]: function to initiate the timer
 *				 and the function hold the system while displaying status of
 *				 the buzzer.
 *
 *[arguments]: the function take void.
 *
 *[return]: the function return void.
 ************************************************************************/
void BUZZER(void);




#endif /* HMI_H_ */
