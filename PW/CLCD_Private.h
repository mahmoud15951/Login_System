/**********************************************************************/
/**********************************************************************/
/*****************	Author: Mahmoud Khater  	***********************/
/*****************		Layer:	HAL	    		***********************/
/*****************		SWC:	LCD 			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

#define LCD_u8_CLR_DISPLAY 	    0b00000001
#define LCD_u8_FUNCTION_SET     0b00111100
#define LCD_u8_DISPLAY_CONTROL  0b00001100
#define LCD_u8_ENTRY_MODE 		0b00000010



#define LCD_u8_POSITION         0b10000000
#define LCD_u8_ROW1Address      128          // 0b1 000 0000
#define LCD_u8_ROW2Address      192          // 0b1 100 0000

#define LCD_u8_Row1       1
#define LCD_u8_Row2       2

#define LCD_u8_Column1    1
#define LCD_u8_Column16   16

#endif /* CLCD_PRIVATE_H_ */
