/*! \file SPI_master.h \brief SPI function library. */
/************************************************************************************************************
*
* File Name		: 'SPI_master.c'
* Title			: SPI function library.
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/16/2018 8:26:56 PM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved
*
************************************************************************************************************/

/*------------------------------------------------- INCLUDES ----------------------------------------------*/

#include "SPI.h"

/*--------------------------------------------- MACROS Definitions -----------------------------------------*/


/*---------------------------------------------- Global Variables -----------------------------------------*/

#if 0
static uint8 au8SpiTransmitBuffer[u8SPI_TX_BUFFER_SIZE]={0};
static uint8 u8TransmitBufferIndex = 0;

static uint8 au8UartReceiveBuffer[u8SPI_RX_BUFFER_SIZE]={0};
static uint8 u8ReceiveBufferIndex = 0;
#endif


/*-------------------------------------------- FUNCTION Definitions ---------------------------------------*

/************************************************************************************************************
* Function				: SPI_vidMasterInit
* Description			: SPI initialization routine in master mode.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void SPI_vidMasterInit(void) {   
	/*Set MOSI, SS, SCK as output*/
    SPI_DDR |= ((1<<SPI_MOSI) | (1<<SPI_SS) | (1<<SPI_SCK));
	/*Set MISO as input*/
	SPI_DDR &= ~((1<<SPI_MISO)); 
	/*set MISO to pull up */ 
	SPI_PORT |= (1<<SPI_MISO);
    SPCR = ((1<<SPE) |              /* SPI Enable */
            (1<<SPIE)|              /* SPI Interrupt Enable */
            (0<<DORD)|              /* Data Order (0:MSB first / 1:LSB first) */
            (1<<MSTR)|              /* Master/Slave select 1:master , 0:slave */
            (1<<SPR1)|(1<<SPR0)|    /* SPI Clock Rate */
            (0<<CPOL)|              /* Clock Polarity (0:SCK low / 1:SCK hi when idle) */
            (0<<CPHA));             /* Clock Phase (0:leading / 1:trailing edge sampling) */
    SPSR = (0<<SPI2X);				/* Double SPI Speed Bit */
}

/************************************************************************************************************
* Function				: SPI_eSendByte
* Description			: Send one byte via SPI.
* Parameters[in]		: [u8Data] a byte to transmit.
* Parameters[in/out]	: None
* Parameters[out]		: STD_ERR_T completion error status
*
*************************************************************************************************************/
extern STD_ERR_T SPI_eSendByte(uint8 u8Data){
	uint8 u8TimeOut = SPI_TIME_OUT;
	STD_ERR_T errRetVal = STD_ERR_NOK;
	
	SPDR = u8Data;
	while( !(SPSR & (1<<SPIF)) && (u8TimeOut !=0 )){
		u8TimeOut--;
	}
	if(u8TimeOut != 0){
		errRetVal = STD_ERR_OK;
	}
	return 	errRetVal;
}

//TODO::handle receive and transmit
ISR(SPI_STC_vect){
	
	
	DIO_vidDigitalPinToggle(DIO_PC2);
}