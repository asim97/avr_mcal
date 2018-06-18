/*! \file TIM_timers.h \brief System Timer function library. */
/**************************************************************************************************************
*
* File Name		: 'TIM_timers.h'
* Title			: System Timers function library
* Author		: Mohamed Abd El Raouf - Copyright (C) 2018-2020
* Created		: 2/18/2018 1:35:00 AM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC
*
***************************************************************************************************************/


#ifndef TIM_TIMERS_H_
#define TIM_TIMERS_H_

/*--------------------------------------------- INCLUDES ------------------------------------------------------*/

#include "MCU.h"
#include "Std_Types.h"

/*----------------------------------------- MACROS Definitions ------------------------------------------------*/

#define TIM1_CHA_CHB_DISCONNECTED       (uint8)0
#define TIM1_CHB_DISCONNECTED		    (uint8)1
#define TIM1_CHA_CHB_NON_INVERTING	    (uint8)2
#define TIM1_CHA_CHB_INVERTING		    (uint8)3


#define TIM1_STOP						(uint8)0
#define TIM1_NO_PRESCALER				(uint8)1
#define TIM1_8_PRESCALER				(uint8)2
#define TIM1_64_PRESCALER				(uint8)3
#define TIM1_256_PRESCALER				(uint8)4
#define TIM1_1024_PRESCALER				(uint8)5
#define TIM1_Ext_CLK_FALLING			(uint8)6
#define TIM1_Ext_CLK_RISING				(uint8)7


#define TIM1_Normal						(uint8)0
#define TIM1_PWM_Ph_8_BIT				(uint8)1
#define TIM1_PWM_Ph_9_BIT				(uint8)2
#define TIM1_PWM_Ph_10_BIT				(uint8)3
#define TIM1_CTC_TOP_OCR1A				(uint8)4
#define TIM1_FAST_PWM_8_BIT				(uint8)5
#define TIM1_FAST_PWM_9_BIT				(uint8)6
#define TIM1_FAST_PWM_10_BIT			(uint8)7
#define TIM1_PWM_Ph_Freq_TOP_ICR1		(uint8)8
#define TIM1_PWM_Ph_Freq_TOP_OCR1A		(uint8)9
#define TIM1_PWM_Ph_TOP_ICR1			(uint8)10
#define TIM1_PWM_Ph_TOP_OCR1A			(uint8)11
#define TIM1_CTC_TOP_ICR1				(uint8)12
#define TIM1_FAST_PWM_TOP_ICR1			(uint8)13
#define TIM1_FAST_PWM_TOP_OCR1A			(uint8)14



/*------------------------------------------ Type Definitions  ------------------------------------------------*/

typedef void (* TIM_tpfvidOverFlowClbk )(void );

/*------------------------------------------ Global Variables -------------------------------------------------*/

TIM_tpfvidOverFlowClbk pfvOnT0OverFlowClbk;

/*---------------------------------------- FUNCTION Definitions -----------------------------------------------*/

/****************************************************************************************************************
* Function				: TIM_vidInitT0
* Description			: Timer0 initialization routine in overflow mode every 1 ms.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*****************************************************************************************************************/
extern void TIM_vidInitT0(void);

/*****************************************************************************************************************
* Function				: TIM_vidT0AttachInterrupt
* Description			: Attach a routine Call back for timer 0 over flow interrupt
* Parameters[in]		: [pfvClbk] pointer the Call back routine
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*******************************************************************************************************************/
extern void TIM_vidT0AttachInterrupt(TIM_tpfvidOverFlowClbk pfvClbk);

/*****************************************************************************************************************
* Function				: TIM_vidT0DeAttachInterrupt
* Description			: De-attach the routine call back from timer 0 over flow interrupt
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*******************************************************************************************************************/
extern void TIM_vidT0DeAttachInterrupt(void);

/*****************************************************************************************************************
* Function				: TIM_u32GetMillis
* Description			: return approximate number of milli seconds elapsed since the initialization of Timer 0
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: uint32 approximate number of milli seconds elapsed since the initialization of Timer 0
*
*******************************************************************************************************************/
extern uint32 TIM_u32GetMillis(void);


/***************************************************************************************************************
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
****************************************************************************************************************/
extern void TIM_vidT1PWMInit(uint8 u8BitRes, uint8 u8PwmChMode, uint8 u8Prescaler);

/***************************************************************************************************************
* Function				: TIM_vidT1SetPwmChannelsMode									  
* Description			: Change mode for timer1 OC1A, OC1B	pins.			  
* Parameters[in]		: [u8PwmChMode ] The desired mode for OC1A, OC1B pins
						  Range ( TIM1_CHA_CHB_DISCONNECTED , TIM1_CHB_DISCONNECTED, 
						  TIM1_CHA_CHB_NON_INVERTING ,TIM1_CHA_CHB_INVERTING )

* Parameters[in/out]	: None												  
* Parameters[out]		: None												  
*																			  
****************************************************************************************************************/
extern void TIM_vidT1SetPwmChannelsMode(uint8 u8PwmChMode);

/***************************************************************************************************************
* Function				: TIM_vidT1SetPrescaler									  
* Description			: set prescaler value for timer 1.			  
* Parameters[in]		: [u8TimPrescaler ] The desired CLK divider for timer one
						  Range ( TIM1_STOP, TIM1_NO_PRESCALER, TIM1_8_PRESCALER, TIM1_64_PRESCALER, 
						  TIM1_256_PRESCALER, TIM1_1024_PRESCALER, TIM1_Ext_CLK_FALLING, 
						  TIM1_Ext_CLK_RISING )
* Parameters[in/out]	: None												  
* Parameters[out]		: None												  
*																			  
****************************************************************************************************************/
extern void TIM_vidT1SetPrescaler(uint8 u8TimPrescaler);

/****************************************************************************************************************
* Function				: TIM_u16T1GetPrescaler
* Description			: Get the current prescaler setting value for timer 1.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: uint16
*
*****************************************************************************************************************/
extern uint16 TIM_u16T1GetPrescaler(void);


/****************************************************************************************************************
* Function				: TIM_vidT1PWMOff
* Description			: Turn off timer1 PWM mode, set PWM1A/B (OutputCompare action) to none.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
******************************************************************************************************************/
extern void TIM_vidT1PWMOff(void);

/*****************************************************************************************************************
*
* Function				: TIM_vidT1PWMAOff
* Description			: Turn off channel A (OC1A) PWM output, set OC1A (OutputCompare action) to none
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
******************************************************************************************************************/
extern void TIM_vidT1PWMAOff(void);

/*****************************************************************************************************************
* Function				: TIM_vidT1PWMBOff
* Description			: Turn off channel B (OC1B) PWM output, set OC1B (OutputCompare action) to none
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
******************************************************************************************************************/
extern void TIM_vidT1PWMBOff(void);

/*****************************************************************************************************************
* Function				: TIM_vidT1PwmOn
* Description			: Turn on channel A/B PWM output set OC1A/B as non-inverted PWM.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
******************************************************************************************************************/
extern void TIM_vidT1PwmOn(void);

/*****************************************************************************************************************
* Function				: TIM_vidT1PwmAOn
* Description			: Turn on channel A PWM output set OC1A as non-inverted PWM.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
******************************************************************************************************************/
extern void TIM_vidT1PwmAOn(void);

/*****************************************************************************************************************
* Function				: TIM_vidT1PwmBOn
* Description			: Turn on channel B PWM output set OC1B as non-inverted PWM.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*******************************************************************************************************************/
extern void TIM_vidT1PwmBOn(void);

/******************************************************************************************************************
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
*******************************************************************************************************************/
extern void TIM_vidT1PwmASetDuty(uint16 u16PwmDuty);

/******************************************************************************************************************
*
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
*******************************************************************************************************************/
extern void TIM_vidT1PwmBSetDuty(uint16 u16PwmDuty);




#endif /* TIM_TIMERS_H_ */