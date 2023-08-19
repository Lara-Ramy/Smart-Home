################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/DC.c \
../HAL/EEPROM.c \
../HAL/LED.c \
../HAL/buzzer.c \
../HAL/keypad.c \
../HAL/lcd.c \
../HAL/servo.c 

OBJS += \
./HAL/DC.o \
./HAL/EEPROM.o \
./HAL/LED.o \
./HAL/buzzer.o \
./HAL/keypad.o \
./HAL/lcd.o \
./HAL/servo.o 

C_DEPS += \
./HAL/DC.d \
./HAL/EEPROM.d \
./HAL/LED.d \
./HAL/buzzer.d \
./HAL/keypad.d \
./HAL/lcd.d \
./HAL/servo.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


