/*
 * main.c
 *
 *  Created on: Aug 14, 2023
 *      Author: larar
 */

//#include "../HAL/LED.h"
//#include "../HAL/buzzer.h"
#include "../HAL/keypad.h"
#include "../HAL/lcd.h"
//#include "../HAL/servo.h"
#include "../MCAL/dio.h"
#include "../MCAL/dio_config.h"
#include "../UTILS/STD_TYPES.h"
#include "../MCAL/USART.h"
#include "../MCAL/ADC.h"
#include "../HAL/EEPROM.h"
#include "../HAL/DC.h"
#include "admin.h"
#include "user.h"
#include <util/delay.h>



uint8 flag = 0;
uint8 password_user;
uint8 password_admin = 123;

uint8 user_entry_pass = 0;
uint16 user_entry_username;
uint8 admin_entry_pass = 0;

uint8 count = 0;
uint8 choice;

uint8 temp_entry = 25;

uint8 dig_read;

/*
 * flags:
 * 0->welcome
 *
 * 1->user enter user
 * 2->user username
 * 3->user enter pass
 * 4->user pass
 *
 * 101->admin enter pass
 * 102->admin pass
 *
 * 255-> admin/user
 */



int main (void){
	DIO_init();
	Keypad_vInit();
	LCD_vInit();
	USART_vInit();
	EEPROM_vInit();
	ADC_vInit();
	DC_vInit();

	LCD_vSendString("1- User Mode");
	LCD_vGoTo(1,0);
	LCD_vSendString("2- Admin Mode");

	while(1){
		uint8 key_pressed = Keypad_u8GetPressed();
		if (KEY_NOT_PRESSED != key_pressed && flag == 0){
			count = 0;
			if(key_pressed == '1'){
				LCD_vSendCmnd(0x01);
				flag = 1;
			}
			else if (key_pressed == '2'){
				LCD_vSendCmnd(0x01);
				flag = 101;
			}
		}


		/*
		 *
		 * USER
		 *
		 */
		if (flag == 1 && count < 3) {
			LCD_vSendString("Enter Username:");
			LCD_vGoTo(1,0);
			flag = 2;
			user_entry_username = 0;
		}

		if (flag == 2){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed != '='){
					LCD_vSendData(key_pressed);
					user_entry_username *= 10;
					user_entry_username += key_pressed - '0';
				}
				else{
					flag = 3;
					LCD_vSendCmnd(0x01);
				}
			}
		}


		if (flag == 3 && count < 3) {
			LCD_vSendString("Enter Password:");
			LCD_vGoTo(1,0);
			flag = 4;
			user_entry_pass = 0;
		}
		else if (flag == 3 && count >=3){
			BUZZER_On();
			_delay_ms(2000);
			BUZZER_Off();
			count = 0;
			flag = 0;
		}

		if (flag == 4){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed != '='){
					LCD_vSendData('*');
					user_entry_pass *= 10;
					user_entry_pass += key_pressed - '0';
				}
				else{
					flag = 5;
					count++;
					LCD_vSendInt(user_entry_pass);
					password_user = EEPROM_u8ReadByte(user_entry_username);
					if (user_entry_pass == password_user){
						LCD_vSendCmnd(0x01);
						LCD_vSendString(" Welcome User");
						_delay_ms(1000);

					}
					else{
						LCD_vSendString("Wrong Password");
						_delay_ms(1000);
						LCD_vSendCmnd(0x01);
						flag = 1;
					}
				}
			}
		}


		if (flag == 5){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("1. Temperature");
			LCD_vGoTo(1,0);
			LCD_vSendString("2. Next");
			flag = 6;
		}

		if (flag == 6){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed == '1'){
					flag = 50;
				}
				else if (key_pressed == '2'){
					flag = 7;
				}
			}
		}

		if (flag == 7){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("1. Room Lights");
			LCD_vGoTo(1,0);
			LCD_vSendString("2. Next");
			flag = 8;
		}
		if (flag == 8){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed == '1'){
					flag = 53;
				}
				else if (key_pressed == '2'){
					flag = 9;
				}
			}
		}

		if (flag == 9){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("1. Door");
			LCD_vGoTo(1,0);
			LCD_vSendString("2. Next");
			flag = 10;
		}

		if (flag == 10){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed == '1'){
					flag = 57;
				}
				else if (key_pressed == '2'){
					flag = 5;
				}
			}
		}

		/*
		 * USER ACTIONS
		 */

		ADC_vChannel_Select(0);
		ADC_vStart_Conversion();

		dig_read=0.25*ADC_u16PollingRead();

		if(dig_read > temp_entry){
			DC_vOn(DC_CLOCK_WISE);
			DC_vControlSpeed(50);
		}
		else{
			DC_vOff();
		}

		if(flag == 50){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("Enter Desired Temp:");
			LCD_vGoTo(1,0);
			temp_entry = 0;
			flag = 51;
		}

		if(flag == 51){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed != '='){
					LCD_vSendData(key_pressed);
					temp_entry *= 10;
					temp_entry += key_pressed - '0';
				}
				else{
					flag = 52;
					LCD_vSendCmnd(0x01);
				}
			}
		}

		if(flag == 52){
			temp(temp_entry);
			key_pressed = Keypad_u8GetPressed();
			if('-' == key_pressed){
				flag = 5;
			}
			else if('c' == key_pressed){
				flag = 255;
			}
		}

		if(flag == 53){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("Enter Room Num:");
			flag = 54;

		}

		if (flag == 54){
			choice = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != choice){
				if(choice <= '5' && choice >= '1'){
					flag = 55;
				}
				else if('-' == key_pressed){
					flag = 5;
				}
				else if('c' == key_pressed){
					flag = 255;
				}
			}
		}

		if(flag == 55){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("1. On");
			LCD_vGoTo(1,0);
			LCD_vSendString("2. Off");
			flag = 56;
		}

		if(flag == 56){
			key_pressed = KEY_NOT_PRESSED;
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed && ('1' == key_pressed || '2' == key_pressed)) {
				switch(choice){
				case '1':
					if(key_pressed == '1'){
						openledroom1();
					}
					else if (key_pressed == '2'){
						closeledroom1();
					}
					break;
				case '2':
					if(key_pressed == '1'){
						openledroom2();
					}
					else if (key_pressed == '2'){
						closeledroom2();
					}
					break;
				case '3':
					if(key_pressed == '1'){
						openledroom3();
					}
					else if (key_pressed == '2'){
						closeledroom3();
					}
					break;
				case '4':
					if(key_pressed == '1'){
						openledroom4();
					}
					else if (key_pressed == '2'){
						closeledroom4();
					}
					break;
				case '5':
					if(key_pressed == '1'){
						openledroom5();
					}
					else if (key_pressed == '2'){
						closeledroom5();
					}
					break;
				}
			}
			else if('-' == key_pressed){
				flag = 5;
			}
			else if('c' == key_pressed){
				flag = 255;
			}
		}

		if(flag == 57){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("1. Open");
			LCD_vGoTo(1,0);
			LCD_vSendString("2. Close");
			flag = 58;
		}

		if(flag == 58){
			key_pressed = Keypad_u8GetPressed();
			if(KEY_NOT_PRESSED != key_pressed){
				if(key_pressed == '1'){
					OpenDoor();
				}
				else if (key_pressed == '2'){
					CloseDoor();
				}
				else if (key_pressed == 'c'){
					flag = 255;
				}
				else if (key_pressed == '-'){
					flag = 5;
				}
			}
		}


		/*
		 *
		 * ADMIN
		 *
		 */

		if (flag == 101 && count < 3) {
			LCD_vSendString("Enter Password:");
			LCD_vGoTo(1,0);
			flag = 102;
			admin_entry_pass = 0;
		}
		else if(flag == 101 && count >= 3){
			BUZZER_On();
			_delay_ms(2000);
			BUZZER_Off();
			count = 0;
			flag = 0;
		}

		if (flag == 102){
			key_pressed = Keypad_u8GetPressed();
			if (KEY_NOT_PRESSED != key_pressed) {
				if(key_pressed != '='){
					LCD_vSendData('*');
					admin_entry_pass *= 10;
					admin_entry_pass += key_pressed - '0';
				}
				else{
					count++;
					LCD_vSendInt(admin_entry_pass);

					if (admin_entry_pass == password_admin){
						LCD_vSendCmnd(0x01);
						LCD_vSendString("Welcome Admin");
						flag = 103;
					}
					else{
						LCD_vSendCmnd(0x01);
						LCD_vSendString("Wrong Password");
						_delay_ms(1000);
						LCD_vSendCmnd(0x01);
						flag = 101;
					}
				}
			}
		}
		if (flag == 103) {
			uint8 exit_flag = 0;
			while(exit_flag != 255){
				exit_flag = admin_mode();
			}

			flag = 255;

		}






		/*
		 * GENERAL
		 */

		if (flag == 255){
			LCD_vSendCmnd(0x01);
			LCD_vSendString("1- User Mode");
			LCD_vGoTo(1,0);
			LCD_vSendString("2- Admin Mode");
			flag = 0;
		}
	}
}
