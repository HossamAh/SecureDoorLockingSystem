################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer_Timer.c \
../MCU2.c \
../MOTOR_TIMER.c \
../app_eeprom.c \
../app_uart.c \
../external_eeprom.c \
../i2c.c \
../timer.c \
../uart.c 

OBJS += \
./Buzzer_Timer.o \
./MCU2.o \
./MOTOR_TIMER.o \
./app_eeprom.o \
./app_uart.o \
./external_eeprom.o \
./i2c.o \
./timer.o \
./uart.o 

C_DEPS += \
./Buzzer_Timer.d \
./MCU2.d \
./MOTOR_TIMER.d \
./app_eeprom.d \
./app_uart.d \
./external_eeprom.d \
./i2c.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


