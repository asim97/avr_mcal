/*! \file TIM_timers.c \brief System Timer function library. */
/*****************************************************************************
*
* File Name		: 'TIM_timers.c'
* Title			: System Timers function library
* Author		: Mohamed Abd El Raouf - Copyright (C) 2018-2020
* Created		: 2/18/2018 1:35:00 AM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC
*
*****************************************************************************/


/*--------------------------------------------- INCLUDES ------------------------------------------------------*/

#include "TIM_timers.h"
#include "Common_Macros.h"
#include "LOG_uartLogger.h"

/*----------------------------------------- MACROS Definitions ------------------------------------------------*/

/*
TCCR1A : Timer/Counter 1 Control Register A
Bit   7		 6		5		4	  3		2	  1		0
	COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10 
	
	• Bit 3  FOC1A: Force Output Compare for channel A
	• Bit 2  FOC1B: Force Output Compare for channel B

	The FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode.
	However, for ensuring compatibility with future devices, these bits must be set to zero when
	TCCR1A is written when operating in a PWM mode. When writing a logical one to the
	FOC1A/FOC1B bit, an immediate Compare Match is forced on the waveform generation unit.
	The OC1A/OC1B output is changed according to its COM1x1:0 bits setting. Note that the
	FOC1A/FOC1B bits are implemented as strobes. Therefore it is the value present in the
	COM1x1:0 bits that determine the effect of the forced compare.
	A FOC1A/FOC1B strobe will not generate any interrupt nor will it clear the timer in Clear Timer
	on Compare Match (CTC) mode using OCR1A as TOP.
	The FOC1A/FOC1B bits are always read as zero.
	
	• Compare Output Mode, Fast PWM
==================================================================================================================================+
	COM1A1/COM1B1	|	COM1A0/COM1B0		|			Description																  |
====================+=======================+=====================================================================================|
		0			|		 0				|	Normal port operation, OC1A/OC1B disconnected.									  |
--------------------+-----------------------+-------------------------------------------------------------------------------------|
		0			|		 1				|	WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B								  |
					|						|	disconnected (normal port operation). 											  |
					|						|	For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.		  |
--------------------+-----------------------+-------------------------------------------------------------------------------------|
		1			|		 0				|	Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM, (non-inverting mode)	  |
--------------------+-----------------------+-------------------------------------------------------------------------------------|
		1			|		 1				|	Set OC1A/OC1B on Compare Match, clear OC1A/OC1B at BOTTOM, (inverting mode)		  |
==================================================================================================================================+

*/

#define TIM1_CHA_CHB_DISCONNECTED_VAL		((0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0))
#define TIM1_CHB_DISCONNECTED_VAL			((0<<COM1A1)|(1<<COM1A0)|(0<<COM1B1)|(1<<COM1B0))
#define TIM1_CHA_CHB_NON_INVERTING_VAL		((1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0))
#define TIM1_CHA_CHB_INVERTING_VAL			((1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0))

/*
=========================================================================================================+												
TCCR1B	  TCCR1B	|	   TCCR1A		  TCCR1A 	|													 |
Bit 4	   BIT 3	|	    Bit 1		   Bit 0	|													 |
====================+===============================+====================================================|
WGM13	WGM12(CTC1)	|	WGM11(PWM11)	WGM10(PWM10)|				Mode					|	  TOP	 |
====================+===============================+=======================================+============|
  0			0		|		0				0		|	 Normal								|	0xFFFF 	 |
  0			0		|		0				1		|	 PWM, Phase Correct, 8-bit			|	0x00FF 	 |
  0			0		|		1				0		|	 PWM, Phase Correct, 9-bit			|	0x01FF 	 |
  0			0		|		1				1		|	 PWM, Phase Correct, 10-bit			|	0x03FF 	 |
  0			1		|		0				0		|	 CTC								|	OCR1A 	 |
--------------------+-------------------------------+---------------------------------------+------------|  
  0			1		|		0				1		|	 Fast PWM, 8-bit					|	0x00FF 	 |
--------------------+-------------------------------+---------------------------------------+------------|  
  0			1		|		1				0		|	 Fast PWM, 9-bit					|	0x01FF	 |
  0			1		|		1				1		|	 Fast PWM, 10-bit					|	0x03FF	 |
  1			0		|		0				0		|	 PWM, Phase and Frequency Correct	|	ICR1 	 |
  1			0		|		0				1		|	 PWM, Phase and Frequency Correct	|	OCR1A 	 |
  1			0		|		1				0		|	 PWM, Phase Correct					|	ICR1 	 |
  1			0		|		1				1		|	 PWM, Phase Correct					|	OCR1A 	 |
  1			1		|		0				0		|	 CTC								|	ICR1 	 |
  1			1		|		0				1		|	 (Reserved)							|	–		 |
  1			1		|		1				0		|	 Fast PWM							|	ICR1 	 |
  1			1		|		1				1		|	 Fast PWM							|	OCR1A	 |
=========================================================================================================+
*/

		
#define TIM1_VAL_Normal				TCCR1B |= (0<<WGM13) | (0<<WGM12);\
									TCCR1A |= (0<<WGM11) | (0<<WGM10)
#define TIM1_VAL_PWM_Ph_8_BIT
#define TIM1_VAL_PWM_Ph_9_BIT
#define TIM1_VAL_PWM_Ph_10_BIT
#define TIM1_VAL_CTC_TOP_OCR1A
#define TIM1_VAL_FAST_PWM_8_BIT
#define TIM1_VAL_FAST_PWM_9_BIT
#define TIM1_VAL_FAST_PWM_10_BIT
#define TIM1_VAL_PWM_Ph_Freq_TOP_ICR1
#define TIM1_VAL_PWM_Ph_Freq_TOP_OCR1A
#define TIM1_VAL_PWM_Ph_TOP_ICR1
#define TIM1_VAL_PWM_Ph_TOP_OCR1A
#define TIM1_VAL_CTC_TOP_ICR1
#define TIM1_VAL_FAST_PWM_TOP_ICR1
#define TIM1_VAL_FAST_PWM_TOP_OCR1A


/***********************************************************************************************************

TCCR1B : Timer/Counter 1 Control Register BBit	   7	6	5   4	  3	    2	 1	  0
	ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10 
	
================================================================================+	
CS12 | CS11 |CS10 |			Description											|
=====+======+=====+=============================================================|
0    |  0   | 0	  |No clock source. (Timer/Counter stopped)						|
0    |  0   | 1	  |clkI/O/1 (No prescaling)										|
0    |  1   | 0	  |clkI/O/8 (From prescaler)									|
0    |  1   | 1	  |clkI/O/64 (From prescaler)									|
1    |  0   | 0	  |clkI/O/256 (From prescaler)									|
1    |  0   | 1	  |clkI/O/1024 (From prescaler)									|
1    |  1   | 0	  |External clock source on T1 pin. Clock on falling edge		|
1    |  1   | 1	  |External clock source on T1 pin. Clock on rising edge		|
================================================================================+

***********************************************************************************************************/

#define TIM1_VAL_STOP				((0<<CS12)|(0<<CS11)|(0<<CS10))
#define TIM1_VAL_NO_PRESCALER		((0<<CS12)|(0<<CS11)|(1<<CS10))
#define TIM1_VAL_8_PRESCALER		((0<<CS12)|(1<<CS11)|(0<<CS10))
#define TIM1_VAL_64_PRESCALER		((0<<CS12)|(1<<CS11)|(1<<CS10))
#define TIM1_VAL_256_PRESCALER		((1<<CS12)|(0<<CS11)|(0<<CS10))
#define TIM1_VAL_1024_PRESCALER		((1<<CS12)|(0<<CS11)|(1<<CS10))
#define TIM1_VAL_Ext_CLK_FALLING	((1<<CS12)|(1<<CS11)|(0<<CS10))
#define TIM1_VAL_Ext_CLK_RISING		((1<<CS12)|(1<<CS11)|(1<<CS10))

/*------------------------------------------ Global Variables -------------------------------------------------*/

static uint32 TIM_u32Millis = 0; /* max value nearly equals 1 week */
static uint32 TIM_u32OverFlowCounter = 0;

/*---------------------------------------- FUNCTION Definitions -----------------------------------------------*/

/******************************************************************************
Function			: TIMER0_OVF_vect ISR routine                                   
Description			: Timer0 Overflow interrupt service routine.
Parameters[in]		: None 
Parameters[in/out]	: None 
Parameters[out]		: None 
********************************************************************************/
ISR(TIMER0_OVF_vect)
{
	TIM_u32OverFlowCounter++;
	TIM_u32Millis++;
	
	/* re init counter */
	TCNT0 = 131;
	if (TIM_u32OverFlowCounter % 1000 == 0){
		TIM_u32OverFlowCounter = 0;
		INFO("1 second passed");
	}
	if (pfvOnT0OverFlowClbk != NULL){
		pfvOnT0OverFlowClbk();
	}
}

/******************************************************************************************************************
* Function				: TIM_vidInitT0										  
* Description			: Timer0 initialization routine in overflow mode every 1 ms.					  
* Parameters[in]		: None												  
* Parameters[in/out]	: None												  
* Parameters[out]		: None												  
*																			  
*******************************************************************************************************************/
extern void TIM_vidInitT0(void)
{
	TIM_u32OverFlowCounter = 0;
	TIM_u32Millis = 0;
	
	pfvOnT0OverFlowClbk = NULL;

	/* Timer0 settings: ~ 1000 ticks (1 ms) */
	TCCR0 = (1<<CS01); // prescaler = 8
	/* init counter */
	TCNT0 = 131;
	/* Timer0 Overflow Interrupt Enable */
	TIMSK = (1<<TOIE0); 
}

/*****************************************************************************************************************
* Function				: TIM_vidT0AttachInterrupt
* Description			: Attach a routine Call back for timer 0 over flow interrupt
* Parameters[in]		: [pfvClbk] pointer the Call back routine
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*******************************************************************************************************************/
extern void TIM_vidT0AttachInterrupt(TIM_tpfvidOverFlowClbk pfvClbk)
{
	pfvOnT0OverFlowClbk = pfvClbk;
}

/*****************************************************************************************************************
* Function				: TIM_vidT0DeAttachInterrupt
* Description			: De-attach a routine Call back for timer 0 over flow interrupt
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*******************************************************************************************************************/
extern void TIM_vidT0DeAttachInterrupt(void)
{
	pfvOnT0OverFlowClbk = NULL;
}

/*****************************************************************************************************************
* Function				: TIM_u32GetMillis
* Description			: return approximate number of milli seconds elapsed since the initialization of Timer 0
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: uint32 approximate number of milli seconds elapsed since the initialization of Timer 0
*
*******************************************************************************************************************/
extern uint32 TIM_u32GetMillis(void)
{
	return TIM_u32Millis;
}

/***********************************************************************************************************
* Function				: TIM_vidT1PWMInit									  
* Description			: Timer1 PWM initialization routine.				  
* Parameters[in]		: [u8BitRes	   ] Number of bits that dictate the 
										 counter register max value.
						  Range ( 8 or 9 or 10 bits).
						   				 
						  [u8PwmChMode ] The desired mode for OC1A, OC1B pins
						  Range ( TIM1_CHA_CHB_DISCONNECTED , TIM1_CHB_DISCONNECTED,
						  TIM1_CHA_CHB_NON_INVERTING ,TIM1_CHA_CHB_INVERTING )
						  
						  [u8Prescaler ] The prescaler value for the timer CLK
						  Range ( TIM1_STOP, TIM1_NO_PRESCALER, TIM1_8_PRESCALER, TIM1_64_PRESCALER,
						  TIM1_256_PRESCALER, TIM1_1024_PRESCALER, TIM1_Ext_CLK_FALLING,
						  TIM1_Ext_CLK_RISING )
						  
* Parameters[in/out]	: None												  
* Parameters[out]		: None												  
*																			  
************************************************************************************************************/
extern void TIM_vidT1PWMInit(uint8 u8BitRes, uint8 u8PwmChMode, uint8 u8Prescaler)
{
	
	/* configures timer1 for use with PWM output on OC1A and OC1B pins 	*/
	/* enable timer1 as 8,9 or 10bit PWM								*/
	
	switch (u8BitRes)
	{
		case 8:
			/* 8bit mode */
			CLEAR_BIT(TCCR1B,WGM13);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1A,WGM10);
		break;
		
		case 9:
			/* 9bit mode */

		break;
		
		case 10:
			/* 10bit mode */

		break;
		
		default:
			INFO("Invalid mode");
		break;
	}
	

	
	
	/* clear output compare value A */
	WRITE_REG_VAL(OCR1AH, 0x00);
	WRITE_REG_VAL(OCR1AL, 0x00);
	/* clear output compare value B */
	WRITE_REG_VAL(OCR1BH, 0x00);
	WRITE_REG_VAL(OCR1BL, 0x00);
	
	TIM_vidT1SetPrescaler(u8Prescaler);
	TIM_vidT1SetPwmChannelsMode(u8PwmChMode);
	
}

/***********************************************************************************************************
* Function				: TIM_vidT1SetPwmChannelsMode									  
* Description			: Change mode for timer1 OC1A, OC1B	pins.			  
* Parameters[in]		: [u8PwmChMode ] The desired mode for OC1A, OC1B pins
						  Range ( TIM1_CHA_CHB_DISCONNECTED , TIM1_CHB_DISCONNECTED, 
						  TIM1_CHA_CHB_NON_INVERTING ,TIM1_CHA_CHB_INVERTING )

* Parameters[in/out]	: None												  
* Parameters[out]		: None												  
*																			  
************************************************************************************************************/
extern void TIM_vidT1SetPwmChannelsMode (uint8 u8PwmChMode)
{
	switch(u8PwmChMode){
		case TIM1_CHA_CHB_DISCONNECTED:
			TCCR1A |= TIM1_CHA_CHB_DISCONNECTED_VAL;
		break;
		
		case TIM1_CHB_DISCONNECTED:
			TCCR1A |= TIM1_CHB_DISCONNECTED_VAL;
		break;
		
		case TIM1_CHA_CHB_NON_INVERTING:
			TCCR1A |= TIM1_CHA_CHB_NON_INVERTING_VAL;
		break;
		
		case TIM1_CHA_CHB_INVERTING:
			TCCR1A |= TIM1_CHA_CHB_INVERTING_VAL;
		break;
		
		default:
			INFO("Invalid T1 Mode Requested!!");
		break;
	}
}

/***********************************************************************************************************
* Function				: TIM_vidT1SetPrescaler									  
* Description			: set prescaler value for timer 1.			  
* Parameters[in]		: [u8TimPrescaler ] The desired CLK divider for timer one
						  Range ( TIM1_STOP, TIM1_NO_PRESCALER, TIM1_8_PRESCALER, TIM1_64_PRESCALER, 
						  TIM1_256_PRESCALER, TIM1_1024_PRESCALER, TIM1_Ext_CLK_FALLING, 
						  TIM1_Ext_CLK_RISING )
* Parameters[in/out]	: None												  
* Parameters[out]		: None												  
*																			  
************************************************************************************************************/
extern void TIM_vidT1SetPrescaler(uint8 u8TimPrescaler)
{
	/* set prescaler on timer 1 */
	switch (u8TimPrescaler)
	{
		case TIM1_STOP			 :
			TCCR1B |= TIM1_VAL_STOP;
		break;
		
		case TIM1_NO_PRESCALER	 :
			TCCR1B |= TIM1_VAL_NO_PRESCALER;
		break;
		
		case TIM1_8_PRESCALER	 :
			TCCR1B |= TIM1_VAL_8_PRESCALER;
		break;
		
		case TIM1_64_PRESCALER	 :
			TCCR1B |= TIM1_VAL_64_PRESCALER;
		break;
		
		case TIM1_256_PRESCALER	 :
			TCCR1B |= TIM1_VAL_256_PRESCALER;
		break;
		
		case TIM1_1024_PRESCALER :
			TCCR1B |= TIM1_VAL_1024_PRESCALER;
		break;
		
		case TIM1_Ext_CLK_FALLING:
			TCCR1B |= TIM1_VAL_Ext_CLK_FALLING;
		break;
		
		case TIM1_Ext_CLK_RISING :
			TCCR1B |= TIM1_VAL_Ext_CLK_RISING;
		break;
		
		default:
			INFO("Invalid prescaler value");
		break;
	}
}


/***********************************************************************************************************
* Function				: TIM_u16T1GetPrescaler									  
* Description			: Get the current prescaler setting value for timer 1.			  
* Parameters[in]		: None
* Parameters[in/out]	: None												  
* Parameters[out]		: uint16												  
*																			  
************************************************************************************************************/
extern uint16 TIM_u16T1GetPrescaler(void)
{
	/* get the current prescaler setting */
	return 0;
}


/***********************************************************************************************************
* Function				: TIM_vidT1PWMOff
* Description			: Turn off timer1 PWM mode, set PWM1A/B (OutputCompare action) to none.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PWMOff(void)
{
	/* turn off timer1 PWM mode */
	CLEAR_BIT(TCCR1A,WGM11);
	CLEAR_BIT(TCCR1A,WGM10);
	/* set PWM1A/B (OutputCompare action) to none */
	TIM_vidT1PWMAOff();
	TIM_vidT1PWMBOff();
}

/***********************************************************************************************************
* Function				: TIM_vidT1PwmOn
* Description			: Turn on channel A/B PWM output set OC1A/B as non-inverted PWM.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PwmOn(void)
{
	TIM_vidT1PwmAOn();
	TIM_vidT1PwmBOn();
}

/***********************************************************************************************************
* Function				: TIM_vidT1PwmAOn
* Description			: Turn on channel A PWM output set OC1A as non-inverted PWM.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PwmAOn(void)
{
	/* turn on channel A (OC1A) PWM output */
	/* set OC1A as non-inverted PWM		   */
	SET_BIT(TCCR1A,COM1A1);
	CLEAR_BIT(TCCR1A,COM1A0);
}

/***********************************************************************************************************
* Function				: TIM_vidT1PwmBOn
* Description			: Turn on channel B PWM output set OC1B as non-inverted PWM.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PwmBOn(void)
{
	/* turn on channel B (OC1B) PWM output	*/
	/* set OC1B as non-inverted PWM			*/
	SET_BIT(TCCR1A,COM1B1);
	CLEAR_BIT(TCCR1A,COM1B0);
}

/***********************************************************************************************************
* Function				: TIM_vidT1PWMAOff
* Description			: Turn off channel A (OC1A) PWM output, set OC1A (OutputCompare action) to none
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PWMAOff(void)
{
	/* turn off channel A (OC1A) PWM output		 */
	/* set OC1A (OutputCompare action) to none	 */
	CLEAR_BIT(TCCR1A,COM1A1);
	CLEAR_BIT(TCCR1A,COM1A0);
}

/***********************************************************************************************************
* Function				: TIM_vidT1PWMBOff
* Description			: Turn off channel B (OC1B) PWM output, set OC1B (OutputCompare action) to none
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PWMBOff(void)
{
	/* turn off channel B (OC1B) PWM output		*/
	/* set OC1B (OutputCompare action) to none	*/
	CLEAR_BIT(TCCR1A,COM1B1);
	CLEAR_BIT(TCCR1A,COM1B0);
}

/***********************************************************************************************************
*
* Function				: TIM_vidT1PwmASetDuty
* Description			: Set PWM (output compare) duty for channel A generated on OC1A pin.
* Parameters[in]		: [u16PwmDuty] duty for channel A
						  Range : 
						  pwmDuty should be in the range 0-255 for 8bit PWM
						  pwmDuty should be in the range 0-511 for 9bit PWM
						  pwmDuty should be in the range 0-1023 for 10bit PWM
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PwmASetDuty(uint16 u16PwmDuty)
{
	/*********************************************************************
	 set PWM (output compare) duty for channel A
	 this PWM output is generated on OC1A pin
	 NOTE:	pwmDuty should be in the range 0-255 for 8bit PWM
			pwmDuty should be in the range 0-511 for 9bit PWM
			pwmDuty should be in the range 0-1023 for 10bit PWM
	*********************************************************************/

	OCR1A = u16PwmDuty;
}

/***********************************************************************************************************
* Function				: TIM_vidT1PwmBSetDuty
* Description			: Set PWM (output compare) duty for channel B generated on OC1B pin.
* Parameters[in]		: [u16PwmDuty] duty for channel B
						  Range : 
						  pwmDuty should be in the range 0-255 for 8bit PWM		
						  pwmDuty should be in the range 0-511 for 9bit PWM		
						  pwmDuty should be in the range 0-1023 for 10bit PWM	
* Parameters[in/out]	: None
* Parameters[out]		: None
*
************************************************************************************************************/
extern void TIM_vidT1PwmBSetDuty(uint16 u16PwmDuty)
{
	/*********************************************************************
	set PWM (output compare) duty for channel B
	this PWM output is generated on OC1B pin
	NOTE:	pwmDuty should be in the range 0-255 for 8bit PWM
			pwmDuty should be in the range 0-511 for 9bit PWM
			pwmDuty should be in the range 0-1023 for 10bit PWM
	*********************************************************************/
	OCR1B = u16PwmDuty;
}

