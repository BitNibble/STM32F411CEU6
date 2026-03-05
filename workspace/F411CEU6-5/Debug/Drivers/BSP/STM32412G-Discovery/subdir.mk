################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32412G-Discovery/%.o Drivers/BSP/STM32412G-Discovery/%.su Drivers/BSP/STM32412G-Discovery/%.cyclo: ../Drivers/BSP/STM32412G-Discovery/%.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32412G-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32412G-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_audio.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_eeprom.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_qspi.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_sd.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32412G-2d-Discovery

