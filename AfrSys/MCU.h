/*! \file MCU.h \brief library for all MCU configurations and dedicated APIs */
/**********************************************************************************************************
*
* File Name		: 'MCU.h'
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

#ifndef MCU_H_
#define MCU_H_

/*---------------------------------------------------- INCLUDES --------------------------------------------*/

#include "Std_Types.h"
#include "avr/interrupt.h"
#include "avr/wdt.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

/*--------------------------------------------- MACROS Definitions -----------------------------------------*/

#if !defined (F_CPU)
#define F_CPU 1000000UL
#endif

// supported / tested devices


#if defined(__AVR_ATmega8__)	|| \
defined(__AVR_ATmega16__)		|| \
defined(__AVR_ATmega32__)		|| \
defined(__AVR_ATmega8515__)		|| \
defined(__AVR_ATmega8535__)		|| \
defined(__AVR_ATmega323__)
#endif


#if defined (__AVR_ATmega8__)
#ifndef RAMSTART
#	define RAMSTART 	0x60
#endif
#	define STACK_SIZE	64
#	define TIMER_REG	TCCR0
#	define TIMER_ENABLE	TIMSK
#	define TIMER_VECTOR	TIMER0_OVF_vect
#	define CLK1			_BV(CS00)
#	define CLK1024		_BV(CS02)|_BV(CS00)
#elif defined (__AVR_ATmega16__)
#ifndef RAMSTART
#	define RAMSTART 	0x60
#endif
#	define STACK_SIZE	64
#	define TIMER_REG	TCCR0
#	define TIMER_ENABLE	TIMSK
#	define TIMER_VECTOR	TIMER0_OVF_vect
#	define CLK1			_BV(CS00)
#	define CLK1024		_BV(CS02)|_BV(CS00)
#elif defined (__AVR_ATmega32__)
#ifndef RAMSTART
#	define RAMSTART 	0x60
#endif
#	define STACK_SIZE	96
#	define TIMER_REG	TCCR0
#	define TIMER_ENABLE	TIMSK
#	define TIMER_VECTOR	TIMER0_OVF_vect
#	define CLK1			_BV(CS00)
#	define CLK1024		_BV(CS02)|_BV(CS00)
#elif defined (__AVR_ATmega128__)
#ifndef RAMSTART
#	define RAMSTART 	0x100
#endif
#	define STACK_SIZE	128
#	define TIMER_REG	TCCR0
#	define TIMER_ENABLE	TIMSK
#	define TIMER_VECTOR	TIMER0_OVF_vect
#	define CLK1			_BV(CS00)
#	define CLK1024		_BV(CS02)|_BV(CS01)|_BV(CS00)
#elif defined (__AVR_ATmega2560__)
#ifndef RAMSTART
#	define RAMSTART 	0x200
#endif
#	define STACK_SIZE	128
#	define TIMER_REG	TCCR0B
#	define TIMER_ENABLE	TIMSK0
#	define TIMER_VECTOR	TIMER0_OVF_vect
#	define CLK1			_BV(CS00)
#	define CLK1024		_BV(CS02)|_BV(CS00)
#elif defined (__AVR_ATtiny44__)
#ifndef RAMSTART
#	define RAMSTART 	0x100
#endif
#	define STACK_SIZE	50
#	define TIMER_REG	TCCR0B
#	define TIMER_ENABLE	TIMSK0
#	define TIMER_VECTOR	TIM0_OVF_vect
#	define CLK1			_BV(CS00)
#	define CLK1024		_BV(CS02)|_BV(CS00)
#else
#	error "unsupported device in MCU.h"
#endif


#define NOP() asm volatile("nop");

#define ENABLE_INTERUPTS()		(__asm__ __volatile__ ("sei" ::: "memory"))
#define DISABLE_INTERRUPTS()	(__asm__ __volatile__ ("cli" ::: "memory"))


/*---------------------------------------------- Global Variables -------------------------------------------*/


/*--------------------------------------------- FUNCTION Definitions ----------------------------------------*/

/*************************************************************************************************************
* Function				: MCU_vidResetSrcCheck
* Description			: Check the source of last reset and perform necessary actions
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidResetSrcCheck(void);

/*************************************************************************************************************
* Function				: MCU_vidEnableInterrupts
* Description			: Enables the Global interrupt of the Micro controller taking in consideration
						  the Nested Critical sections
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidEnableInterrupts( void );

/*************************************************************************************************************
* Function				: MCU_vidDisableInterrupts
* Description			: Disables the Global interrupt of the Micro controller taking in
						  consideration the Nested Critical sections
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidDisableInterrupts(void);

/*************************************************************************************************************
* Function				: MCU_vidDelay_1_us
* Description			: Cause a delay of almost 1 us 
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidDelay_1_us(void);

/*************************************************************************************************************
* Function				: MCU_vidDelay_10_us
* Description			: Cause a delay of almost 10 us
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidDelay_10_us(void);

/*************************************************************************************************************
* Function				: MCU_vidResetCpu
* Description			: Cause a reset for the MCU
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None.
*
**************************************************************************************************************/
extern void MCU_vidResetCpu(void);


#endif /* MCU_H_ */