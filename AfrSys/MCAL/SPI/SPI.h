/*! \file SPI_master.h \brief SPI function library. */
/************************************************************************************************************
*
* File Name		: 'SPI_master.h'
* Title			: SPI function library.
* Author		: Mohamed Abd El-Raouf - Copyright (C) 2018-2020
* Created		: 2/16/2018 8:27:16 PM
* Revised		: 3/22/2018 8:35:00 PM
* Version		: 1.0
* Target MCU	: Atmel AVR Series
*
* COPYRIGHT 2018  DEC-LLC All Rights Reserved
*
************************************************************************************************************/

#ifndef SPI_H_
#define SPI_H_

/*------------------------------------------------- INCLUDES ----------------------------------------------*/

#include "MCU.h"
#include "DIO.h"
#include "Std_Types.h"

/*--------------------------------------------- MACROS Definitions -----------------------------------------*/

#define u8SPI_TX_BUFFER_SIZE   ((uint8)150)
#define u8SPI_RX_BUFFER_SIZE   ((uint8)150)

#define SPI_TIME_OUT		   ((uint8)40)

#define SPI_CMD_SET_PIN 0x1000
#define SPI_CMD_SENDRECEIVE 0x2000
#define SPI_PIN_VALUE_BIT 0x0800

//SPI PORT&PIN Config
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_MISO	PB4
#define SPI_MOSI	PB3
#define SPI_SCK		PB5
#define SPI_SS		PB2

/*------------------------------------------ Type Definitions  ------------------------------------------------*/

typedef enum{
	SPI_MASTER_MODE,
	SPI_SLAVE_MODE
}enutSpiModes;

/*---------------------------------------------- Global Variables -----------------------------------------*/


/*-------------------------------------------- FUNCTION Definitions ---------------------------------------*/

/************************************************************************************************************
* Function				: SPI_vidMasterInit
* Description			: SPI initialization routine in master mode.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void SPI_vidMasterInit(void);

/************************************************************************************************************
* Function				: SPI_vidSlaveInit
* Description			: SPI initialization routine in slave mode.
* Parameters[in]		: None
* Parameters[in/out]	: None
* Parameters[out]		: None
*
*************************************************************************************************************/
extern void SPI_vidSlaveInit(void);

/************************************************************************************************************
* Function				: SPI_eSendByte
* Description			: Send one byte via SPI.
* Parameters[in]		: [u8Data] a byte to transmit.
* Parameters[in/out]	: None
* Parameters[out]		: STD_ERR_T completion error status
*
*************************************************************************************************************/
extern STD_ERR_T SPI_eSendByte(uint8 u8Data);




#endif /* SPI_H_ */