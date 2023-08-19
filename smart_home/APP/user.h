/*
 * user.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Kimo Store
 */

#ifndef APP_USER_H_
#define APP_USER_H_

#include "../HAL/servo.h"


void OpenDoor(void);
void CloseDoor(void);
void openledroom1();
void closeledroom1();
void openledroom2();
void closeledroom2();
void openledroom3();
void closeledroom3();
void openledroom4();
void closeledroom4();
void openledroom5();
void closeledroom5();
void BUZZER_On(void);
void BUZZER_Off(void);

void temp(uint8 temperature);



#endif /* APP_USER_H_ */
