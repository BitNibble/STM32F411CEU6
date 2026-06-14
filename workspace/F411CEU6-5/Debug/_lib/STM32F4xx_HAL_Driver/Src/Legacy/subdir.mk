################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c \
../_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.c 

OBJS += \
./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o \
./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.o 

C_DEPS += \
./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d \
./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.d 


# Each subdirectory must supply rules for building sources it contributes
_lib/STM32F4xx_HAL_Driver/Src/Legacy/%.o _lib/STM32F4xx_HAL_Driver/Src/Legacy/%.su _lib/STM32F4xx_HAL_Driver/Src/Legacy/%.cyclo: ../_lib/STM32F4xx_HAL_Driver/Src/Legacy/%.c _lib/STM32F4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/lib/src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-_lib-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

clean-_lib-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.cyclo ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.su ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.cyclo ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.d ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.o ./_lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.su

.PHONY: clean-_lib-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

