/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mahmoud Khater  ***********************/
/*****************		Layer:	APP	    		***********************/
/*****************		SWC:	PASSWORD		***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "Port_Interface.h"
#include "DIO_Interface.h"

#include "KPD_Interface.h"
#include "CLCD_Interface.h"
#define F_CPU  8000000UL
#include <util/delay.h>

#define ZERO 0B11000000
#define ONE  0B11111001
#define TWO  0B10100100
#define THREE 0B10110000
#define FOUR 0B10011001
#define FIVE 0B10010010
#define SIX  0B10000010



int main (void)
{
	u8 arr[7]={SIX,FIVE,FOUR,THREE,TWO,ONE,ZERO};
	u8 Password[3];
	u8 i, Reading, flag=0, time;

	PORT_voidInit();
	CLCD_init();
	CLCD_voidGoToXY(0,1);
	CLCD_voidSendString("Welcome To");
	CLCD_voidGoToXY(1,1);
	CLCD_voidSendString("Password Check");
	_delay_ms(3000);
	CLCD_voidDisplayClear();


	CLCD_voidGoToXY(0,1);
	CLCD_voidSendString("Password:");





	while (1){
			for (i=0;i<3;i++){
				Reading =Local_u8GetPressedKey();
				if (Reading != 0xff){
				Password[i]=Reading;
				// SHIFT LCD

				CLCD_voidSendData(Password[i]);
				}
				else if (Reading == 0xff){
					i--;
				}
			}

			_delay_ms(2000);


//PASSWORD CHECK

			//Check=Password_Check(&Password[0]);

			if ((Password[0]=='1') && (Password[1]=='3') && (Password[2]=='3') ){
				CLCD_voidDisplayClear();
				_delay_ms(1000);
				CLCD_voidSendString("Password Right");
				DIO_u8SetPinValue(DIO_u8PORTA , DIO_u8PIN5 , DIO_u8PIN_HIGH);
				_delay_ms(3000);
				CLCD_voidDisplayClear();
				CLCD_voidSendString("Welcome");
				_delay_ms(3000);
				CLCD_voidDisplayClear();
				DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_HIGH);
				CLCD_voidSendString("Door Close");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("After 6 sec");

				for (time=0;time<7;time++){
					DIO_u8SetPortValue(DIO_u8PORTC,arr[time]);
					_delay_ms(1000);
				}
				DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
				CLCD_voidDisplayClear();
				CLCD_voidSendString("Password:");


		}
			else {
				CLCD_voidDisplayClear();
				_delay_ms(1000);
				CLCD_voidSendString("Password Wrong");
				flag++;
				_delay_ms(3000);
				CLCD_voidDisplayClear();

				if (flag == 2){
					CLCD_voidSendString("Last Try");
				}
				else if (flag < 2){
					CLCD_voidSendString("Try Again");
				}

				_delay_ms(3000);
				CLCD_voidDisplayClear();
				CLCD_voidSendString("Password:");


					}
			if (flag == 3){

				CLCD_voidDisplayClear();
				CLCD_voidSendString("Buzzer Alerted");
				DIO_u8SetPinValue(DIO_u8PORTA , DIO_u8PIN7 , DIO_u8PIN_HIGH);


				}

	}
	return 0;
}






