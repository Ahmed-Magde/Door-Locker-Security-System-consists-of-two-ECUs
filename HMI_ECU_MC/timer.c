/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Header file for the TIMER driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>




/*global pointer to function to store address
 * because the a_ptr in the call back function is local
 * it will pop from stack in the TIMER_setCallBack function
 */
static  void(*g_timer0_ptr)(void)=NULL_PTR;
static  void(*g_timer1_ptr)(void)=NULL_PTR;
static  void(*g_timer2_ptr)(void)=NULL_PTR;



/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/


/*******************************************************************************
 *                       ISR FOR TIMER0                         			   *
 *******************************************************************************/

//Normal Mode
ISR(TIMER0_OVF_vect)
{
	//to make sure that g_timer0_ptr contain the function address

	if(g_timer0_ptr!=NULL_PTR)
	{
		(*g_timer0_ptr)();
	}

}

//CTC Mode
ISR(TIMER0_COMP_vect)
{
	//to make sure that g_timer0_ptr contain the function address

	if(g_timer0_ptr!=NULL_PTR)
	{
		(*g_timer0_ptr)();
	}

}


/*******************************************************************************
 *                       ISR FOR TIMER1                          *
 *******************************************************************************/

//Normal Mode
ISR(TIMER1_OVF_vect)
{
	//to make sure that g_timer1_ptr contain the function address

	if(g_timer1_ptr!=NULL_PTR)
	{
		(*g_timer1_ptr)();
	}

}

//CTC Mode
ISR(TIMER1_COMPA_vect)
{
	//to make sure that g_timer1_ptr contain the function address

	if(g_timer1_ptr!=NULL_PTR)
	{
		(*g_timer1_ptr)();
	}

}




/*******************************************************************************
 *                       ISR FOR TIMER2                          *
 *******************************************************************************/

//Normal Mode
ISR(TIMER2_OVF_vect)
{
	//to make sure that g_timer2_ptr contain the function address

	if(g_timer2_ptr!=NULL_PTR)
	{
		(*g_timer2_ptr)();
	}

}


//CTC Mode
ISR(TIMER2_COMP_vect)
{
	//to make sure that g_timer2_ptr contain the function address

	if(g_timer2_ptr!=NULL_PTR)
	{
		(*g_timer2_ptr)();
	}

}



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/




void TIMER_init( const TIMER_ConfigType *ptr)
{

	switch(ptr->timer_number)
	{

	case TIMER0:

		/**************** TIMER0 initialization *****************/

		TIMER_DeInit(TIMER0);// to make sure the timer registers write by zero

		switch(ptr->mode)//select timer mode
		{
		case Normal:

			TCCR0 |=(1<<FOC0);//The FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode


			/* Configure the timer control register
			 * 1. Non PWM mode FOC0=1
			 * 2. Normal Mode WGM01=0 & WGM00=0
			 * 3. Normal Mode COM00=0 & COM01=0
			 * 4. clock = entered clock
			 */
			TCCR0 =(TCCR0 & 0XF8) | ((ptr->clock) & 0x07);

			TCNT0 = (ptr->init_value);   //Set Timer initial value to init_value

			TIMSK |=(1<<TOIE0); // Enable Timer0 Overflow Interrupt

			break;

		case CTC:

			TCCR0 |=(1<<FOC0);/*The FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode*/

			/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. No need for OC0 in this example so COM00=0 & COM01=0
			 * 4. clock = F_CPU/clock CS00,CS01,CS02
			 */
			TCCR0 |=(1<<WGM01);

			TCCR0 =(TCCR0 & 0XF8) | ((ptr->clock) & 0x07);

			OCR0 = (ptr->compare_value);   // Set Compare Value to compare_value

			TCNT0 = (ptr->init_value);    //Set Timer initial value to init_value

			TIMSK |=(1<<OCIE0);    // Enable Timer0 Compare Interrupt

			break;
		}//mode_select for timer0 end

		break;

		case TIMER1:

			/**************** TIMER1 initialization *****************/

			TIMER_DeInit(TIMER1);// to make sure the timer registers write by zero

			switch(ptr->mode)//select timer mode
			{
			case Normal:

				/* Configure the timer control register
				 * 1. Non PWM mode FOC1A=1
				 * 2. Normal Mode  WGM12=0  & WGM11=0 & WGM10=0
				 * 3. Normal Mode COM1A1/COM1B1 COM1A0/COM1B0
				 * 4. clock = entered clock
				 */

				TCCR1A |=(1<<FOC1A) ;
				TCCR1B =(TCCR1B & 0XF8) | ((ptr->clock) & 0x07);
				TCNT1 =(ptr->init_value);  /* Set timer1 initial count to init_value */
				TIMSK |=(1<<TOIE1);   /* Enable Timer1 overflow A Interrupt */

				break;

			case CTC:

				/*FOC1A:The FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode.*/
				TCCR1A |=(1<<FOC1A);
				/* Configure timer1 control register
				 * 1. Non PWM mode FOC1A=1
				 * 2. CTC Mode WGM12=1  & WGM11=0 & WGM10=0
				 * 3. No need for OC1A in
				 * 4. clock = F_CPU/clock CS10,CS11,CS12
				 */
				TCCR1B |=(1<<WGM12);
				TCCR1B =(TCCR1B & 0XF8) | ((ptr->clock) & 0x07);
				TCNT1 =(ptr->init_value);
				OCR1A =(ptr->compare_value);  /* Set the Compare value to compare_value*/
				TIMSK |=(1<<OCIE1A);   /* Enable Timer1 Compare A Interrupt */

				break;
			}//mode_select for timer0 end

			break;

			case TIMER2:

				/**************** TIMER2 initialization *****************/

				TIMER_DeInit(TIMER2);// to make sure the timer registers write by zero

				switch(ptr->mode)//select timer mode
				{
				case Normal:

					TCCR2 |=(1<<FOC2);/*The FOC2 bit is only active when the WGM20 bit specifies a non-PWM mode*/

					/* Configure the timer control register
					 * 1. Non PWM mode FOC2=1
					 * 2. Normal Mode WGM21=0 & WGM20=0
					 * 3. Normal Mode COM20=0 & COM21=0
					 * 4. clock = entered clock
					 */
					TCCR2 =(TCCR2 & 0XF8) | ((ptr->clock) & 0x07);

					TCNT2 = (ptr->init_value);   //Set Timer initial value to init_value

					TIMSK |=(1<<TOIE2); // Enable Timer2 Overflow Interrupt

					break;

				case CTC:

					TCCR2 |=(1<<FOC2);/*The FOC2 bit is only active when the WGM20 bit specifies a non-PWM mode*/

					/* Configure timer2 control register
					 * 1. Non PWM mode FOC2=1
					 * 2. CTC Mode WGM21=1 & WGM20=0
					 * 3. No need for OC2 in this example so COM20=0 & COM21=0
					 * 4. clock = F_CPU/clock CS00 CS01 CS02
					 */
					TCCR2 |=(1<<WGM21);

					TCCR2 =(TCCR2 & 0XF8) | ((ptr->clock) & 0x07);

					OCR2 = (ptr->compare_value);   // Set Compare Value to compare_value

					TCNT2 = (ptr->init_value);    //Set Timer initial value to init_value

					TIMSK |=(1<<OCIE2);    // Enable Timer2 Compare Interrupt

					break;
				}//mode_select for timer0 end

				break;

	}//timer_number select end

}//timer initialization end


/*
 * Description: Function to reset the timer to 0.
 */
void TIMER_DeInit(TIMER_Number timer_number)
{
	switch(timer_number)//select timer (TIMER0,TIMER1,TIMER2)
	{
	case TIMER0:

		TCCR0 &= 0;//set Timer/Counter Control Register to zero.
		TCNT0 &= 0;//set Timer/Counter Register to zero.
		TIMSK &= ~(1<<TOIE0);//set Timer/Counter0 Overflow Interrupt Enable to zero.
		TIMSK &= ~(1<<OCIE0);//set : Timer/Counter0 Output Compare Match Interrupt Enable to zero.
		OCR0 &= 0;//set Output Compare Register to zero.

		break;
	case TIMER1:

		TCCR1A &= 0;//set Timer/Counter Control Register A to zero.
		TCCR1B &= 0;//set Timer/Counter Control Register B to zero.
		TCNT1 &= 0;//set Timer/Counter Register to zero.
		OCR1A &= 0;//set Output Compare Register A to zero.
		TIMSK &= ~(1<<TOIE1);//set Timer/Counter1 Overflow Interrupt Enable to zero.
		TIMSK &= ~(1<<OCIE1A);//set  Timer/Counter1 Output Compare Match A Interrupt Enable to zero.

		break;

	case TIMER2:

		TCCR2 &= 0;//set Timer/Counter Control Register to zero.
		TCNT2 &= 0;//set Timer/Counter Register to zero.
		TIMSK &=~(1<<TOIE2);//set Timer/Counter2 Overflow Interrupt Enable to zero.
		TIMSK &=~(1<<OCIE2);//set : Timer/Counter2 Output Compare Match Interrupt Enable to zero.
		OCR2 &= 0;//set Output Compare Register to zero.

		break;
	}
}



/*
 * Description: Function to set the Call Back function address.
 */
void TIMER_setCallBack(void(*a_ptr)(void),TIMER_Number timer_number)
{
	switch(timer_number)//select timer (TIMER0,TIMER1,TIMER2)
	{
	case TIMER0:
		/*
		 *put the address in the global pointer
		 *because the a_ptr is local it will pop from stack
		 */
		g_timer0_ptr = a_ptr;

		break;
	case TIMER1:
		/*
		 *put the address in the global pointer
		 *because the a_ptr is local it will pop from stack
		 */
		g_timer1_ptr = a_ptr;

		break;

	case TIMER2:
		/*
		 *put the address in the global pointer
		 *because the a_ptr is local it will pop from stack
		 */
		g_timer2_ptr = a_ptr;

		break;
	}
}
