/*! \file Common_Macros.h \brief common macros that are most commonly used in all other components */
/**********************************************************************************************************
*
* File Name		: 'Common_Macros.h'
* Title			: Common macros that are most commonly used in all other components
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/9/2018 3:33:02 PM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved
*
************************************************************************************************************/
#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define STD_ERR_OK		254U
#define STD_ERR_NOK		255U

#define TRUE	1U
#define FALSE	0U

#define PI			(3.141592653589793238462643383279500)
#define HALF_PI		(1.570796326794896619231321691639800)
#define TWO_PI		(6.283185307179586476925286766559000)
#define DEG_TO_RAD	(0.017453292519943295769236907684886)
#define RAD_TO_DEG	(57.29577951308232087679815481410500)

#define MIN(A,B)		((A)<(B)?(A):(B))
#define MAX(A,b)		((A)>(B)?(A):(B))
#define ABS(X)			((X)>0?(X):-(X))
#define CONSTRAIN		(VAL,LOWEST,HIGHEST) ((VAL)<(LOWEST)?(LOWEST):((VAL)>(HIGHEST)?(HIGHEST):(VAL)))
#define ROUND(X)		((X)>=0?(long)((X)+0.5f):(long)((X)-0.5f))
#define RADIANS(DEG)	((DEG)*DEG_TO_RAD)
#define DEGREES(RAD)	((RAD)*RAD_TO_DEG)
#define SQUARE(X)		((X)*(X))

#define SET_BIT(REG,BIT)			(REG |= 1<<BIT)
#define CLEAR_BIT(REG,BIT)			(REG &= ~(1<<BIT))
#define SET_BIT_HIGH(REG,BIT)		(SET_BIT(REG,BIT))
#define SET_BIT_LOW(REG,BIT)		(CLEAR_BIT(REG,BIT))
#define TOGGLE_BIT(REG,BIT)			(REG = REG ^ (1<<BIT) )
#define WRITE_BIT_VAL(REG, BIT,VAL)	(VAL ? SET_BIT(REG,BIT) : CLEAR_BIT(REG,BIT))
#define READ_BIT_VAL(REG, BIT)		(((REG) >> (BIT)) & 0x01)

#define WRITE_REG_VAL(REG, VAL)     (REG = VAL)
#define	inb(addr)			(addr)

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


#endif /* COMMON_MACROS_H_ */