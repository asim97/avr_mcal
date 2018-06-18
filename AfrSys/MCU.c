/*! \file MCU.c \brief library for all MCU configurations and dedicated APIs */
/**********************************************************************************************************
*
* File Name		: 'MCU.c'
* Title			: Library for all MCU configurations and dedicated APIs
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/10/2018 6:24:51 PM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved
*

 ----------------------------------------------------------------------------------------------------------
 cpu		:   ATmega8
 speed		:   1 mhz (max: 16 mhz)
 voltage	:	5 V
 ram		:   1024 bytes (0x0060-0x045f)
 rom		:   4096 bytes (0x0000-0x0fff)
 eeprom		:	512 bytes (0x0000-0x01ff)
 -----------------------------------------------------------------------------------------------------------
  -----------------------------------------------------------------------------------------------------------
  cpu:     ATmega32
  speed:   1 mhz (max: 16 mhz)
  voltage: 5 V
  ram:     2048 bytes (0x0060-0x085f)
  rom:     16384 bytes (0x0000-0x3fff)
  eeprom:  1024 bytes (0x0000-0x03ff)
  -----------------------------------------------------------------------------------------------------------
************************************************************************************************************/

/*---------------------------------------------------- INCLUDES --------------------------------------------*/
#include "MCU.h"
#include "LOG_uartLogger.h"

/*--------------------------------------------- MACROS Definitions ------------------------------------------*/



/*---------------------------------------------- Global Variables -------------------------------------------*/

/* Var. to count the number of the nested critical sections */
static uint8 MCU_u8NoOfInterrDisabled = (uint8)0x00;


/*--------------------------------------------- FUNCTION Definitions ----------------------------------------*/

/*************************************************************************************************************
* Function				: MCU_vidResetSrcCheck
* Description			: Check the source of last reset and perform necessary actions
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidResetSrcCheck(void){

	/* Reset Source checking */
	if (MCUCSR & (1<<PORF))
	{
		/* Power-on Reset */
		MCUCSR=0;

		INFO("Power-on Reset");
	}
	else if (MCUCSR & (1<<EXTRF))
	{
		/* External Reset */
		MCUCSR=0;

		INFO("External Reset");
	}
	else if (MCUCSR & (1<<BORF))
	{
		/* Brown-Out Reset */
		MCUCSR=0;

		INFO("Brown-Out Reset");
	}
	else if (MCUCSR & (1<<WDRF))
	{
		/* Watchdog Reset */
		MCUCSR=0;

		INFO("Watchdog Reset");
	} else {
		INFO("UNKNOWN RESET");
	}
}

/************************************************************************************************************
* Function				: MCU_vidDisableInterrupts
* Description			: Disables the Global interrupt of the Micro controller taking in
						  consideration the Nested Critical sections
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
*************************************************************************************************************/
extern void MCU_vidDisableInterrupts(void)
{
	if(MCU_u8NoOfInterrDisabled == (uint8)0)
	{
		cli();
		MCU_u8NoOfInterrDisabled ++;
	}
	else
	{
		MCU_u8NoOfInterrDisabled ++;
	}
}

/************************************************************************************************************
* Function				: MCU_vidEnableInterrupts
* Description			: Enables the Global interrupt of the Micro controller taking in consideration
						  the Nested Critical sections
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
*************************************************************************************************************/
extern void MCU_vidEnableInterrupts( void )
{
	if(MCU_u8NoOfInterrDisabled > (uint8)0)
	{
		MCU_u8NoOfInterrDisabled --;
	}
	else
	{

	}
	if(MCU_u8NoOfInterrDisabled ==(uint8)0)
	{
		sei();
	}
	else
	{

	}
	
}

/************************************************************************************************************
* Function				: MCU_vidDelay_1_us
* Description			: Cause a delay of almost 1 us
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
*************************************************************************************************************/
extern void MCU_vidDelay_1_us(void)  {
	/* depends on cpu speed @ 1 mhz 1 us != 1 nop (minus something for call+ret) */
	NOP();
}

/************************************************************************************************************
* Function				: MCU_vidDelay_10_us
* Description			: Cause a delay of almost 10 us
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
*************************************************************************************************************/
extern void MCU_vidDelay_10_us(void) { 
	unsigned char a;
	 for (a=0; a<10; a++){
		  MCU_vidDelay_1_us(); 
	 }
}

/*************************************************************************************************************
* Function				: MCU_vidResetCpu
* Description			: Cause a reset for the MCU
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidResetCpu(void) {
	
}



