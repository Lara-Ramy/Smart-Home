/*
 * admin.c
 *
 *  Created on: Aug 14, 2023
 *      Author: larar
 */

#include "admin.h"
#include "../UTILS/STD_TYPES.h"
#include "../MCAL/USART.h"
#include "../HAL/EEPROM.h"

uint8 admin_mode()
{
	uint8 Local_Choice =0;
	uint8 Local_pass[4];
	uint8 Local_send2eep;
	uint8 var1;
	uint8 opt1[10] = "1.Add    ";
	uint8 opt2[10] = "2.Delete    ";
	uint8 opt3[10] = "3.Exit";
	uint8 Local_ID;
	UART_SendString("Choose:   ");
	UART_SendString(opt1);
	UART_SendString(opt2);
	UART_SendString(opt3);
	Local_Choice = USART_u16Receive();

	switch(Local_Choice-48)
	{
	case 1:
		UART_SendString("     Enter The ID:  ");
		while(var1==0)
		{
			var1 = USART_u16Receive()-48;
		}
		Local_ID = var1;

		UART_SendString("    Enter Password:  ");

		UART_RecString(&Local_pass[0]);
		UART_SendString(&Local_pass[0]);

		Local_send2eep=string_to_int(Local_pass);
		USART_vTransmit(Local_send2eep);
		EEPROM_vWriteByte(Local_ID, Local_send2eep);

		break;
	case 2:
		UART_SendString("Enter The ID:  ");
		Local_ID = USART_u16Receive()-48;
		EEPROM_vWriteByte(Local_ID, 0);
		break;
	case 3:
		return 255;
		break;
	}

}
uint8* int_to_string(uint8 data)
{
	uint8 buff[3];
	buff[0]=data/100;
	buff[1]=(data/10)-buff[0];
	buff[2]=(data)-buff[0]-buff[1];
	return buff;
}

uint8 string_to_int(uint8* data)
{
	uint8 Wdata;
	Wdata = (data[2]-48) +(data[1]-48)*10+(data[0]-48)*100;

	return Wdata;
}
