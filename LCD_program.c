/*
 * LCD_program.c
 *
 *  Created on: Apr 5, 2022
 *      Author: mhmdr
 */

#include "LCD_Interface.h"
#define F_CPU 8000000U
#include <util/delay.h>

void LCD_Init(void)
{
	#if 		LCD_Mode == LCD_8BIT_MODE

	DIO_SetPinDir(LCD_Command_Port,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Command_Port,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Command_Port,LCD_E_PIN,DIO_PIN_OUTPUT);

	DIO_SetPortDir(LCD_Data_Port,DIO_PORT_OUTPUT);
	_delay_ms(100);

	LCD_WriteCommand(0x38); /*command to set the lcd in 8bit mode*/
	LCD_WriteCommand(0x0E); /*cursor blinking command*/
	LCD_WriteCommand(0x01); /*clear lcd command*/
	LCD_WriteCommand(0x06); /*shift cursor right command*/
	LCD_WriteCommand(0x02); /*start from home(0,0) command*/
	_delay_ms(5);

	#elif		LCD_Mode == LCD_4BIT_MODE
	DIO_SetPinDir(LCD_Command_Port,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Command_Port,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Command_Port,LCD_E_PIN,DIO_PIN_OUTPUT);

	DIO_SetPinDir(LCD_Data_Port,LCD_D7,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Data_Port,LCD_D6,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Data_Port,LCD_D5,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_Data_Port,LCD_D4,DIO_PIN_OUTPUT);
	_delay_ms(100);

	LCD_WriteCommand(0x33); /***********************************************/
	LCD_WriteCommand(0x32); /*list of commands to set the lcd in 4bit mode */
	LCD_WriteCommand(0x28); /***********************************************/

	LCD_WriteCommand(0x0E); /*cursor blinking command*/
	LCD_WriteCommand(0x01); /*clear lcd command*/
	LCD_WriteCommand(0x06); /*shift cursor right command*/
	LCD_WriteCommand(0x02); /*start from home(0,0) command*/
	_delay_ms(5);

	#endif
}

void LCD_WriteCommand( uint8 cmd)
{
	DIO_SetPinVal(LCD_Command_Port,LCD_RS_PIN,DIO_PIN_LOW);
	DIO_SetPinVal(LCD_Command_Port,LCD_RW_PIN,DIO_PIN_LOW);
	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

	#if 		LCD_Mode == LCD_8BIT_MODE

	DIO_SetPortVal(LCD_Data_Port,cmd);

	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

	#elif		LCD_Mode == LCD_4BIT_MODE

	DIO_SetPortVal(LCD_Data_Port,((cmd & 0xF0)|(LCD_Data_Port & 0x0F)));

	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

	DIO_SetPortVal(LCD_Data_Port,((cmd << 4)|(LCD_Data_Port & 0x0F)));

	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

	#endif

	_delay_ms(5);

}

void LCD_WriteChar(uint8 character)
{
		DIO_SetPinVal(LCD_Command_Port,LCD_RS_PIN,DIO_PIN_HIGH);
		DIO_SetPinVal(LCD_Command_Port,LCD_RW_PIN,DIO_PIN_LOW);
		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

		#if 		LCD_Mode == LCD_8BIT_MODE

		DIO_SetPortVal(LCD_Data_Port,character);

		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

		#elif		LCD_Mode == LCD_4BIT_MODE

		DIO_SetPortVal(LCD_Data_Port,((character & 0xF0)|(LCD_Data_Port & 0x0F)));

		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

		DIO_SetPortVal(LCD_Data_Port,((character << 4)|(LCD_Data_Port & 0x0F)));

		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_SetPinVal(LCD_Command_Port,LCD_E_PIN ,DIO_PIN_LOW);

		#endif

		_delay_ms(5);


}

void LCD_WriteString(uint8 *str)
{
	uint8 counter=0;
	while(str[counter] != '\0')
	{
		LCD_WriteChar(str[counter]);
		counter++;
	}

}

void LCD_Goto (uint8 row, uint8 col)
{
	uint8 postion[2]={0x80,0xC0};
	LCD_WriteCommand(postion[row]+col);

}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01); /*clear lcd command*/
}

void LCD_WriteInterger(sint32 intgr)
{
	sint32 y=1;

		if(intgr < 0)
		{
			LCD_WriteChar('-');
			intgr *= -1;
		}

		while (intgr > 0)
		{
			y = ((y*10) + (intgr%10));
			intgr /=10;
		}

		while (y>1)
		{
			LCD_WriteChar((y%10)+48);
			y/=10;
		}
}

void LCD_StoreCustomChar (uint8* pattern ,uint8 CGRAM_index)
{

	uint8 address;
	uint8 index;

	if (CGRAM_index < 8)
	{
	address = CGRAM_index *8;

	address = SET_BIT(address,6);
	LCD_WriteCommand(address);
	for(index=0 ; index <8 ;index++)
	{
	LCD_WriteChar(pattern[index]);
	}
	}
	LCD_WriteCommand(0x02);
}

void LCD_PrintCustomChar (uint8 CGRAM_index,uint8 row, uint8 col)
{
LCD_Goto(row,col);
LCD_WriteChar(CGRAM_index);

}
