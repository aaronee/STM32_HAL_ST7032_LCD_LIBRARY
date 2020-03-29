################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup/startup_stm32f103xb.S 

OBJS += \
./startup/startup_stm32f103xb.o 

S_UPPER_DEPS += \
./startup/startup_stm32f103xb.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -DSTM32F103xB -DDEBUG -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/CMSIS/Include" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


