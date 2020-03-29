################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32_ST7032.c \
../Src/it.c \
../Src/main.c \
../Src/msp.c \
../Src/syscalls.c \
../Src/system_stm32f1xx.c 

OBJS += \
./Src/STM32_ST7032.o \
./Src/it.o \
./Src/main.o \
./Src/msp.o \
./Src/syscalls.o \
./Src/system_stm32f1xx.o 

C_DEPS += \
./Src/STM32_ST7032.d \
./Src/it.d \
./Src/main.d \
./Src/msp.d \
./Src/syscalls.d \
./Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DSTM32F103xB -DDEBUG -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/CMSIS/Include" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/Users/khoahuynh/Documents/Document/STM32F103CB-BluePill/STM32_ST7032/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


