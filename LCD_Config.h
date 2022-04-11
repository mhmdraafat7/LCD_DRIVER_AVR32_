/*
 * LCD_Config.h
 *
 *  Created on: Apr 5, 2022
 *      Author: mhmdr
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/**********************************************************************/
/*                          include DIO to use it's variables         */
/**********************************************************************/
#include "../DIO/DIO_Interface.h"


/**********************************************************************/
/*                          LCD configurations                        */
/**********************************************************************/


#define LCD_4BIT_MODE  4 /*MACRO TO DEFINE 4bit MODE*/
#define LCD_8BIT_MODE  8/*MACRO TO DEFINE 8bit MODE*/

#define LCD_Mode				LCD_4BIT_MODE  /*MACRO TO SELECT LCD MODE 4 OR 8*/


#define LCD_Data_Port 			DIO_PORTA

#define LCD_Command_Port 		DIO_PORTB

#define LCD_RS_PIN          	DIO_PIN1
#define LCD_RW_PIN          	DIO_PIN2
#define LCD_E_PIN   			DIO_PIN3

#define LCD_D7					DIO_PIN7
#define LCD_D6					DIO_PIN6
#define LCD_D5					DIO_PIN5
#define LCD_D4					DIO_PIN4
#define LCD_D3					DIO_PIN3
#define LCD_D2					DIO_PIN2
#define LCD_D1					DIO_PIN1
#define LCD_D0					DIO_PIN0



#endif /* LCD_CONFIG_H_ */
