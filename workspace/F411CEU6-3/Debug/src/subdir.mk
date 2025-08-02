################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/74hc595.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armfunction.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armlcd.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armquery.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armsystick.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/buffer.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/circbuffer.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/explode.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc1.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc2.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc3.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxcrc.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxdma.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxflash.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxgpio.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxmapping.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxnvic.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxpwr.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxrcc.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxrtc.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxsram.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxsyscfg.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim1and8.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim2to5.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim6and7.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim9to14.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxusart.c \
D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/znpid.c 

OBJS += \
./src/74hc595.o \
./src/armfunction.o \
./src/armlcd.o \
./src/armquery.o \
./src/armsystick.o \
./src/buffer.o \
./src/circbuffer.o \
./src/explode.o \
./src/stm32fxxxadc.o \
./src/stm32fxxxadc1.o \
./src/stm32fxxxadc2.o \
./src/stm32fxxxadc3.o \
./src/stm32fxxxcrc.o \
./src/stm32fxxxdma.o \
./src/stm32fxxxflash.o \
./src/stm32fxxxgpio.o \
./src/stm32fxxxmapping.o \
./src/stm32fxxxnvic.o \
./src/stm32fxxxpwr.o \
./src/stm32fxxxrcc.o \
./src/stm32fxxxrtc.o \
./src/stm32fxxxsram.o \
./src/stm32fxxxsyscfg.o \
./src/stm32fxxxtim1and8.o \
./src/stm32fxxxtim2to5.o \
./src/stm32fxxxtim6and7.o \
./src/stm32fxxxtim9to14.o \
./src/stm32fxxxusart.o \
./src/znpid.o 

C_DEPS += \
./src/74hc595.d \
./src/armfunction.d \
./src/armlcd.d \
./src/armquery.d \
./src/armsystick.d \
./src/buffer.d \
./src/circbuffer.d \
./src/explode.d \
./src/stm32fxxxadc.d \
./src/stm32fxxxadc1.d \
./src/stm32fxxxadc2.d \
./src/stm32fxxxadc3.d \
./src/stm32fxxxcrc.d \
./src/stm32fxxxdma.d \
./src/stm32fxxxflash.d \
./src/stm32fxxxgpio.d \
./src/stm32fxxxmapping.d \
./src/stm32fxxxnvic.d \
./src/stm32fxxxpwr.d \
./src/stm32fxxxrcc.d \
./src/stm32fxxxrtc.d \
./src/stm32fxxxsram.d \
./src/stm32fxxxsyscfg.d \
./src/stm32fxxxtim1and8.d \
./src/stm32fxxxtim2to5.d \
./src/stm32fxxxtim6and7.d \
./src/stm32fxxxtim9to14.d \
./src/stm32fxxxusart.d \
./src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
src/74hc595.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/74hc595.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/armfunction.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armfunction.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/armlcd.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armlcd.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/armquery.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armquery.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/armsystick.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/armsystick.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/buffer.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/buffer.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/circbuffer.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/circbuffer.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/explode.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/explode.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxadc.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxadc1.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc1.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxadc2.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc2.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxadc3.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxadc3.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxcrc.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxcrc.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxdma.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxdma.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxflash.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxflash.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxgpio.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxgpio.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxmapping.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxmapping.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxnvic.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxnvic.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxpwr.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxpwr.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxrcc.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxrcc.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxrtc.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxrtc.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxsram.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxsram.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxsyscfg.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxsyscfg.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxtim1and8.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim1and8.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxtim2to5.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim2to5.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxtim6and7.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim6and7.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxtim9to14.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxtim9to14.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32fxxxusart.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/stm32fxxxusart.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/znpid.o: D:/Documents/GitHub_2024/STM32-F446RE/workspace/src/znpid.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/74hc595.cyclo ./src/74hc595.d ./src/74hc595.o ./src/74hc595.su ./src/armfunction.cyclo ./src/armfunction.d ./src/armfunction.o ./src/armfunction.su ./src/armlcd.cyclo ./src/armlcd.d ./src/armlcd.o ./src/armlcd.su ./src/armquery.cyclo ./src/armquery.d ./src/armquery.o ./src/armquery.su ./src/armsystick.cyclo ./src/armsystick.d ./src/armsystick.o ./src/armsystick.su ./src/buffer.cyclo ./src/buffer.d ./src/buffer.o ./src/buffer.su ./src/circbuffer.cyclo ./src/circbuffer.d ./src/circbuffer.o ./src/circbuffer.su ./src/explode.cyclo ./src/explode.d ./src/explode.o ./src/explode.su ./src/stm32fxxxadc.cyclo ./src/stm32fxxxadc.d ./src/stm32fxxxadc.o ./src/stm32fxxxadc.su ./src/stm32fxxxadc1.cyclo ./src/stm32fxxxadc1.d ./src/stm32fxxxadc1.o ./src/stm32fxxxadc1.su ./src/stm32fxxxadc2.cyclo ./src/stm32fxxxadc2.d ./src/stm32fxxxadc2.o ./src/stm32fxxxadc2.su ./src/stm32fxxxadc3.cyclo ./src/stm32fxxxadc3.d ./src/stm32fxxxadc3.o ./src/stm32fxxxadc3.su ./src/stm32fxxxcrc.cyclo ./src/stm32fxxxcrc.d ./src/stm32fxxxcrc.o ./src/stm32fxxxcrc.su ./src/stm32fxxxdma.cyclo ./src/stm32fxxxdma.d ./src/stm32fxxxdma.o ./src/stm32fxxxdma.su ./src/stm32fxxxflash.cyclo ./src/stm32fxxxflash.d ./src/stm32fxxxflash.o ./src/stm32fxxxflash.su ./src/stm32fxxxgpio.cyclo ./src/stm32fxxxgpio.d ./src/stm32fxxxgpio.o ./src/stm32fxxxgpio.su ./src/stm32fxxxmapping.cyclo ./src/stm32fxxxmapping.d ./src/stm32fxxxmapping.o ./src/stm32fxxxmapping.su ./src/stm32fxxxnvic.cyclo ./src/stm32fxxxnvic.d ./src/stm32fxxxnvic.o ./src/stm32fxxxnvic.su ./src/stm32fxxxpwr.cyclo ./src/stm32fxxxpwr.d ./src/stm32fxxxpwr.o ./src/stm32fxxxpwr.su ./src/stm32fxxxrcc.cyclo ./src/stm32fxxxrcc.d ./src/stm32fxxxrcc.o ./src/stm32fxxxrcc.su ./src/stm32fxxxrtc.cyclo ./src/stm32fxxxrtc.d ./src/stm32fxxxrtc.o ./src/stm32fxxxrtc.su ./src/stm32fxxxsram.cyclo ./src/stm32fxxxsram.d ./src/stm32fxxxsram.o ./src/stm32fxxxsram.su ./src/stm32fxxxsyscfg.cyclo ./src/stm32fxxxsyscfg.d ./src/stm32fxxxsyscfg.o ./src/stm32fxxxsyscfg.su ./src/stm32fxxxtim1and8.cyclo ./src/stm32fxxxtim1and8.d ./src/stm32fxxxtim1and8.o ./src/stm32fxxxtim1and8.su ./src/stm32fxxxtim2to5.cyclo ./src/stm32fxxxtim2to5.d ./src/stm32fxxxtim2to5.o ./src/stm32fxxxtim2to5.su ./src/stm32fxxxtim6and7.cyclo ./src/stm32fxxxtim6and7.d ./src/stm32fxxxtim6and7.o ./src/stm32fxxxtim6and7.su ./src/stm32fxxxtim9to14.cyclo ./src/stm32fxxxtim9to14.d ./src/stm32fxxxtim9to14.o ./src/stm32fxxxtim9to14.su ./src/stm32fxxxusart.cyclo ./src/stm32fxxxusart.d ./src/stm32fxxxusart.o ./src/stm32fxxxusart.su ./src/znpid.cyclo ./src/znpid.d ./src/znpid.o ./src/znpid.su

.PHONY: clean-src

