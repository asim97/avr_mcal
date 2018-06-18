/*! \file DIO.h \brief Digital Input/Output peripheral driver. */
/**********************************************************************************************************
*
* File Name		: 'DIO.h'
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
#ifndef DIO_H_
#define DIO_H_

/*------------------------------------------------- INCLUDES ----------------------------------------------*/

#include "Std_Types.h"
#include "Common_Macros.h"
#include "MCU.h"

/*-------------------------------------------- MACROS Definitions -----------------------------------------*/

#define HIGH 0x01
#define LOW  0x00

#define INPUT	0x00
#define OUTPUT	0x01
#define INPUT_PULLUP 0x2



/*********************************************** ATMEGA 8 PIN MAP *******************************************/
#define DIO_PB0	0U
#define DIO_PB1	1U
#define DIO_PB2	2U
#define DIO_PB3	3U
#define DIO_PB4	4U
#define DIO_PB5	5U
#define DIO_PB6	6U
#define DIO_PB7	7U

#define DIO_PC0	8U
#define DIO_PC1	9U
#define DIO_PC2	10U
#define DIO_PC3	11U
#define DIO_PC4	12U
#define DIO_PC5	13U
#define DIO_PC6	14U

#define DIO_PD0	15U
#define DIO_PD1	16U
#define DIO_PD2	17U
#define DIO_PD3	18U
#define DIO_PD4	19U
#define DIO_PD5	20U
#define DIO_PD6	21U
#define DIO_PD7	22U
/***********************************************************************************************************/


/*------------------------------------------ Global Variables ---------------------------------------------*/


/*---------------------------------------- FUNCTION Definitions -------------------------------------------*/

/************************************************************************************************************
* Function				: DIO_vidSetPinMode
* Description			: Set pin mode in/out.
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
						  Range : see PIN MAP macros defined on top of "DIO.h" file
						  [u8Mode] desired mode (Input/Output) for selected pin 
						  Range : (INPUT, OUTPUT, or INPUT_PULLUP)
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void		DIO_vidSetPinMode		(uint8 u8Pin, uint8 u8Mode);

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
extern void		DIO_vidDigitalPinWrite	(uint8 u8Pin, uint8 u8Value);

/************************************************************************************************************
* Function				: DIO_vidDigitalPinToggle
* Description			: toggle the value of a given pin (HIGH to LOW  or LOW to HIGH).
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
						  Range : see PIN MAP macros defined on top of "DIO.h" file
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void		DIO_vidDigitalPinToggle	(uint8 u8Pin);

/************************************************************************************************************
* Function				: DIO_u8DigitalRead
* Description			: Read the value of a given pin.
* Parameters[in]		: [u8Pin] Selected pin from all available pins in the MCU
						  Range : see PIN MAP macros defined on top of "DIO.h" file
* Parameters[in/out]	: None
* Parameters[out]		: uint8 the logical value value of the selected pin (HIGH, or LOW).
*
*************************************************************************************************************/
extern uint8	DIO_u8DigitalRead		(uint8 u8Pin);



#if 0
extern uint32	DIO_u32AnalogRead		(uint8 u8Pin);
extern void		DIO_vidAnalogReference	(uint8 u8Mode);
extern void		DIO_vidAnalogPinWrite	(uint8 u8Pin, uint8 u8Value);
#endif


#endif /* DIO_H_ */