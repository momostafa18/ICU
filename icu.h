/*
 * icu.h
 *
 *  Created on: Oct 4, 2022
 *      Author: mohamedmostafamohame
 */

#ifndef ICU_H_
#define ICU_H_
#include"std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	F_CPU_NO_CLOCK,F_CPU_CLOCK_1,F_CPU_CLOCK_8,F_CPU_CLOCK_64,F_CPU_CLOCK_256,F_CPU_CLOCK_1024
}ICU_CLOCK;
typedef enum
{
	FALLING,RISING
}ICU_EDGETYPE;
typedef struct
{
	ICU_EDGETYPE edge;
	ICU_CLOCK clock;
}ICU_CONFIG;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void Icu_init(ICU_CONFIG(*config_ptr));
/*
 * Description: Function to set the Call Back function address.
 */
void Icu_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(ICU_EDGETYPE edge);
/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void);
/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void);
/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_deinit();

#endif /* ICU_H_ */
