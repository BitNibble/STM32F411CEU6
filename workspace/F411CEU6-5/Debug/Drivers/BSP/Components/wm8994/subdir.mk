################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/wm8994/wm8994.c 

OBJS += \
./Drivers/BSP/Components/wm8994/wm8994.o 

C_DEPS += \
./Drivers/BSP/Components/wm8994/wm8994.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/wm8994/%.o Drivers/BSP/Components/wm8994/%.su Drivers/BSP/Components/wm8994/%.cyclo: ../Drivers/BSP/Components/wm8994/%.c Drivers/BSP/Components/wm8994/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-wm8994

clean-Drivers-2f-BSP-2f-Components-2f-wm8994:
	-$(RM) ./Drivers/BSP/Components/wm8994/wm8994.cyclo ./Drivers/BSP/Components/wm8994/wm8994.d ./Drivers/BSP/Components/wm8994/wm8994.o ./Drivers/BSP/Components/wm8994/wm8994.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-wm8994

