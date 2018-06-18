/*! \file SCI_uart.c \brief UART driver with receive/transmit function library. */
/*************************************************************************************************************
*
* File Name		: 'SCI_uart.c'
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

/*--------------------------------------------- INCLUDES --------------------------------------------------*/

#include "SCI_uart.h"
#include "DIO.h"
#include "MCU.h"
#include "string.h"

/*----------------------------------------- MACROS Definitions --------------------------------------------*/
/** brief  UART Baud rate Expression
 *  param1  xtal cpu  system clock in Mhz, e.g. 4000000L for 4Mhz          
 *  param2  baud rate baud rate in bps, e.g. 1200, 2400, 9600     
 */
#define UART_BAUD_SELECT(u16BAUD_RATE,CPU_CLK) ((CPU_CLK)/((u16BAUD_RATE)*16l)-1)
#define UART_BAUD_SELECT_DOUBLE_SPEED(u16BAUD_RATE,CPU_CLK) (((CPU_CLK)/((u16BAUD_RATE)*8l)-1)|0x8000)



/*------------------------------------------ Global Variables ---------------------------------------------*/

uint8 au8UartTransmitBuffer[u8TX_BUFFER_SIZE]={0};
uint8 u8TransmitBufferIndex = 0;

uint8 au8UartReceiveBuffer[u8RX_BUFFER_SIZE]={0};
uint8 u8ReceiveBufferIndex = 0;

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
extern void UART_init(uint16 u16BaudRate)
{
	/*double transmission speed */
	SET_BIT(UCSRA,U2X);
	
	/* enable UART as transmitter and receiver */
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	/* enable UART as transmitter and receiver interrupts*/
	SET_BIT(UCSRB,RXCIE);
	SET_BIT(UCSRB,TXCIE);
	
	/* 8-bit data, NO parity, one stop bit and async*/
	SET_BIT(UCSRC,URSEL);
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	
	/* baud rate=9600 & Fosc=1MHz -->  UBBR=( Fosc / (8 * baud rate) ) - 1 = 12 */
	uint16 UBBR_VAL = UART_BAUD_SELECT_DOUBLE_SPEED(u16BaudRate, F_CPU);
	UBBR_VAL &= ~0x8000;
	UBRRH = (uint8)(UBBR_VAL>>8);
	UBRRL = (uint8)UBBR_VAL;
}

/************************************************************************************************************
* Function				: UART_sendByte
* Description			: Wait for UDRE flag to be set indicating that the buffer is empty and ready for 
						  transmitting then send one byte.
* Parameters[in]		: [u8Char] the data byte to send through UART
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_sendByte(uint8 u8Char)
{
	/*UDRE flag is set when the buffer is empty and 
	ready for transmitting a new byte so wait until this flag is set to one*/
	while(!(UCSRA & (1<<UDRE))){}
	SET_BIT(UCSRB,TXEN);  /// test
	UDR = u8Char;
	CLEAR_BIT(UCSRB,TXEN); /// test
}

/************************************************************************************************************
* Function				: UART_sendByte
* Description			: Blocking receive one byte from UART.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: [u8Char] the data byte received from the UART channel
*
*************************************************************************************************************/
extern char UART_recieveByte(void)
{
	/*RXC flag is set when the UART receive data so until this flag is set to one*/
	SET_BIT(UCSRB,RXEN); /// test
	while(!(UCSRA & (1<<RXC))){}
	CLEAR_BIT(UCSRB,RXEN); /// test
	return UDR;
}

/************************************************************************************************************
* Function				: UART_sendString
* Description			: Send a string via UART in interrupt driven manner using buffers to store the string
						  and start sending one byte. After first one byte is sent the interrupt is generated
						  and the following byte will be transmitted from the ISR till all bytes stored in the
						  TX buffer are sent
* Parameters[in]		: [u8ptrTxString] pointer to the string to send through UART
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_sendString(const char *u8ptrTxString)
{
	strcpy(au8UartTransmitBuffer,u8ptrTxString);
	UART_sendByte(u8ptrTxString[0]);
}

/************************************************************************************************************
* Function				: UART_receiveString
* Description			: Blocking receive string until a certain delimiter is received from UART.
* Parameters[in]		: None
* Parameters[in/out]	: [a_str_Ptr] pointer to a buffer to store the incoming string from UART
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void UART_receiveString(char *a_str_Ptr)
{
	unsigned char i = 0;
	a_str_Ptr[i] = UART_recieveByte();
	while(a_str_Ptr[i] != '#')
	{
		i++;
		a_str_Ptr[i] = UART_recieveByte();
	}
	a_str_Ptr[i] = '#';
}

ISR(USART_TXC_vect){
	u8TransmitBufferIndex++;
	if(au8UartTransmitBuffer[u8TransmitBufferIndex] != '\0'){
		UART_sendByte(au8UartTransmitBuffer[u8TransmitBufferIndex]);
	} else {
		u8TransmitBufferIndex = 0;
		memset(au8UartTransmitBuffer, '\0',u8TX_BUFFER_SIZE);
	}
}

ISR(USART_RXC_vect){
	char recData=UDR;
	if(recData == '\r' || recData == '\n'){			
	} else {	
		if(u8ReceiveBufferIndex <= u8RX_BUFFER_SIZE){
			au8UartReceiveBuffer[u8ReceiveBufferIndex]=recData;
			u8ReceiveBufferIndex++;
		} else {
							
		}		
	}
}

