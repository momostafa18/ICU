/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mohamed Mostafa
 *******************************************************************************************/
#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include "common_macros.h"
#include<stdlib.h>

void LCD_init(void)
{
	/*Setup for the pin direction of RS and Enable pins as output*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_EN_PORT_ID,LCD_EN_PIN_ID,PIN_OUTPUT);

	_delay_ms(20); /*Delaying for 20ms because the LCD power on in 15ms  */
#if(LCD_DATA_BITS_MODE == 4)

	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	/*Setup for the Data port as output*/
    GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
		/*Initialization of 8_bit LCD (Depends on each LCD Where every one has it's own way)*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /*RS=0 for sending Command*/
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_HIGH);/*E=1 for enabling with LCD*/
	_delay_ms(1);
#if(LCD_DATA_BITS_MODE == 4)
	/* since we are dealing with 4 bit mode we have to send the command twice so we send first
	 the LSB which are form 7 to 4 after this immediately you have to disable the LCD to allow
	 the data sent to pass by the buffer then we send the MSB  */
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_HIGH);/*E=0 for disabling with LCD*/
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));
#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command);/*Sending Command*/
	_delay_ms(1);
#endif
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_LOW);/*E=0 for disabling the LCD*/
	_delay_ms(1);
}
void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /*RS=1 for sending Data*/
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_HIGH);/*E=1 for dealing with LCD*/
	_delay_ms(1);
#if(LCD_DATA_BITS_MODE == 4)
	/* since we are dealing with 4 bit mode we have to send the command twice so we send first
	 the LSB which are form 7 to 4 after this immediatly you have to disable the LCD to allow
	 the data sent to pass by the buffer then we send the MSB  */
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,7));

	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_HIGH);/*E=0 for disabling with LCD*/
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));
#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,character);/*Sending Command*/
	_delay_ms(1);
#endif
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOGIC_LOW);/*E=0 for disabling the LCD*/
	_delay_ms(1);
}
void LCD_displayString(uint8 *character)
{
	while((*character) !='\0')
	{
		LCD_displayCharacter(*character);
		character++;
	}

}
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
void LCD_moveCursor(uint8 row,uint8 cloumn)
{
	uint8 LCD_memoryAddress;
	/*The logic of this is the number of the khana is the number of the column fadel bs eny adeef 3aleh rakm
	 elrow bs fbgm3 kol shwya qemet elrow 3ala elcolumn wab3tha*/
	switch(row)
	{
	case 0:
		LCD_memoryAddress=cloumn;
		break;
	case 1:
		LCD_memoryAddress=cloumn+0x40;
		break;
	case 2:
		LCD_memoryAddress=cloumn+0x10;
		break;
	case 3:
		LCD_memoryAddress=cloumn+0x50;
		break;
	}
	LCD_sendCommand(LCD_memoryAddress|LCD_SET_CURSOR_LOCATION);
}
void LCD_integerToString(int data)
{
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}
void LCD_displayStringRowColumn(uint8 row, uint8 column , uint8 *string)
{
	LCD_moveCursor(row,column);
	LCD_displayString(string);
}


