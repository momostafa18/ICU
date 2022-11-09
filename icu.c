/*
 * icu.c
 *
 *  Created on: Oct 4, 2022
 *      Author: mohamedmostafamohame
 */

#include"icu.h"
#include"gpio.h"
#include<avr/io.h>
#include"common_macros.h"
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the address of the call back function in the application */
static volatile void(*g_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers.
 */
void Icu_init(ICU_CONFIG(*config_ptr))
{
	/* Setting PD6 as input pin (PD6 is the input capture pin) */
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,PIN_INPUT);
	/* Setting timer on normal mode */
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	/* Getting the required clock */
	TCCR1B=(TCCR1B & 0xF8) | ((config_ptr->clock));
	/* Getting the required edge */
	TCCR1B=(TCCR1B & 0xBF) | ((config_ptr->edge)<<6);
    /* Initial value for the timer to start counting from the 0*/
	TCNT1=0;
	/* Initial value for the Input Capture Register*/
	ICR1=0;
	/* Enable the Input Capture Interrupt*/
	SET_BIT(TIMSK,TICIE1);
}
/*
 * Description: Function to set the Call Back function address.
 */
void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr=a_ptr;
}
/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(ICU_EDGETYPE a_edgeType)
{
	TCCR1B=(TCCR1B & 0xBF) | (a_edgeType<<6);
}
/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}
/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void)
{
	TCNT1=0;
}
/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_deinit()
{
	/* Clear All Timer1 Registers */
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;
	/* Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK,TICIE1);
}
