################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/74hc595.c \
../lib/src/BT_Commands.c \
../lib/src/ESP8266_Commands.c \
../lib/src/armfunction.c \
../lib/src/armlcd.c \
../lib/src/armsystick.c \
../lib/src/buffer.c \
../lib/src/explode.c \
../lib/src/stm32f411ceu6.c \
../lib/src/stm32fxxxadc1.c \
../lib/src/stm32fxxxadc2.c \
../lib/src/stm32fxxxadc3.c \
../lib/src/stm32fxxxcrc.c \
../lib/src/stm32fxxxdma.c \
../lib/src/stm32fxxxflash.c \
../lib/src/stm32fxxxgpio.c \
../lib/src/stm32fxxxi2c.c \
../lib/src/stm32fxxxnvic.c \
../lib/src/stm32fxxxpwr.c \
../lib/src/stm32fxxxrcc.c \
../lib/src/stm32fxxxrtc.c \
../lib/src/stm32fxxxsram.c \
../lib/src/stm32fxxxsyscfg.c \
../lib/src/stm32fxxxtim1and8.c \
../lib/src/stm32fxxxtim2to5.c \
../lib/src/stm32fxxxtim6and7.c \
../lib/src/stm32fxxxtim9to14.c \
../lib/src/stm32fxxxtool.c \
../lib/src/stm32fxxxusart1.c \
../lib/src/stm32fxxxusart2.c \
../lib/src/stm32fxxxusart6.c \
../lib/src/timer_irq.c \
../lib/src/webpages.c \
../lib/src/znpid.c 

OBJS += \
./lib/src/74hc595.o \
./lib/src/BT_Commands.o \
./lib/src/ESP8266_Commands.o \
./lib/src/armfunction.o \
./lib/src/armlcd.o \
./lib/src/armsystick.o \
./lib/src/buffer.o \
./lib/src/explode.o \
./lib/src/stm32f411ceu6.o \
./lib/src/stm32fxxxadc1.o \
./lib/src/stm32fxxxadc2.o \
./lib/src/stm32fxxxadc3.o \
./lib/src/stm32fxxxcrc.o \
./lib/src/stm32fxxxdma.o \
./lib/src/stm32fxxxflash.o \
./lib/src/stm32fxxxgpio.o \
./lib/src/stm32fxxxi2c.o \
./lib/src/stm32fxxxnvic.o \
./lib/src/stm32fxxxpwr.o \
./lib/src/stm32fxxxrcc.o \
./lib/src/stm32fxxxrtc.o \
./lib/src/stm32fxxxsram.o \
./lib/src/stm32fxxxsyscfg.o \
./lib/src/stm32fxxxtim1and8.o \
./lib/src/stm32fxxxtim2to5.o \
./lib/src/stm32fxxxtim6and7.o \
./lib/src/stm32fxxxtim9to14.o \
./lib/src/stm32fxxxtool.o \
./lib/src/stm32fxxxusart1.o \
./lib/src/stm32fxxxusart2.o \
./lib/src/stm32fxxxusart6.o \
./lib/src/timer_irq.o \
./lib/src/webpages.o \
./lib/src/znpid.o 

C_DEPS += \
./lib/src/74hc595.d \
./lib/src/BT_Commands.d \
./lib/src/ESP8266_Commands.d \
./lib/src/armfunction.d \
./lib/src/armlcd.d \
./lib/src/armsystick.d \
./lib/src/buffer.d \
./lib/src/explode.d \
./lib/src/stm32f411ceu6.d \
./lib/src/stm32fxxxadc1.d \
./lib/src/stm32fxxxadc2.d \
./lib/src/stm32fxxxadc3.d \
./lib/src/stm32fxxxcrc.d \
./lib/src/stm32fxxxdma.d \
./lib/src/stm32fxxxflash.d \
./lib/src/stm32fxxxgpio.d \
./lib/src/stm32fxxxi2c.d \
./lib/src/stm32fxxxnvic.d \
./lib/src/stm32fxxxpwr.d \
./lib/src/stm32fxxxrcc.d \
./lib/src/stm32fxxxrtc.d \
./lib/src/stm32fxxxsram.d \
./lib/src/stm32fxxxsyscfg.d \
./lib/src/stm32fxxxtim1and8.d \
./lib/src/stm32fxxxtim2to5.d \
./lib/src/stm32fxxxtim6and7.d \
./lib/src/stm32fxxxtim9to14.d \
./lib/src/stm32fxxxtool.d \
./lib/src/stm32fxxxusart1.d \
./lib/src/stm32fxxxusart2.d \
./lib/src/stm32fxxxusart6.d \
./lib/src/timer_irq.d \
./lib/src/webpages.d \
./lib/src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o lib/src/%.su lib/src/%.cyclo: ../lib/src/%.c lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-3/Core/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-3/lib/src" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-3/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-3/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-3/Drivers/CMSIS/Include" -I"D:/Embedded/STM32F411CEU6/workspace/F411CEU6-3/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-src

clean-lib-2f-src:
	-$(RM) ./lib/src/74hc595.cyclo ./lib/src/74hc595.d ./lib/src/74hc595.o ./lib/src/74hc595.su ./lib/src/BT_Commands.cyclo ./lib/src/BT_Commands.d ./lib/src/BT_Commands.o ./lib/src/BT_Commands.su ./lib/src/ESP8266_Commands.cyclo ./lib/src/ESP8266_Commands.d ./lib/src/ESP8266_Commands.o ./lib/src/ESP8266_Commands.su ./lib/src/armfunction.cyclo ./lib/src/armfunction.d ./lib/src/armfunction.o ./lib/src/armfunction.su ./lib/src/armlcd.cyclo ./lib/src/armlcd.d ./lib/src/armlcd.o ./lib/src/armlcd.su ./lib/src/armsystick.cyclo ./lib/src/armsystick.d ./lib/src/armsystick.o ./lib/src/armsystick.su ./lib/src/buffer.cyclo ./lib/src/buffer.d ./lib/src/buffer.o ./lib/src/buffer.su ./lib/src/explode.cyclo ./lib/src/explode.d ./lib/src/explode.o ./lib/src/explode.su ./lib/src/stm32f411ceu6.cyclo ./lib/src/stm32f411ceu6.d ./lib/src/stm32f411ceu6.o ./lib/src/stm32f411ceu6.su ./lib/src/stm32fxxxadc1.cyclo ./lib/src/stm32fxxxadc1.d ./lib/src/stm32fxxxadc1.o ./lib/src/stm32fxxxadc1.su ./lib/src/stm32fxxxadc2.cyclo ./lib/src/stm32fxxxadc2.d ./lib/src/stm32fxxxadc2.o ./lib/src/stm32fxxxadc2.su ./lib/src/stm32fxxxadc3.cyclo ./lib/src/stm32fxxxadc3.d ./lib/src/stm32fxxxadc3.o ./lib/src/stm32fxxxadc3.su ./lib/src/stm32fxxxcrc.cyclo ./lib/src/stm32fxxxcrc.d ./lib/src/stm32fxxxcrc.o ./lib/src/stm32fxxxcrc.su ./lib/src/stm32fxxxdma.cyclo ./lib/src/stm32fxxxdma.d ./lib/src/stm32fxxxdma.o ./lib/src/stm32fxxxdma.su ./lib/src/stm32fxxxflash.cyclo ./lib/src/stm32fxxxflash.d ./lib/src/stm32fxxxflash.o ./lib/src/stm32fxxxflash.su ./lib/src/stm32fxxxgpio.cyclo ./lib/src/stm32fxxxgpio.d ./lib/src/stm32fxxxgpio.o ./lib/src/stm32fxxxgpio.su ./lib/src/stm32fxxxi2c.cyclo ./lib/src/stm32fxxxi2c.d ./lib/src/stm32fxxxi2c.o ./lib/src/stm32fxxxi2c.su ./lib/src/stm32fxxxnvic.cyclo ./lib/src/stm32fxxxnvic.d ./lib/src/stm32fxxxnvic.o ./lib/src/stm32fxxxnvic.su ./lib/src/stm32fxxxpwr.cyclo ./lib/src/stm32fxxxpwr.d ./lib/src/stm32fxxxpwr.o ./lib/src/stm32fxxxpwr.su ./lib/src/stm32fxxxrcc.cyclo ./lib/src/stm32fxxxrcc.d ./lib/src/stm32fxxxrcc.o ./lib/src/stm32fxxxrcc.su ./lib/src/stm32fxxxrtc.cyclo ./lib/src/stm32fxxxrtc.d ./lib/src/stm32fxxxrtc.o ./lib/src/stm32fxxxrtc.su ./lib/src/stm32fxxxsram.cyclo ./lib/src/stm32fxxxsram.d ./lib/src/stm32fxxxsram.o ./lib/src/stm32fxxxsram.su ./lib/src/stm32fxxxsyscfg.cyclo ./lib/src/stm32fxxxsyscfg.d ./lib/src/stm32fxxxsyscfg.o ./lib/src/stm32fxxxsyscfg.su ./lib/src/stm32fxxxtim1and8.cyclo ./lib/src/stm32fxxxtim1and8.d ./lib/src/stm32fxxxtim1and8.o ./lib/src/stm32fxxxtim1and8.su ./lib/src/stm32fxxxtim2to5.cyclo ./lib/src/stm32fxxxtim2to5.d ./lib/src/stm32fxxxtim2to5.o ./lib/src/stm32fxxxtim2to5.su ./lib/src/stm32fxxxtim6and7.cyclo ./lib/src/stm32fxxxtim6and7.d ./lib/src/stm32fxxxtim6and7.o ./lib/src/stm32fxxxtim6and7.su ./lib/src/stm32fxxxtim9to14.cyclo ./lib/src/stm32fxxxtim9to14.d ./lib/src/stm32fxxxtim9to14.o ./lib/src/stm32fxxxtim9to14.su ./lib/src/stm32fxxxtool.cyclo ./lib/src/stm32fxxxtool.d ./lib/src/stm32fxxxtool.o ./lib/src/stm32fxxxtool.su ./lib/src/stm32fxxxusart1.cyclo ./lib/src/stm32fxxxusart1.d ./lib/src/stm32fxxxusart1.o ./lib/src/stm32fxxxusart1.su ./lib/src/stm32fxxxusart2.cyclo ./lib/src/stm32fxxxusart2.d ./lib/src/stm32fxxxusart2.o ./lib/src/stm32fxxxusart2.su ./lib/src/stm32fxxxusart6.cyclo ./lib/src/stm32fxxxusart6.d ./lib/src/stm32fxxxusart6.o ./lib/src/stm32fxxxusart6.su ./lib/src/timer_irq.cyclo ./lib/src/timer_irq.d ./lib/src/timer_irq.o ./lib/src/timer_irq.su ./lib/src/webpages.cyclo ./lib/src/webpages.d ./lib/src/webpages.o ./lib/src/webpages.su ./lib/src/znpid.cyclo ./lib/src/znpid.d ./lib/src/znpid.o ./lib/src/znpid.su

.PHONY: clean-lib-2f-src

