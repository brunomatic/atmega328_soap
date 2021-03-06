################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../battery.c \
../eeprom_control.c \
../ir_gate.c \
../main.c \
../power_control.c \
../tests.c \
../timer.c \
../uart.c 

OBJS += \
./battery.o \
./eeprom_control.o \
./ir_gate.o \
./main.o \
./power_control.o \
./tests.o \
./timer.o \
./uart.o 

C_DEPS += \
./battery.d \
./eeprom_control.d \
./ir_gate.d \
./main.d \
./power_control.d \
./tests.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


