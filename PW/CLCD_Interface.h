/**********************************************************************/
/**********************************************************************/
/*****************	Author: Mahmoud Khater  	***********************/
/*****************		Layer:	HAL	    		***********************/
/*****************		SWC:	LCD 			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


/*Send commands*/
void CLCD_voidSendCommand(u8 Copy_u8Command);


/*Send Data*/
void CLCD_voidSendData(u8 Copy_u8Data);

/*Initialization*/
void CLCD_init(void);

/*Send Strings*/
void CLCD_voidSendString(const char* Copy_pcString);

/*Position Control*/
void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);

/*Send Pattern to LCD*/
void CLCD_voidSendSpecialChar(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber ,u8 Copy_u8XPos ,u8 Copy_u8YPos);

/*Clear Display*/
void CLCD_voidDisplayClear(void);


#endif /* CLCD_INTERFACE_H_ */
