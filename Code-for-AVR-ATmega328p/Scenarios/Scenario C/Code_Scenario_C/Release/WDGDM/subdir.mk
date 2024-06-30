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
	avr-gcc -I"K:\ReposClone\Watchdog-Timer-Use-Cases\Code-for-AVR-ATmega328p\Scenarios\Scenario C\Code_Scenario_C\gpio" -I"K:\ReposClone\Watchdog-Timer-Use-Cases\Code-for-AVR-ATmega328p\Scenarios\Scenario C\Code_Scenario_C\WDGDM" -I"K:\ReposClone\Watchdog-Timer-Use-Cases\Code-for-AVR-ATmega328p\Scenarios\Scenario C\Code_Scenario_C\WDGDrv" -I"K:\ReposClone\Watchdog-Timer-Use-Cases\Code-for-AVR-ATmega328p\Scenarios\Scenario C\Code_Scenario_C\LEDMgr" -Wall -g3 -gdwarf-2 -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


