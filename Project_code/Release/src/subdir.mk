################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/initialize-hardware.c \
../src/main.c \
../src/stm32f4xx_hal_msp.c \
../src/write.c 

C_DEPS += \
./src/initialize-hardware.d \
./src/main.d \
./src/stm32f4xx_hal_msp.d \
./src/write.d 

OBJS += \
./src/initialize-hardware.o \
./src/main.o \
./src/stm32f4xx_hal_msp.o \
./src/write.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\Lib" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\GPIO" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\LEDMgr" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\NVIC" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\RCC" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\WDGDrv" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\WDGM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/stm32f4xx_hal_msp.o: ../src/stm32f4xx_hal_msp.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\Lib" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\GPIO" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\LEDMgr" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\NVIC" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\RCC" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\WDGDrv" -I"C:\Users\Kareem\eclipse-workspace\Blinking_LED_with_Wathcdog\WDGM" -std=gnu11 -Wno-padded -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


