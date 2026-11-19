################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/Src/74hc595.c \
../Library/Src/armfunction.c \
../Library/Src/armlcd.c \
../Library/Src/armquery.c \
../Library/Src/armsystick.c \
../Library/Src/buffer.c \
../Library/Src/circbuffer.c \
../Library/Src/explode.c \
../Library/Src/stm32fxxxadc.c \
../Library/Src/stm32fxxxadc1.c \
../Library/Src/stm32fxxxadc2.c \
../Library/Src/stm32fxxxadc3.c \
../Library/Src/stm32fxxxcrc.c \
../Library/Src/stm32fxxxdma.c \
../Library/Src/stm32fxxxflash.c \
../Library/Src/stm32fxxxgpio.c \
../Library/Src/stm32fxxxmapping.c \
../Library/Src/stm32fxxxnvic.c \
../Library/Src/stm32fxxxpwr.c \
../Library/Src/stm32fxxxrcc.c \
../Library/Src/stm32fxxxrtc.c \
../Library/Src/stm32fxxxsram.c \
../Library/Src/stm32fxxxsyscfg.c \
../Library/Src/stm32fxxxtim1and8.c \
../Library/Src/stm32fxxxtim2to5.c \
../Library/Src/stm32fxxxtim6and7.c \
../Library/Src/stm32fxxxtim9to14.c \
../Library/Src/stm32fxxxusart.c \
../Library/Src/znpid.c 

OBJS += \
./Library/Src/74hc595.o \
./Library/Src/armfunction.o \
./Library/Src/armlcd.o \
./Library/Src/armquery.o \
./Library/Src/armsystick.o \
./Library/Src/buffer.o \
./Library/Src/circbuffer.o \
./Library/Src/explode.o \
./Library/Src/stm32fxxxadc.o \
./Library/Src/stm32fxxxadc1.o \
./Library/Src/stm32fxxxadc2.o \
./Library/Src/stm32fxxxadc3.o \
./Library/Src/stm32fxxxcrc.o \
./Library/Src/stm32fxxxdma.o \
./Library/Src/stm32fxxxflash.o \
./Library/Src/stm32fxxxgpio.o \
./Library/Src/stm32fxxxmapping.o \
./Library/Src/stm32fxxxnvic.o \
./Library/Src/stm32fxxxpwr.o \
./Library/Src/stm32fxxxrcc.o \
./Library/Src/stm32fxxxrtc.o \
./Library/Src/stm32fxxxsram.o \
./Library/Src/stm32fxxxsyscfg.o \
./Library/Src/stm32fxxxtim1and8.o \
./Library/Src/stm32fxxxtim2to5.o \
./Library/Src/stm32fxxxtim6and7.o \
./Library/Src/stm32fxxxtim9to14.o \
./Library/Src/stm32fxxxusart.o \
./Library/Src/znpid.o 

C_DEPS += \
./Library/Src/74hc595.d \
./Library/Src/armfunction.d \
./Library/Src/armlcd.d \
./Library/Src/armquery.d \
./Library/Src/armsystick.d \
./Library/Src/buffer.d \
./Library/Src/circbuffer.d \
./Library/Src/explode.d \
./Library/Src/stm32fxxxadc.d \
./Library/Src/stm32fxxxadc1.d \
./Library/Src/stm32fxxxadc2.d \
./Library/Src/stm32fxxxadc3.d \
./Library/Src/stm32fxxxcrc.d \
./Library/Src/stm32fxxxdma.d \
./Library/Src/stm32fxxxflash.d \
./Library/Src/stm32fxxxgpio.d \
./Library/Src/stm32fxxxmapping.d \
./Library/Src/stm32fxxxnvic.d \
./Library/Src/stm32fxxxpwr.d \
./Library/Src/stm32fxxxrcc.d \
./Library/Src/stm32fxxxrtc.d \
./Library/Src/stm32fxxxsram.d \
./Library/Src/stm32fxxxsyscfg.d \
./Library/Src/stm32fxxxtim1and8.d \
./Library/Src/stm32fxxxtim2to5.d \
./Library/Src/stm32fxxxtim6and7.d \
./Library/Src/stm32fxxxtim9to14.d \
./Library/Src/stm32fxxxusart.d \
./Library/Src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
Library/Src/%.o Library/Src/%.su Library/Src/%.cyclo: ../Library/Src/%.c Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/GitHub_2024/STM32-F446RE/workspace/F411CEU6-3/Library/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library-2f-Src

clean-Library-2f-Src:
	-$(RM) ./Library/Src/74hc595.cyclo ./Library/Src/74hc595.d ./Library/Src/74hc595.o ./Library/Src/74hc595.su ./Library/Src/armfunction.cyclo ./Library/Src/armfunction.d ./Library/Src/armfunction.o ./Library/Src/armfunction.su ./Library/Src/armlcd.cyclo ./Library/Src/armlcd.d ./Library/Src/armlcd.o ./Library/Src/armlcd.su ./Library/Src/armquery.cyclo ./Library/Src/armquery.d ./Library/Src/armquery.o ./Library/Src/armquery.su ./Library/Src/armsystick.cyclo ./Library/Src/armsystick.d ./Library/Src/armsystick.o ./Library/Src/armsystick.su ./Library/Src/buffer.cyclo ./Library/Src/buffer.d ./Library/Src/buffer.o ./Library/Src/buffer.su ./Library/Src/circbuffer.cyclo ./Library/Src/circbuffer.d ./Library/Src/circbuffer.o ./Library/Src/circbuffer.su ./Library/Src/explode.cyclo ./Library/Src/explode.d ./Library/Src/explode.o ./Library/Src/explode.su ./Library/Src/stm32fxxxadc.cyclo ./Library/Src/stm32fxxxadc.d ./Library/Src/stm32fxxxadc.o ./Library/Src/stm32fxxxadc.su ./Library/Src/stm32fxxxadc1.cyclo ./Library/Src/stm32fxxxadc1.d ./Library/Src/stm32fxxxadc1.o ./Library/Src/stm32fxxxadc1.su ./Library/Src/stm32fxxxadc2.cyclo ./Library/Src/stm32fxxxadc2.d ./Library/Src/stm32fxxxadc2.o ./Library/Src/stm32fxxxadc2.su ./Library/Src/stm32fxxxadc3.cyclo ./Library/Src/stm32fxxxadc3.d ./Library/Src/stm32fxxxadc3.o ./Library/Src/stm32fxxxadc3.su ./Library/Src/stm32fxxxcrc.cyclo ./Library/Src/stm32fxxxcrc.d ./Library/Src/stm32fxxxcrc.o ./Library/Src/stm32fxxxcrc.su ./Library/Src/stm32fxxxdma.cyclo ./Library/Src/stm32fxxxdma.d ./Library/Src/stm32fxxxdma.o ./Library/Src/stm32fxxxdma.su ./Library/Src/stm32fxxxflash.cyclo ./Library/Src/stm32fxxxflash.d ./Library/Src/stm32fxxxflash.o ./Library/Src/stm32fxxxflash.su ./Library/Src/stm32fxxxgpio.cyclo ./Library/Src/stm32fxxxgpio.d ./Library/Src/stm32fxxxgpio.o ./Library/Src/stm32fxxxgpio.su ./Library/Src/stm32fxxxmapping.cyclo ./Library/Src/stm32fxxxmapping.d ./Library/Src/stm32fxxxmapping.o ./Library/Src/stm32fxxxmapping.su ./Library/Src/stm32fxxxnvic.cyclo ./Library/Src/stm32fxxxnvic.d ./Library/Src/stm32fxxxnvic.o ./Library/Src/stm32fxxxnvic.su ./Library/Src/stm32fxxxpwr.cyclo ./Library/Src/stm32fxxxpwr.d ./Library/Src/stm32fxxxpwr.o ./Library/Src/stm32fxxxpwr.su ./Library/Src/stm32fxxxrcc.cyclo ./Library/Src/stm32fxxxrcc.d ./Library/Src/stm32fxxxrcc.o ./Library/Src/stm32fxxxrcc.su ./Library/Src/stm32fxxxrtc.cyclo ./Library/Src/stm32fxxxrtc.d ./Library/Src/stm32fxxxrtc.o ./Library/Src/stm32fxxxrtc.su ./Library/Src/stm32fxxxsram.cyclo ./Library/Src/stm32fxxxsram.d ./Library/Src/stm32fxxxsram.o ./Library/Src/stm32fxxxsram.su ./Library/Src/stm32fxxxsyscfg.cyclo ./Library/Src/stm32fxxxsyscfg.d ./Library/Src/stm32fxxxsyscfg.o ./Library/Src/stm32fxxxsyscfg.su ./Library/Src/stm32fxxxtim1and8.cyclo ./Library/Src/stm32fxxxtim1and8.d ./Library/Src/stm32fxxxtim1and8.o ./Library/Src/stm32fxxxtim1and8.su ./Library/Src/stm32fxxxtim2to5.cyclo ./Library/Src/stm32fxxxtim2to5.d ./Library/Src/stm32fxxxtim2to5.o ./Library/Src/stm32fxxxtim2to5.su ./Library/Src/stm32fxxxtim6and7.cyclo ./Library/Src/stm32fxxxtim6and7.d ./Library/Src/stm32fxxxtim6and7.o ./Library/Src/stm32fxxxtim6and7.su ./Library/Src/stm32fxxxtim9to14.cyclo ./Library/Src/stm32fxxxtim9to14.d ./Library/Src/stm32fxxxtim9to14.o ./Library/Src/stm32fxxxtim9to14.su ./Library/Src/stm32fxxxusart.cyclo ./Library/Src/stm32fxxxusart.d ./Library/Src/stm32fxxxusart.o ./Library/Src/stm32fxxxusart.su ./Library/Src/znpid.cyclo ./Library/Src/znpid.d ./Library/Src/znpid.o ./Library/Src/znpid.su

.PHONY: clean-Library-2f-Src

