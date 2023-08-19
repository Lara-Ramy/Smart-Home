################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ADC.c \
../MCAL/I2C.c \
../MCAL/USART.c \
../MCAL/dio.c \
../MCAL/dio_config.c \
../MCAL/general_interrupt.c \
../MCAL/timer0.c \
../MCAL/timer1.c 

OBJS += \
./MCAL/ADC.o \
./MCAL/I2C.o \
./MCAL/USART.o \
./MCAL/dio.o \
./MCAL/dio_config.o \
./MCAL/general_interrupt.o \
./MCAL/timer0.o \
./MCAL/timer1.o 

C_DEPS += \
./MCAL/ADC.d \
./MCAL/I2C.d \
./MCAL/USART.d \
./MCAL/dio.d \
./MCAL/dio_config.d \
./MCAL/general_interrupt.d \
./MCAL/timer0.d \
./MCAL/timer1.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


