################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LEDMgr/LEDM.c 

OBJS += \
./LEDMgr/LEDM.o 

C_DEPS += \
./LEDMgr/LEDM.d 


# Each subdirectory must supply rules for building sources it contributes
LEDMgr/%.o: ../LEDMgr/%.c LEDMgr/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"K:\BlinkingLED_with_Watchdog\BlinkingLed_with_Watchdog\gpio" -I"K:\BlinkingLED_with_Watchdog\BlinkingLed_with_Watchdog\WDGDM" -I"K:\BlinkingLED_with_Watchdog\BlinkingLed_with_Watchdog\WDGDrv" -I"K:\BlinkingLED_with_Watchdog\BlinkingLed_with_Watchdog\LEDMgr" -Wall -g3 -gdwarf-2 -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


