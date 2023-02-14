################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../features/ModuleCAN/Src/ModuleCAN.c 

OBJS += \
./features/ModuleCAN/Src/ModuleCAN.o 

C_DEPS += \
./features/ModuleCAN/Src/ModuleCAN.d 


# Each subdirectory must supply rules for building sources it contributes
features/ModuleCAN/Src/%.o features/ModuleCAN/Src/%.su: ../features/ModuleCAN/Src/%.c features/ModuleCAN/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/application/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/TelemetryMAIN/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleCAN/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleFlash/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleNEXTION/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleRTC/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleSDCard/Inc" -I"C:/Users/AtakanErtekin/Desktop/Elektromobil WorkSpace/EEM_TELEMETRY_PROJECT/features/ModuleWIFI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-features-2f-ModuleCAN-2f-Src

clean-features-2f-ModuleCAN-2f-Src:
	-$(RM) ./features/ModuleCAN/Src/ModuleCAN.d ./features/ModuleCAN/Src/ModuleCAN.o ./features/ModuleCAN/Src/ModuleCAN.su

.PHONY: clean-features-2f-ModuleCAN-2f-Src

