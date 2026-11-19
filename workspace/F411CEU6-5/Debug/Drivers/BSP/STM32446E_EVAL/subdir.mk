################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.c \
../Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.c 

OBJS += \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.o \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.o 

C_DEPS += \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.d \
./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32446E_EVAL/%.o Drivers/BSP/STM32446E_EVAL/%.su Drivers/BSP/STM32446E_EVAL/%.cyclo: ../Drivers/BSP/STM32446E_EVAL/%.c Drivers/BSP/STM32446E_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32446E_EVAL

clean-Drivers-2f-BSP-2f-STM32446E_EVAL:
	-$(RM) ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_audio.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_camera.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_eeprom.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_io.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_lcd.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_qspi.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sd.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_sdram.su ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.cyclo ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.d ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.o ./Drivers/BSP/STM32446E_EVAL/stm32446e_eval_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32446E_EVAL

