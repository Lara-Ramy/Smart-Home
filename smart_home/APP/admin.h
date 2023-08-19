/*
 * admin.h
 *
 *  Created on: Aug 14, 2023
 *      Author: larar
 */

#ifndef APP_ADMIN_H_
#define APP_ADMIN_H_

#include "../UTILS/STD_TYPES.h"

uint8 admin_mode();
uint8* int_to_string(uint8 data);
uint8 string_to_int(uint8* data);

#endif /* APP_ADMIN_H_ */
