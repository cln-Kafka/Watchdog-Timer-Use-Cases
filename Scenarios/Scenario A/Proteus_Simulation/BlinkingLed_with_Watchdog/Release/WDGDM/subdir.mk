################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../WDGDM/WDGM.c 

OBJS += \
./WDGDM/WDGM.o 

C_DEPS += \
./WDGDM/WDGM.d 


# Each subdirectory must supply rules for building sources it contributes
WDGDM/%.o: ../WDGDM/%.c WDGDM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Desktop\nouran\SBME\SBME 3.2\embedded\Final Project\avr final 4\BlinkingLED_with_Watchdog-main\BlinkingLed_with_Watchdog\gpio" -I"D:\Desktop\nouran\SBME\SBME 3.2\embedded\Final Project\avr final 4\BlinkingLED_with_Watchdog-main\BlinkingLed_with_Watchdog\WDGDM" -I"D:\Desktop\nouran\SBME\SBME 3.2\embedded\Final Project\avr final 4\BlinkingLED_with_Watchdog-main\BlinkingLed_with_Watchdog\WDGDrv" -I"D:\Desktop\nouran\SBME\SBME 3.2\embedded\Final Project\avr final 4\BlinkingLED_with_Watchdog-main\BlinkingLed_with_Watchdog\LEDMgr" -Wall -g3 -gdwarf-2 -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


