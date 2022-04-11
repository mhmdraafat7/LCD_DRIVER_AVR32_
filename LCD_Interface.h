/*
 * LCD_Interface.h
 *
 *  Created on: Apr 5, 2022
 *      Author: mhmdr
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LCD_Config.h"

void LCD_Init(void);
void LCD_WriteCommand( uint8 cmd);
void LCD_WriteChar(uint8 character);
void LCD_WriteString(uint8 *Ptr_character);
void LCD_Goto (uint8 row, uint8 col);
void LCD_Clear(void);
void LCD_WriteInterger(sint32 intgr);
void LCD_PrintCustomChar (uint8 CGRAM_index, uint8 row, uint8 col);
void LCD_StoreCustomChar (uint8* pattern , uint8 CGRAM_index);


#endif /* LCD_INTERFACE_H_ */
