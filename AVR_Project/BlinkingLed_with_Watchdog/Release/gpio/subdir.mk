################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gpio/gpio.c 

OBJS += \
./gpio/gpio.o 

C_DEPS += \
./gpio/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
gpio/%.o: ../gpio/%.c gpio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\AVR_Project\BlinkingLed_with_Watchdog\gpio" -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\AVR_Project\BlinkingLed_with_Watchdog\LEDMgr" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


