/*
 * AfrSys.c
 *
 * Created: 2/8/2018 1:57:15 AM
 * Author : mabdelr2
 */ 




#include "MCU.h"

#include <util/delay.h>


#include "DIO.h"
#include "SCI_uart.h"
#include "SPI.h"
#include "LOG_uartLogger.h"
#include "adc.h"
#include "TIM_timers.h"


int main(void)
{
	uint16 u16AdcVal=0;
	//uint8 u8ValStr [20];
	
	DIO_vidSetPinMode(DIO_PC2, OUTPUT);
	DIO_vidSetPinMode(DIO_PB1, OUTPUT);
	DIO_vidSetPinMode(DIO_PC0, INPUT);
	
	DDRB = 0x06;                      // Set Port PB1 and PB2 as Output
	
	MCU_vidDisableInterrupts();
	
	UART_init(9600U);
	SPI_vidMasterInit();
	
	
	TIM_vidT1PWMInit(8, TIM1_CHA_CHB_NON_INVERTING, TIM1_1024_PRESCALER);
	
	TIM_vidT1PwmASetDuty(127);
	TIM_vidT1PwmBSetDuty(127);

	//ADC_vidInit();
	
	MCU_vidEnableInterrupts();


		

	//int input=23765;
	int fVolt;

	MCU_vidResetSrcCheck();

	while(1) {
		INFO("logger test! \n");
		SPI_eSendByte(0x01);
				
		_delay_ms(1000);
	}
	//uint32 temp;

	//INFO("ADC Read : \n");
	//u16AdcVal = ADC_u16Read(0);/* read channel zero where the temp sensor is connect */
	//temp = ((u16AdcVal*5)/(1023))*10; /* calculate the temp from the ADC value*/
	//INFO("ADC VAL : %d", u16AdcVal );
		
	
	while(1){
		
		u16AdcVal = ADC_u16Read(0);/* read channel zero where the temp sensor is connect */
		//temp = ((u16AdcVal*5)/(1023))*10; /* calculate the temp from the ADC value*/
		INFO("ADC VAL : %d", u16AdcVal );
		//INFO("Tmp VAL : %d", temp );
		_delay_ms(1000);
	}
	
	while(0) {
		
		//PORTC &= ~(1<<PINC3); /* LED on */
		//UART_sendByte('A');
		//DIO_vidDigitalPinToggle(DIO_PC2);
		//DIO_vidDigitalPinWrite(DIO_PC0, HIGH);
		//printNumber(2345,10);
		//UART_sendString();
		//UART_sendString("\r\n");
		//UART_sendString("ADC VAL : ");
		
		u16AdcVal = ADC_u16Read(0);
		fVolt=(u16AdcVal*5.00)/1023;
		INFO("ADC VAL : %d", u16AdcVal );
		INFO("volt VAL : %d", fVolt );
		//printNumber(u16AdcVal,10);
		//UART_sendString("\r\n");
		//UART_sendString(
		_delay_ms(1000);
		DIO_vidDigitalPinWrite(DIO_PB2,LOW);
		//SPI_eSendByte('A');
		_delay_ms(10);
		DIO_vidDigitalPinWrite(DIO_PB2,HIGH);
		//PORTC |= 1<<PINC3; /* LED off */
		//DIO_vidDigitalPinWrite(DIO_PC0, LOW);
		//_delay_ms(900);
	}
	
	while(1){
		
	}
	return 0;
}

