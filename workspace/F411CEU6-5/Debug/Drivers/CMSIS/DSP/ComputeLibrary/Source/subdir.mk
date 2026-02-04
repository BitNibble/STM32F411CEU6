################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.c 

OBJS += \
./Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.o 

C_DEPS += \
./Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/ComputeLibrary/Source/%.o Drivers/CMSIS/DSP/ComputeLibrary/Source/%.su Drivers/CMSIS/DSP/ComputeLibrary/Source/%.cyclo: ../Drivers/CMSIS/DSP/ComputeLibrary/Source/%.c Drivers/CMSIS/DSP/ComputeLibrary/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-ComputeLibrary-2f-Source

clean-Drivers-2f-CMSIS-2f-DSP-2f-ComputeLibrary-2f-Source:
	-$(RM) ./Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.cyclo ./Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.d ./Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.o ./Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-ComputeLibrary-2f-Source

