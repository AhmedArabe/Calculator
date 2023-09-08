/***********************************************************************/
/***********************************************************************/
/**************    Auther: Ahmed Arabe         *************************/
/**************    Layer: HAL                 *************************/
/**************    SWC:LCD                     *************************/
/**************    Version: 1.00               *************************/
/***********************************************************************/
/***********************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "avr/delay.h"




void HLCD_VoidInit(void)
{


#if HLCD_U8_MODE == EIGHT_BIT_MODE

	/* set Port direction output */
	DIO_u8SetPortDirection(HLCD_U8_DATA_PORT,DIO_u8_PORT_OUTPUT);
	/* RS DIR OUT*/
	DIO_u8SetPinDirection(HLCD_U8_CONTROL_PORT,HLCD_U8_RS_PIN,DIO_u8_PIN_OUTPUT);
	/* RW DIR OUT*/
	DIO_u8SetPinDirection(HLCD_U8_CONTROL_PORT,HLCD_U8_RW_PIN,DIO_u8_PIN_OUTPUT);
	/* EN DIR OUT*/
	DIO_u8SetPinDirection(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_OUTPUT);

	_delay_ms(40);

	/* function set 8_bit mode , 2-Line ,font_type 5*7 */
	HLCD_VoidSendCommand(FUNCTIONSET);
	_delay_ms(1);

	/* Display on/off control*/
	HLCD_VoidSendCommand(DISPLAYON);
	_delay_ms(1);

	/* display Clear*/
	HLCD_VoidSendCommand(DISPLAYCLEAR);
	_delay_ms(2);

	/* return to home*/
	HLCD_VoidSendCommand(0b00000010);



#elif HLCD_U8_MODE == FOUR_BIT_MODE

	DIO_u8SetPinDirection(HLCD_U8_DATA_PORT,DIO_u8_PIN7,DIO_u8_PIN_OUTPUT);
	DIO_u8SetPinDirection(HLCD_U8_DATA_PORT,DIO_u8_PIN6,DIO_u8_PIN_OUTPUT);
	DIO_u8SetPinDirection(HLCD_U8_DATA_PORT,DIO_u8_PIN5,DIO_u8_PIN_OUTPUT);
	DIO_u8SetPinDirection(HLCD_U8_DATA_PORT,DIO_u8_PIN4,DIO_u8_PIN_OUTPUT);

	/* RS DIR OUT*/
	DIO_u8SetPinDirection(HLCD_U8_CONTROL_PORT,HLCD_U8_RS_PIN,DIO_u8_PIN_OUTPUT);
	/* RW DIR OUT*/
	DIO_u8SetPinDirection(HLCD_U8_CONTROL_PORT,HLCD_U8_RW_PIN,DIO_u8_PIN_OUTPUT);
	/* EN DIR OUT*/
	DIO_u8SetPinDirection(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_OUTPUT);
	_delay_ms(40);

	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,DIO_u8_PORT_LOW);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN7,DIO_u8_PIN_HIGH);

	_delay_us(40);

	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,DIO_u8_PORT_LOW);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN7,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN6,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN4,DIO_u8_PIN_HIGH);

	_delay_us(40);
	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,DIO_u8_PORT_LOW);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN4,DIO_u8_PIN_HIGH);
	_delay_ms(2);


#endif
}

void HLCD_VoidSendChar(u8 copy_u8char)
{
	/*     RS=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_RS_PIN,DIO_u8_PIN_HIGH);
	/*     RW=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_RW_PIN,DIO_u8_PIN_LOW);
#if HLCD_U8_MODE == EIGHT_BIT_MODE

	/*     Data   */
	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,copy_u8char);

	/*     EN=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_HIGH);
	/*       delay 2ms  */
	_delay_ms(2);
	/*     EN=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_LOW);
	/*       delay 2ms  */
	_delay_ms(2);

#elif HLCD_U8_MODE == FOUR_BIT_MODE
	/*	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN7,(copy_u8char>>7)&1);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN6,(copy_u8char>>6)&1);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,(copy_u8char>>5)&1);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN4,(copy_u8char>>4)&1);
	_delay_ms(2);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN7,(copy_u8char>>3)&1);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN6,(copy_u8char>>2)&1);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,(copy_u8char>>1)&1);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN4,(copy_u8char>>0)&1);
	 */

	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,(copy_u8char<<4)&0xf0);

	/*     EN=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_HIGH);
	/*       delay 2ms  */
	_delay_ms(2);
	/*     EN=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_LOW);
	/*       delay 2ms  */
	_delay_ms(2);

	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,copy_u8char&0xf0);

	/*     EN=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_HIGH);
	/*       delay 2ms  */
	_delay_ms(2);
	/*     EN=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_LOW);
	/*       delay 2ms  */
	_delay_ms(2);




#endif




}



void HLCD_VoidSendCommand(u8 copy_u8command)

{
	/*     RS=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_RS_PIN,DIO_u8_PIN_LOW);
	/*     RW=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_RW_PIN,DIO_u8_PIN_LOW);

#if HLCD_U8_MODE == EIGHT_BIT_MODE

	/*     Command   */
	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,copy_u8command);

	/*     EN=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_HIGH);
	/*       delay 2ms  */
	_delay_ms(2);
	/*     EN=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_LOW);
	/*       delay 2ms  */
	_delay_ms(2);

#elif HLCD_U8_MODE == FOUR_BIT_MODE

	/*	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN7,((copy_u8command>>7)&1));
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN6,((copy_u8command>>6)&1));
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,((copy_u8command>>5)&1));
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN4,((copy_u8command>>4)&1));
	_delay_ms(2);
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN7,((copy_u8command>>3)&1));
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN6,((copy_u8command>>2)&1));
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN5,((copy_u8command>>1)&1));
	DIO_u8SetPinValue(HLCD_U8_DATA_PORT,DIO_u8_PIN4,((copy_u8command>>0)&1));
	 */

	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,(copy_u8command<<4)&0xf0);

	/*     EN=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_HIGH);
	/*       delay 2ms  */
	_delay_ms(2);
	/*     EN=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_LOW);
	/*       delay 2ms  */
	_delay_ms(2);

	DIO_u8SetPortValue(HLCD_U8_DATA_PORT,(copy_u8command&0xf0));

	/*     EN=1   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_HIGH);
	/*       delay 2ms  */
	_delay_ms(2);
	/*     EN=0   */
	DIO_u8SetPinValue(HLCD_U8_CONTROL_PORT,HLCD_U8_EN_PIN,DIO_u8_PIN_LOW);
	/*       delay 2ms  */
	_delay_ms(2);







#endif


}


void HLCD_VoidSendString(u8 copy_u8Char[])
{
	u8 i=0;
	while(copy_u8Char[i]!='\0')
	{
		HLCD_VoidSendChar(copy_u8Char[i]);
		i++;
	}
}



void HLCD_VoidSendNumber(u32 copy_u8Char)
{
	if(copy_u8Char ==0)
	{
		HLCD_VoidSendChar(copy_u8Char+'0');

	}
	u32  Local_u8_revers_number =1;
	while(copy_u8Char>0)
	{
		Local_u8_revers_number = (Local_u8_revers_number*10) + (copy_u8Char%10);
		copy_u8Char = copy_u8Char/10;
	}
	while(Local_u8_revers_number>1)
	{
		copy_u8Char=Local_u8_revers_number%10;
		Local_u8_revers_number=Local_u8_revers_number/10;
		HLCD_VoidSendChar(copy_u8Char+'0');

	}

}






void HLCD_VoidGotoXY(u8 copy_u8RowPos ,u8 copy_u8ColPos)
{
	if(copy_u8RowPos ==0)
	{
		HLCD_VoidSendCommand(copy_u8ColPos+128);

	}
	else if(copy_u8RowPos ==1)
	{
		HLCD_VoidSendCommand(copy_u8ColPos+128+64);

	}

}




u8 HLCD_VoidDraw(u8 *copy_u8char, u8 copy_u8Location,u8 copy_u8Xpos ,u8 copy_u8Ypos)
{
	u8 Local_u8ErrorState=0;

	if(copy_u8Location >=0 && copy_u8Location <=7 )
	{
		u8 i=0;
		HLCD_VoidSendCommand(64+8*(copy_u8Location));  //address 0 of  location 0 of CG_Ram
		for(i=0;i<8;i++)
		{
			HLCD_VoidSendChar(copy_u8char[i]);

		}
		HLCD_VoidSendCommand(0b10000000);//address 0 of DD_Ram
		HLCD_VoidGotoXY(copy_u8Xpos,copy_u8Ypos);
		HLCD_VoidSendChar(copy_u8Location); //address location 0 of CG_Ram
	}
	else
	{
		Local_u8ErrorState=1;

	}
	return Local_u8ErrorState;
}




