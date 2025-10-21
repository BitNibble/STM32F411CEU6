################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c \
../Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.c 

OBJS += \
./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o \
./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.o 

C_DEPS += \
./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d \
./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.o Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.su Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.cyclo: ../Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.c Drivers/STM32F4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -ID:/Embedded/STM32F411CEU6/workspace/F411CEU6-4/Core/Inc -ID:/Embedded/STM32F411CEU6/workspace/F411CEU6-4/Drivers/STM32F4xx_HAL_Driver/Inc -ID:/Embedded/STM32F411CEU6/workspace/F411CEU6-4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -ID:/Embedded/STM32F411CEU6/workspace/F411CEU6-4/Drivers/CMSIS/Device/ST/STM32F4xx/Include -ID:/Embedded/STM32F411CEU6/workspace/F411CEU6-4/Drivers/CMSIS/Include -ID:/Embedded/STM32F411CEU6/workspace/F411CEU6-4/lib/src -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

clean-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.cyclo ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.su ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.cyclo ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.d ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.o ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.su

.PHONY: clean-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

