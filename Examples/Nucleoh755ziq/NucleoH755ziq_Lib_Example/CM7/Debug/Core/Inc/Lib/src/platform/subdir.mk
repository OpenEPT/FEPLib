################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Lib/src/platform/nucleoh755ziq.c 

OBJS += \
./Core/Inc/Lib/src/platform/nucleoh755ziq.o 

C_DEPS += \
./Core/Inc/Lib/src/platform/nucleoh755ziq.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Lib/src/platform/%.o Core/Inc/Lib/src/platform/%.su Core/Inc/Lib/src/platform/%.cyclo: ../Core/Inc/Lib/src/platform/%.c Core/Inc/Lib/src/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Lib-2f-src-2f-platform

clean-Core-2f-Inc-2f-Lib-2f-src-2f-platform:
	-$(RM) ./Core/Inc/Lib/src/platform/nucleoh755ziq.cyclo ./Core/Inc/Lib/src/platform/nucleoh755ziq.d ./Core/Inc/Lib/src/platform/nucleoh755ziq.o ./Core/Inc/Lib/src/platform/nucleoh755ziq.su

.PHONY: clean-Core-2f-Inc-2f-Lib-2f-src-2f-platform

