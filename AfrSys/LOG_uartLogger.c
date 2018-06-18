/*! \file LOG_uartLogger.c \brief UART logger library. */
/************************************************************************************************************
*
* File Name		: 'LOG_uartLogger.c'
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

/*--------------------------------------------- INCLUDES --------------------------------------------------*/
#include "SCI_uart.h"
#include "LOG_uartLogger.h"

/*----------------------------------------- MACROS Definitions --------------------------------------------*/

/*-------------------------------------Static functions Declarations --------------------------------------*/

static void uart_putchar(char c, FILE *stream);
static char uart_getchar(FILE *stream);

/*------------------------------------------ Global Variables ---------------------------------------------*/

boolean bLoggerInitialized = FALSE;
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
FILE uart_io = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

/*-------------------------------------Static functions Definitions ---------------------------------------*/

static void uart_putchar(char c, FILE *stream) {
	if (c == '\n') {
		uart_putchar('\r', stream);
	}
	UART_sendByte(c);
}

static char uart_getchar(FILE *stream) {
	return UART_recieveByte();
}

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
extern void LOG_vidInit(void){
	    UART_init(SERIAL_DEBUGGER_BAUD_RATE__);
		stdout = &uart_output;
		stdin  = &uart_input;
	    bLoggerInitialized = TRUE;
}


/************************************************************************************************************
* Function				: LOG_vidPrint
* Description			: Print a string to the UART terminal.
* Parameters[in]		: Multiple arguments that will be appended into a string and sent to the UART channel
* Parameters[in/out]	: None
* Parameters[out]		: None
*
Note : This function will initialize the default UART peripheral if it is not initialized
*************************************************************************************************************/
extern void LOG_vidPrint(char * format, ...){
	if ( bLoggerInitialized == FALSE ){
		LOG_vidInit();
		bLoggerInitialized = TRUE;
	}
	char debugMsg[DBG_BUF_MAX_SIZE];
	va_list ap;
	va_start(ap, format);
	vsnprintf(debugMsg, DBG_BUF_MAX_SIZE, format, ap);
	printf(debugMsg);
	va_end(ap);

}

/************************************************************************************************************
* Function				: LOG_vidPrintLn
* Description			: Print a string in one line to the UART terminal.
* Parameters[in]		: Multiple arguments that will be appended into a string and sent to the UART channel
* Parameters[in/out]	: None
* Parameters[out]		: None
*
Note : This function will initialize the default UART peripheral if it is not initialized
*************************************************************************************************************/
extern void LOG_vidPrintLn(char * format, ...){
	if ( bLoggerInitialized == FALSE ){
		LOG_vidInit();
		bLoggerInitialized = TRUE;
	}
	char debugMsg[DBG_BUF_MAX_SIZE];
	va_list ap;
	va_start(ap, format);
	vsnprintf(debugMsg, DBG_BUF_MAX_SIZE, format, ap);
	printf("%s\r",debugMsg);
	va_end(ap);
}