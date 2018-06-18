/*! \file ADC.c \brief System ADC function library. */
/************************************************************************************************************
*
* File Name		: 'ADC.c'
* Title			: System ADC function library
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/18/2018 1:35:00 AM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved 
*
************************************************************************************************************/


/*------------------------------------------------- INCLUDES ----------------------------------------------*/
#include "DIO.h"
#include "LOG_uartLogger.h"

#include "ADC.h"

/*--------------------------------------------- MACROS Definitions -----------------------------------------*/




/*---------------------------------------------- Global Variables -----------------------------------------*/


/*-------------------------------------------- FUNCTION Definitions ---------------------------------------*/


/************************************************************************************************************
* Function				: ADC_vidInit
* Description			: ADC initialization routine.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void ADC_vidInit(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX3:0  = 0000 to choose channel 0 as initialization 
	 */

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */ 
	
	/* ADC initialization */

	ADMUX = ADC_VREF_AREF | (ADLAR_ADJUST<<ADLAR);
	
	/********************************************************************************************************
				(ADCSRA) ADC Control and Status Register A 
	 ADEN: ADC Enable
	 ADSC: ADC Start Conversion 
	 ADFR: ADC Free Running Select
	 ADIF: ADC Interrupt Flag (if ADC interrupt disabled cleared by writing a logical one)
	 ADIE: ADC Interrupt Enable
	 ADPS2:0: ADC Prescaler Select Bits	 
	 
	 ADPS2 ADPS1 ADPS0		Division Factor
	 0     0	   0			 2
	 0     0	   1			 2
	 0     1	   0			 4
	 0     1	   1			 8
	 1     0	   0			 16
	 1     0	   1			 32
	 1     1	   0			 64
	 1     1	   1			 128
	*********************************************************************************************************/
	
	ADCSRA = (1<<ADEN)|(0<<ADSC)|(0<<ADIF)|(ADC_INT_MODE<<ADIE)|ADC_PRESCALER_8; 
}

/************************************************************************************************************
* Function				: ADC_u16Read
* Description			: Start Single conversion and return the ADC reading for selected channel.
* Parameters[in]		: [u8ChannelNum] selected channel to get reading for
						  Range (0-5)
* Parameters[in/out]	: None
* Parameters[out]		: [uint16] ADC reading.
*
*************************************************************************************************************/
extern uint16 ADC_u16Read(uint8 u8ChannelNum)
{
   //Select ADC Channel ch must be 0-5
   u8ChannelNum = u8ChannelNum & 0x05;
   ADMUX |= u8ChannelNum;

	MCU_vidDelay_10_us();
	
   /* Start Single conversion */
   ADCSRA |= (1<<ADSC);

   /* Wait for conversion to complete */
   while(!(ADCSRA & (1<<ADIF)));

   /* Clear ADIF by writing one to it */
   ADCSRA|=(1<<ADIF);
   //INFO("ADCL %d",ADCL);
   //INFO("ADCH %d",ADCH);
   return ADC;
}