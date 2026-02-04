################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/backup/startup_stm32f411ceux.s 

OBJS += \
./Startup/backup/startup_stm32f411ceux.o 

S_DEPS += \
./Startup/backup/startup_stm32f411ceux.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/backup/%.o: ../Startup/backup/%.s Startup/backup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup-2f-backup

clean-Startup-2f-backup:
	-$(RM) ./Startup/backup/startup_stm32f411ceux.d ./Startup/backup/startup_stm32f411ceux.o

.PHONY: clean-Startup-2f-backup

