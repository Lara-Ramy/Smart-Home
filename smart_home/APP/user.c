/*
 * user.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Kimo Store
 */

#include "user.h"
#include "../MCAL/dio.h"
#include "../MCAL/ADC.h"
#include "../HAL/DC.h"
#include "../HAL/lcd.h"
#include <avr/delay.h>

void OpenDoor(void)
{
	Servo_vOn(180);
}

void CloseDoor(void)
{
	Servo_vOn(90);
}

void openledroom1()
{
	DIO_WriteChannel(PA1,HIGH);
}

void closeledroom1()
{
	DIO_WriteChannel(PA1,LOW);
}

void openledroom2()
{
	DIO_WriteChannel(PA4,HIGH);
}

void closeledroom2()
{
	DIO_WriteChannel(PA4,LOW);
}

void openledroom3()
{
	DIO_WriteChannel(PA5,HIGH);
}

void closeledroom3()
{
	DIO_WriteChannel(PA5,LOW);
}

void openledroom4()
{
	DIO_WriteChannel(PA6,HIGH);
}

void closeledroom4()
{
	DIO_WriteChannel(PA6,LOW);
}

void openledroom5()
{
	DIO_WriteChannel(PA7,HIGH);
}

void closeledroom5()
{
	DIO_WriteChannel(PA7,LOW);
}

void BUZZER_On(void)
{
	DIO_WriteChannel(PC6,HIGH);
}
void BUZZER_Off(void)
{
	DIO_WriteChannel(PC6,LOW);
}

void temp(uint8 temperature)
{
	uint16 Local_dig_read;
	uint16 temp;
	ADC_vChannel_Select(0);
	ADC_vStart_Conversion();

	Local_dig_read=ADC_u16PollingRead();
	//	temp =((uint32)Local_dig_read*2560UL)/1024;
	temp =0.25*Local_dig_read;
	LCD_vSendCmnd(0x01);
	LCD_vSendString("Current:");
	LCD_vSendInt(temp);
	LCD_vGoTo(1,0);
	LCD_vSendString("Desired:");
	LCD_vSendInt(temperature);
	_delay_ms(50);


	// if temp is higher than 28 open fan & print fan on in lcd
	if(temp>temperature)
	{
		DC_vOn(DC_CLOCK_WISE);
		DC_vControlSpeed(50);
	}

	// if temp is lower than 28 open fan & print fan of in lcd
	else if(temp<=temperature)
	{
		DC_vOff();
	}
}

