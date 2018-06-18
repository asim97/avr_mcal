/*! \file DIO.c \brief Digital Input/Output peripheral driver. */
/**********************************************************************************************************
*
* File Name		: 'DIO.c'
* Title			: Digital Input/Output peripheral driver
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/8/2018 9:36:19 PM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved 
*
************************************************************************************************************/


/*--------------------------------------------- INCLUDES --------------------------------------------------*/

#include "DIO.h"


/*----------------------------------------- MACROS Definitions --------------------------------------------*/

/*------------------------------------------ Global Variables ---------------------------------------------*/

/*---------------------------------------- FUNCTION Definitions -------------------------------------------*/

/************************************************************************************************************
* Function				: DIO_vidSetPinMode
* Description			: Digital pin in/out mode select.
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
							Range : see PIN MAP macros defined on top of "DIO.h" file
							[u8Mode] desired mode (Input/Output) for selected pin
							Range : (INPUT, OUTPUT, or INPUT_PULLUP)
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void	DIO_vidSetPinMode(uint8 u8Pin, uint8 u8Mode)
{	if(u8Mode==INPUT || u8Mode==OUTPUT)	{
		if(u8Pin >= DIO_PB0 && u8Pin <= DIO_PB7){
			WRITE_BIT_VAL(DDRB, u8Pin, u8Mode);			
		} else if(u8Pin >= DIO_PC0 && u8Pin <= DIO_PC6){
			WRITE_BIT_VAL(DDRC, (u8Pin-8), u8Mode);
		} else if(u8Pin >= DIO_PD0 && u8Pin <= DIO_PD7){
			WRITE_BIT_VAL(DDRD, (u8Pin-15), u8Mode);
		}
	}
}

/************************************************************************************************************
* Function				: DIO_vidDigitalPinWrite
* Description			: Set pin value (HIGH/LOW).
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
						  Range : see PIN MAP macros defined on top of "DIO.h" file
						  [u8Value] desired value (HIGH, or LOW) 
						  Range : defined macros (HIGH, or LOW)
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void	DIO_vidDigitalPinWrite	(uint8 u8Pin, uint8 u8Value){
	if (u8Value==HIGH || u8Value ==LOW){	
		if(u8Pin >= DIO_PB0 && u8Pin <= DIO_PB7){
			WRITE_BIT_VAL(PORTB, u8Pin,u8Value);
		} else if(u8Pin >= DIO_PC0 && u8Pin <= DIO_PC6){
			WRITE_BIT_VAL(PORTC, (u8Pin-8),u8Value);
		} else if(u8Pin >= DIO_PD0 && u8Pin <= DIO_PD7){
			WRITE_BIT_VAL(PORTD, (u8Pin-15),u8Value);
		}
	}
}

/************************************************************************************************************
* Function				: DIO_vidDigitalPinToggle
* Description			: toggle the value of a given pin (HIGH to LOW  or LOW to HIGH).
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
						  Range : see PIN MAP macros defined on top of "DIO.h" file
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void	DIO_vidDigitalPinToggle	(uint8 u8Pin){
	if(u8Pin >= DIO_PB0 && u8Pin <= DIO_PB7){
		TOGGLE_BIT(PORTB, u8Pin);
	} else if(u8Pin >= DIO_PC0 && u8Pin <= DIO_PC6){
		TOGGLE_BIT(PORTC, (u8Pin-8));
	} else if(u8Pin >= DIO_PD0 && u8Pin <= DIO_PD7){
		TOGGLE_BIT(PORTD, (u8Pin-15));
	}
}

/************************************************************************************************************
* Function				: DIO_u8DigitalRead
* Description			: Read the value of a given pin.
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
						  Range : see PIN MAP macros defined on top of "DIO.h" file
* Parameters[in/out]	: None
* Parameters[out]		: uint8 the logical value value of the selected pin (HIGH, or LOW).
*
*************************************************************************************************************/
extern uint8 DIO_u8DigitalRead (uint8 u8Pin){
	uint8 u8RetVal = STD_ERR_NOK;
	if(u8Pin >= DIO_PB0 && u8Pin <= DIO_PB7){
			u8RetVal = READ_BIT_VAL(PORTB, u8Pin);
		} else if(u8Pin >= DIO_PC0 && u8Pin <= DIO_PC6){
			u8RetVal = READ_BIT_VAL(PORTC, u8Pin-8);
		} else if(u8Pin >= DIO_PD0 && u8Pin <= DIO_PD7){
			u8RetVal = READ_BIT_VAL(PORTD, u8Pin-15);
	}	
	return u8RetVal;
}


#if 0
extern uint32	DIO_u32AnalogRead		(uint8 u8Pin){
	
	return 0;
}
extern void		DIO_vidAnalogReference	(uint8 u8Mode){
	
}
extern void		DIO_vidAnalogPinWrite	(uint8 u8Pin, uint8 u8Value){
	
}
#endif

