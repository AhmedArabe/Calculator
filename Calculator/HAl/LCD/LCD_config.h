/***********************************************************************/
/***********************************************************************/
/**************    Auther: Ahmed Arabe         *************************/
/**************    Layer: HAL                 *************************/
/**************    SWC:LCD                     *************************/
/**************    Version: 1.00               *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_



#define HLCD_U8_DATA_PORT   		DIO_u8_PORTA

#define HLCD_U8_CONTROL_PORT  		DIO_u8_PORTB
#define HLCD_U8_RS_PIN   			DIO_u8_PIN0
#define HLCD_U8_RW_PIN				DIO_u8_PIN1
#define HLCD_U8_EN_PIN				DIO_u8_PIN2


#define EIGHT_BIT_MODE   8
#define FOUR_BIT_MODE    4

#define  HLCD_U8_MODE 	EIGHT_BIT_MODE



#endif
