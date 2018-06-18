/*! \file LOG_uartLogger.h \brief UART logger library. */
/************************************************************************************************************
*
* File Name		: 'LOG_uartLogger.h'
* Title			: UART logger library
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/26/2018 5:22:32 AM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved
*
************************************************************************************************************/
#ifndef LOG_UARTLOGGER_H_
#define LOG_UARTLOGGER_H_

/*--------------------------------------------- INCLUDES --------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>

/*----------------------------------------- MACROS Definitions --------------------------------------------*/
#define SERIAL_DEBUGGER_BAUD_RATE__ 9600u
#define DBG_BUF_MAX_SIZE 100U
/* wrapper to print one line to the UART terminal*/
#define INFO(...) LOG_vidPrintLn((char*)__VA_ARGS__)

/*------------------------------------------ Global Variables ---------------------------------------------*/

/*------------------------------------ Global Functions Definitions----------------------------------------*/

/************************************************************************************************************
* Function				: LOG_vidInit
* Description			: Initialize the LOG_uartLogger module by initializing the UART channel and setting 
						  the stdout,stdin to the UART peripheral .
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void LOG_vidInit(void);

/************************************************************************************************************
* Function				: LOG_vidPrint
* Description			: Print a string to the UART terminal.
* Parameters[in]		: Multiple arguments that will be appended into a string and sent to the UART channel
* Parameters[in/out]	: None
* Parameters[out]		: None
*
Note : This function will initialize the default UART peripheral if it is not initialized
*************************************************************************************************************/
extern void LOG_vidPrint(char * format, ...);

/************************************************************************************************************
* Function				: LOG_vidPrintLn
* Description			: Print a string in one line to the UART terminal.
* Parameters[in]		: Multiple arguments that will be appended into a string and sent to the UART channel
* Parameters[in/out]	: None
* Parameters[out]		: None
*
Note : This function will initialize the default UART peripheral if it is not initialized
*************************************************************************************************************/
extern void LOG_vidPrintLn(char * format, ...);




#endif /* LOG_UARTLOGGER_H_ */