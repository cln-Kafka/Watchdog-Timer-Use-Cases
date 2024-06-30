################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO/GPIO.c 

C_DEPS += \
./GPIO/GPIO.d 

OBJS += \
./GPIO/GPIO.o 


# Each subdirectory must supply rules for building sources it contributes
GPIO/%.o: ../GPIO/%.c GPIO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\Project_Code\GPIO" -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\Project_Code\LEDMgr" -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\Project_Code\NVIC" -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\Project_Code\WDGDrv" -I"E:\SBE\SBE 3rd Year\Second Semester\Embedded Systems\BlinkingLED_with_Watchdog\Project_Code\WDGM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


