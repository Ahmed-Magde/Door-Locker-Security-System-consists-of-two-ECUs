 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the BUZZER driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

#define BUZZER_PORT   PORTA_ID
#define BUZZER_PIN    PIN0_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*[Description]:  Function to initialize the buzzer and set pin direction as output*/
void BUZZER_init(void);

/*[Description]:  Function to turn on the buzzer*/
void BUZZER_start(void);

/*[Description]:  Function to turn off the buzzer*/
void BUZZER_stop(void);


#endif /* BUZZER_H_ */
