################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.c \
../Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.c 

OBJS += \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.o \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.o 

C_DEPS += \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.d \
./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM324xG_EVAL/%.o Drivers/BSP/STM324xG_EVAL/%.su Drivers/BSP/STM324xG_EVAL/%.cyclo: ../Drivers/BSP/STM324xG_EVAL/%.c Drivers/BSP/STM324xG_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/Src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-5/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM324xG_EVAL

clean-Drivers-2f-BSP-2f-STM324xG_EVAL:
	-$(RM) ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_audio.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_camera.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_eeprom.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_io.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_lcd.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sd.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_sram.su ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.cyclo ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.d ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.o ./Drivers/BSP/STM324xG_EVAL/stm324xg_eval_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM324xG_EVAL

