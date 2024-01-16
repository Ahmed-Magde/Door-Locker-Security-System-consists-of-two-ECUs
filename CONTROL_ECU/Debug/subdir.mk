################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../control.c \
../control_app.c \
../dc_motor.c \
../external_eeprom.c \
../gpio.c \
../pwm.c \
../timer.c \
../twi.c \
../uart.c 

OBJS += \
./buzzer.o \
./control.o \
./control_app.o \
./dc_motor.o \
./external_eeprom.o \
./gpio.o \
./pwm.o \
./timer.o \
./twi.o \
./uart.o 

C_DEPS += \
./buzzer.d \
./control.d \
./control_app.d \
./dc_motor.d \
./external_eeprom.d \
./gpio.d \
./pwm.d \
./timer.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


