################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_ECU.c \
../app_uart.c \
../keypad.c \
../keypad_UART.c \
../lcd.c \
../lcd_timer.c \
../timer.c \
../uart.c 

OBJS += \
./HMI_ECU.o \
./app_uart.o \
./keypad.o \
./keypad_UART.o \
./lcd.o \
./lcd_timer.o \
./timer.o \
./uart.o 

C_DEPS += \
./HMI_ECU.d \
./app_uart.d \
./keypad.d \
./keypad_UART.d \
./lcd.d \
./lcd_timer.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


