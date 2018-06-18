/*! \file SCI_uart.h \brief UART driver with receive/transmit function library. */
/************************************************************************************************************
*
* File Name		: 'SCI_uart.h'
* Title			: Interrupt Driven UART driver with receive/transmit circular buffers
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/10/2018 1:08:57 AM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved 
*
************************************************************************************************************/


#ifndef SCI_UART_H_
#define SCI_UART_H_

/*--------------------------------------------- INCLUDES --------------------------------------------------*/

#include "Std_Types.h"


/*----------------------------------------- MACROS Definitions --------------------------------------------*/

#define u8TX_BUFFER_SIZE  100U
#define u8RX_BUFFER_SIZE  100U

/*------------------------------------------ Global Variables ---------------------------------------------*/

/*---------------------------------------- FUNCTION Definitions -------------------------------------------*/


/************************************************************************************************************
* Function				: UART_init
* Description			: Initialize UART by double transmission speed, enable UART as transmitter and receiver, 
						  set UART to 8-bit data, NO parity, one stop bit and async and set baud rate.
* Parameters[in]		: [u16BaudRate] desired baud rate
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_init(uint16 u16BaudRate);

/************************************************************************************************************
* Function				: UART_sendByte
* Description			: Wait for UDRE flag to be set indicating that the buffer is empty and ready for 
						  transmitting then send one byte.
* Parameters[in]		: [u8Char] the data byte to send through UART
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_sendByte(uint8 u8Char);

/************************************************************************************************************
* Function				: UART_sendString
* Description			: Send a string via UART in interrupt driven manner using buffers to store the string
						  and start sending one byte. After first one byte is sent the interrupt is generated
						  and the following byte will be transmitted from the ISR till all bytes stored in the
						  TX buffer are sent
* Parameters[in]		: [u8ptrTxString] pointer to the string to be sent through UART
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_sendString(const char *u8ptrTxString);

/************************************************************************************************************
* Function				: UART_sendByte
* Description			: Blocking receive one byte from UART.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: [u8Char] the data byte received from the UART channel
*
*************************************************************************************************************/
extern char UART_recieveByte(void);

/************************************************************************************************************
* Function				: UART_receiveString
* Description			: Blocking receive string until a certain delimiter is received from UART.
* Parameters[in]		: None
* Parameters[in/out]	: [a_str_Ptr] pointer to a buffer to store the incoming string from UART
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_receiveString(char *a_str_Ptr);


#endif /* SCI_UART_H_ */