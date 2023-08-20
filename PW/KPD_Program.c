/**************************************************************************/
/**************************************************************************/
/*****************		Author: Mahmoud Khater		***********************/
/*****************		Layer:	MCAL				***********************/
/*****************		SWC:	KPD					***********************/
/*****************		Version:1.00				***********************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_Config.h"
#include "KPD_Interface.h"
#include "KPD_private.h"

u8 Local_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY , Local_u8COLUMNIdx, Local_u8ROWIdx, Local_u8PinState;
	static u8 Local_KPDArr[ROW_NUM][COLUMN_NUM]=KPD_ARR_VAL;
	static u8 Local_u8KPDColumnArr[COLUMN_NUM]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8KPDRowArr[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};

	for(Local_u8COLUMNIdx=0;Local_u8COLUMNIdx<COLUMN_NUM;Local_u8COLUMNIdx++)
	{
		/*Activate Current Column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8COLUMNIdx],DIO_u8PIN_LOW);

		for(Local_u8ROWIdx=0;Local_u8ROWIdx<ROW_NUM;Local_u8ROWIdx++)
		{
			/*Read Current Row*/
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8ROWIdx],&Local_u8PinState);

			/*Check if Key is Pressed*/
			if (DIO_u8PIN_LOW==Local_u8PinState)
			{
				Local_u8PressedKey=Local_KPDArr[Local_u8ROWIdx][Local_u8COLUMNIdx];
				while(DIO_u8PIN_LOW==Local_u8PinState)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8ROWIdx],&Local_u8PinState);
				}
				return Local_u8PressedKey;
			}
		}
		/*Deactivate Current Column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8COLUMNIdx],DIO_u8PIN_HIGH);
	}



	return Local_u8PressedKey;
}


