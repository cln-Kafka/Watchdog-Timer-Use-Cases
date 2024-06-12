################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LEDMgr/LEDM.c 

C_DEPS += \
./LEDMgr/LEDM.d 

OBJS += \
./LEDMgr/LEDM.o 


# Each subdirectory must supply rules for building sources it contributes
LEDMgr/%.o: ../LEDMgr/%.c LEDMgr/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\Lib" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\GPIO" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\LEDMgr" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\NVIC" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\RCC" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\WDGDrv" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\WDGM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


