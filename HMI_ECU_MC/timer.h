 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/********************************************************************************/
/*this enum to select which mode the timer will run
 * select from : normal mode (overflow)
 * 				 ctc mode (compare match)
 */
typedef enum
{
	Normal,CTC
}TIMER_Mode;


/*******************************************************************************/

/*this enum to select the prescaler for clock source
 * and every timer has its prescaler
 *
 *	 No clock source (Timer/Counter stopped).
 * 	 clkT2S/(No prescaling)
 *	 clkT2S/8 (From prescaler)
 *	 clkT2S/32 (From prescaler)
 *	 clkT2S/64 (From prescaler)
 *   clkT2S/128 (From prescaler)
 *	 clkT2S/256 (From prescaler)
 *	 clkT2S/1024 (From prescaler)
 *	 External clock source on Tn pin. Clock on falling edge.
 *	 External clock source on Tn pin. Clock on rising edge
 */
typedef enum
{
	/**********timer0**************/
	T0_No_clock,T0_No_prescaling,T0_clk_8,T0_clk_64,T0_clk_256,T0_clk_1024,T0_EX_clk_falling,T0_EX_clk_rising,

	/**********timer1*************/
	T1_No_clock=0,T1_No_prescaling,T1_clk_8,T1_clk_64,T1_clk_256,T1_clk_1024,T1_EX_clk_falling,T1_EX_clk_rising,

	/**********timer2*************/
	T2_No_clock=0,T2_No_prescaling,T2_clk_8,T2_clk_32,T2_clk_64,T2_clk_128,T2_clk_256,T2_clk_1024

}TIMER_Clock;

/***************************************************************************/

/* this enum to select which timer you will use
 * select from:timer0
 * 			  :timer1
 * 			  :timer2
 */
typedef enum
{
	TIMER0,TIMER1,TIMER2

}TIMER_Number;

/********************************************************************************/
typedef struct
{
	TIMER_Number timer_number;
	uint16 init_value; //the initial value for TCNTn
	uint16 compare_value;//the initial value for OCRn
	TIMER_Mode mode;
	TIMER_Clock clock;

}TIMER_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*[Description]:  Function to Initialize Timer Driver
 *                - Working in Interrupt Mode
 *                - Choose Timer initial value
 *                - Choose Timer_Number (TIMER0, TIMER1, TIMER2)
 *                - Choose Timer_Mode (Normal, CTC)
 *                - Choose Timer compare match value if using CTC mode
 *                - Choose Timer_Clock
 *
 * The Function return void
 *
 */


void TIMER_init( const TIMER_ConfigType *ptr);


/***********************************************************************
 * [Description]: Function to reset the timer to 0(remove any initial value).
 * 				- Choose Timer_Number (TIMER0, TIMER1, TIMER2)
 *
 *[arguments]: Choose Timer_Number (TIMER0, TIMER1, TIMER2).
 *
 *[return]: the function return void
 ***********************************************************************/
void TIMER_DeInit(TIMER_Number timer_number);



/***********************************************************************
 * [Description]: Function to set the Call Back function address.
 * 				- Choose Timer_Number (TIMER0, TIMER1, TIMER2).
 *
 *[arguments]: address of the call back function
 *			 - Choose Timer_Number (TIMER0, TIMER1, TIMER2).
 *
 *[return]: the function return void
 ***********************************************************************/
void TIMER_setCallBack(void(*a_ptr)(void),TIMER_Number timer_number);



#endif /* TIMER_H_ */
