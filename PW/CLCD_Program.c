/**********************************************************************/
/**********************************************************************/
/*****************	Author: Mahmoud Khater  	***********************/
/*****************		Layer:	HAL	    		***********************/
/*****************		SWC:	LCD 			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/

		/*Library*/
#include "util/delay.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

		/* MCAL */
#include "DIO_interface.h"

		 /*HAL*/
#include "CLCD_Config.h"
#include "CLCD_Interface.h"
#include "CLCD_Private.h"

/*Send commands*/
void CLCD_voidSendCommand(u8 Copy_u8Command)
{
		/*set RS pin low*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
		/*set RW pin LOW*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
		/*Command*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

		/*enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}

/*Send Data*/
void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*HIGH for send data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	/*set RW pin LOW*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
		/*Send Data For PINS*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

		/*enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}

/*Initialization*/
void CLCD_init(void)
{
	/*Wait for more than 30ms */
	_delay_ms(40);

	/*Function Set Command : 2 Lines, 8*5 Font size*/
	CLCD_voidSendCommand(0b00111000);

	/*Display on/off control:	display enable , disable cursor , no blink cursor*/
	CLCD_voidSendCommand(0b00001100);

	/*Clear Display*/
	CLCD_voidSendCommand(1);
	_delay_ms(2);

	/*Initialize LCD Pins Direction*/
	DIO_u8SetPortDirection(CLCD_DATA_PORT,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PORT_OUTPUT);
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	s8 i=0;
	while(Copy_pcString[i]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[i]);
		i++;
	}
}

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if (Copy_u8XPos==0)
	{
		Local_u8Address=Copy_u8YPos;
	}
	else if (Copy_u8XPos==1)
	{
		Local_u8Address=0x40 + Copy_u8YPos;
	}
	CLCD_voidSendCommand(Local_u8Address+128);
}

void CLCD_voidSendSpecialChar(u8 *Copy_pu8Pattern, u8 Copy_u8PatternNumber ,u8 Copy_u8XPos ,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress=0,Local_u8Iterator;

	/*calculate CGRAM Address Whose each block equal 8 bytes*/
	Local_u8CGRAMAddress =Copy_u8PatternNumber;

	/*Send CGRAM Address command to LCD, with setting bit 6, clearing bit 7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/*Write the pattern into CGRAM*/
	for (Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	/*Go back to the DDRAM to display the Pattern*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*Display the pattern written in CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}

void CLCD_voidDisplayClear(void)
{
	CLCD_voidSendCommand(LCD_u8_CLR_DISPLAY);
}
