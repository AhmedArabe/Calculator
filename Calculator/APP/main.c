/*
 * main.c
 *
 *  Created on: Oct 27, 2021
 *      Author: ahmed17039
 */


#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"
#include  "../HAl/key_pad/KPD_Interface.h"
#include "../HAl/LCD/LCD_interface.h"
#include "Function.h"

void main(void)
{
	u8 num1=0;
	u8 num2=0;
	u8 flag=0;
	u8 opertion=0;
	u8 Local_u8Key;
	HLCD_VoidInit();
	while(1)
	{

		do
		{
			Local_u8Key=KPD_u8GetPressedKey();
		}while(Local_u8Key==0xff);

		switch (Local_u8Key)
		{
		case '/' :   HLCD_VoidSendChar('/');  opertion=4; flag=1;   break;
		case '*' :   HLCD_VoidSendChar('*');  opertion=3; flag=1;   break;
		case '-' :   HLCD_VoidSendChar('-');  opertion=2; flag=1;   break;
		case '+' :   HLCD_VoidSendChar('+');  opertion=1; flag=1;   break;
		case '=' :   HLCD_VoidSendChar('=');   flag=0;

		            calculation(num1,num2,opertion);


	    break;

		case '$' :  HLCD_VoidSendCommand(DISPLAYCLEAR);

					num1=num2=0;
					opertion=0;
		break;
		default :   HLCD_VoidSendNumber(Local_u8Key);
					if(flag==0)
					{

						num1=num1*10+Local_u8Key;
					}else if(flag==1)
					{

						num2=num2*10+Local_u8Key;
					}

		break;

		}


	}

}

