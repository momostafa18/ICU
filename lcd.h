/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mohamed Mostafa
 *******************************************************************************************/

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LCD_DATA_BITS_MODE  8

#if((LCD_DATA_BITS_MODE!=4) && (LCD_DATA_BITS_MODE!=8))
#error "Number of Data bits should be equal to 4 or 8"
#endif

#define LCD_RS_PORT_ID      PORTD_ID
#define LCD_RS_PIN_ID       PIN4_ID
/*
#define LCD_RW_PORT_ID
#define LCD_RW_PORT_ID
*/
#define LCD_EN_PORT_ID      PORTD_ID
#define LCD_EN_PIN_ID       PIN5_ID

#define LCD_DATA_PORT_ID    PORTC_ID

#if(LCD_DATA_BITS_MODE==4)

#define LCD_DB4_PIN_ID      PIN3_ID
#define LCD_DB5_PIN_ID      PIN4_ID
#define LCD_DB6_PIN_ID      PIN5_ID
#define LCD_DB7_PIN_ID      PIN6_ID

#endif



/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 *Description:Initialize of LCD
 1.SETUP Pin directions (RS,EN,Data pins)
 2.SETUP LCD for 4 bit or 8 bit mode
*/
void LCD_init(void);
/*
 *Description:Sending command to the LCD
 1.Making RS=0
 2.Enabling the LCD and send the command then disabling it.
*/
void LCD_sendCommand(uint8 command);
/*
 *Description:Displaying one character on the LCD
 1.Making RS=1
 2.Enabling the LCD and send the command then disabling it.
*/
void LCD_displayCharacter(uint8 character);
/*
 *Description:Displaying string on the LCD
 1.Pointer to char are used to display string
*/
void LCD_displayString(uint8 *character);
/*
 *Description:Moving cursor to a specific position
*/
void LCD_moveCursor(uint8 row,uint8 cloumn);
/*
 *Description:Clearing screen of the LCD
*/
void LCD_clearScreen(void);
/*
 *Description:Displaying a string in a specific position
*/
void LCD_displayStringRowColumn(uint8 row,uint8 cloumn, uint8 *string);
/*
 *Description:Converting integer to string to display it
 1.we use the function (itoa)--> integer to ASCII to get the ascii of the number and send it to the LCD
*/
void LCD_integerToString(int data);

#endif /* LCD_H_ */
