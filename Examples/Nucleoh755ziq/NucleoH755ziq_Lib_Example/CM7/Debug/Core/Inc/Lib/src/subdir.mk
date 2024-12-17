################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Lib/src/openept_ed.c 

O_SRCS += \
../Core/Inc/Lib/src/openept_ed.o 

OBJS += \
./Core/Inc/Lib/src/openept_ed.o 

C_DEPS += \
./Core/Inc/Lib/src/openept_ed.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Lib/src/%.o Core/Inc/Lib/src/%.su Core/Inc/Lib/src/%.cyclo: ../Core/Inc/Lib/src/%.c Core/Inc/Lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Lib-2f-src

clean-Core-2f-Inc-2f-Lib-2f-src:
	-$(RM) ./Core/Inc/Lib/src/openept_ed.cyclo ./Core/Inc/Lib/src/openept_ed.d ./Core/Inc/Lib/src/openept_ed.o ./Core/Inc/Lib/src/openept_ed.su

.PHONY: clean-Core-2f-Inc-2f-Lib-2f-src

