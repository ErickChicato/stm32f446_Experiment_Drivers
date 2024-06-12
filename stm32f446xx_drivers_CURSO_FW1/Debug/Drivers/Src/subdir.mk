################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32f446xx_crc.c \
../Drivers/Src/stm32f446xx_gpio.c \
../Drivers/Src/stm32f446xx_interrp.c 

OBJS += \
./Drivers/Src/stm32f446xx_crc.o \
./Drivers/Src/stm32f446xx_gpio.o \
./Drivers/Src/stm32f446xx_interrp.o 

C_DEPS += \
./Drivers/Src/stm32f446xx_crc.d \
./Drivers/Src/stm32f446xx_gpio.d \
./Drivers/Src/stm32f446xx_interrp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -c -I../Inc -I"C:/Users/robo1/STM32CubeIDE/workspace_1.11.0/stm32f446xx_drivers_CURSO_FW1/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32f446xx_crc.d ./Drivers/Src/stm32f446xx_crc.o ./Drivers/Src/stm32f446xx_crc.su ./Drivers/Src/stm32f446xx_gpio.d ./Drivers/Src/stm32f446xx_gpio.o ./Drivers/Src/stm32f446xx_gpio.su ./Drivers/Src/stm32f446xx_interrp.d ./Drivers/Src/stm32f446xx_interrp.o ./Drivers/Src/stm32f446xx_interrp.su

.PHONY: clean-Drivers-2f-Src

