#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"


void calculation(u8 num1,u8 num2,u8 opertion)
{
	if(opertion ==1)  // +
	{

		HLCD_VoidSendNumber(num1+num2);
	}
	else if(opertion==2) // -
	{

		HLCD_VoidSendNumber(num1-num2);

	}
	else if(opertion==3) //*
	{
		HLCD_VoidSendNumber(num1*num2);

	}
	else  if(opertion) //*
	{
		if(num2==0)
		{

			HLCD_VoidSendCommand(0b00000001);         //Clear Screen
			HLCD_VoidSendString("Invalid Operation\n");
		}
		else
		{
			HLCD_VoidSendNumber(num1/num2);
		}
	}

}

