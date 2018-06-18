/*! \file ADC.h \brief System ADC function library. */
/*************************************************************************************************************
*
* File Name		: 'ADC.h'
* Title			: System ADC function library
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/18/2018 1:35:00 AM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved 
*
*************************************************************************************************************/
#ifndef ADC_H_
#define ADC_H_


/*---------------------------------------------------- INCLUDES --------------------------------------------*/

#include "MCU.h"
#include "Std_Types.h"

/*--------------------------------------------- MACROS Definitions -----------------------------------------*/

/*
REFS1 REFS0			Voltage Reference Selection
  0     0		AREF, Internal Vref turned off
  0     1		AVCC with external capacitor at AREF pin
  1     0		Reserved
  1     1		Internal 2.56V Voltage Reference with external capacitor at AREF pi
 
*/
// Voltage Reference: AVCC pin
#define ADC_VREF_AVCC ((0<<REFS1) | (1<<REFS0))

// Voltage Reference: AREF pin
#define ADC_VREF_AREF ((0<<REFS1) | (0<<REFS0))

// Voltage Reference: Int., cap. on AREF
#define ADC_VREF_INTERNAL ((1<<REFS1) | (1<<REFS0))

#define	 RIGHT_ADJUSTED 0u
#define	 LEFT_ADJUSTED  1u

#define ADC_INTERRUPT_ENABLED  1u
#define ADC_INTERRUPT_DISABLED 0u

#define ADC_PRESCALER_2    ((0<<ADPS2)|(0<<ADPS1)|(1<<ADPS1))
#define ADC_PRESCALER_4    ((0<<ADPS2)|(1<<ADPS1)|(0<<ADPS1))
#define ADC_PRESCALER_8    ((0<<ADPS2)|(1<<ADPS1)|(1<<ADPS1))
#define ADC_PRESCALER_16   ((1<<ADPS2)|(0<<ADPS1)|(0<<ADPS1))
#define ADC_PRESCALER_32   ((1<<ADPS2)|(0<<ADPS1)|(1<<ADPS1))
#define ADC_PRESCALER_64   ((1<<ADPS2)|(1<<ADPS1)|(0<<ADPS1))
#define ADC_PRESCALER_128  ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS1))

#define ADC_VREF_TYPE	ADC_VREF_AVCC
#define ADLAR_ADJUST	RIGHT_ADJUSTED
#define ADC_INT_MODE	ADC_INTERRUPT_DISABLED
#define ADC_PRESCALER	ADC_PRESCALER_8



/*------------------------------------------------- Global Variables ----------------------------------------*/


/*--------------------------------------------- FUNCTION Definitions ----------------------------------------*/


/*************************************************************************************************************
* Function				: ADC_vidInit
* Description			: ADC initialization routine.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
**************************************************************************************************************/
extern void ADC_vidInit(void);

/*************************************************************************************************************
* Function				: ADC_u16Read
* Description			: Start Single conversion and return the ADC reading for selected channel.
* Parameters[in]		: [u8ChannelNum] selected channel to get reading for
						  Range (0-5)
* Parameters[in/out]	: None
* Parameters[out]		: [uint16] ADC reading.
						  Range : (0 - 1023)
*
**************************************************************************************************************/
extern uint16 ADC_u16Read(uint8 u8ChannelNum);


#endif /* ADC_H_ */