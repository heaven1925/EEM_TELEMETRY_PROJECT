################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../features/ModuleSDCard/Src/ModuleSDCard.c 

OBJS += \
./features/ModuleSDCard/Src/ModuleSDCard.o 

C_DEPS += \
./features/ModuleSDCard/Src/ModuleSDCard.d 


# Each subdirectory must supply rules for building sources it contributes
features/ModuleSDCard/Src/%.o features/ModuleSDCard/Src/%.su: ../features/ModuleSDCard/Src/%.c features/ModuleSDCard/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/application/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/TelemetryMAIN/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleCAN/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleFlash/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleNEXTION/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleRTC/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleSDCard/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleWIFI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-features-2f-ModuleSDCard-2f-Src

clean-features-2f-ModuleSDCard-2f-Src:
	-$(RM) ./features/ModuleSDCard/Src/ModuleSDCard.d ./features/ModuleSDCard/Src/ModuleSDCard.o ./features/ModuleSDCard/Src/ModuleSDCard.su

.PHONY: clean-features-2f-ModuleSDCard-2f-Src

