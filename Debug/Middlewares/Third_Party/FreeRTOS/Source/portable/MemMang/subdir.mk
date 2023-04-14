################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.su Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.cyclo: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/application/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/TelemetryMAIN/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleCAN/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleFlash/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleNEXTION/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleRTC/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleSDCard/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleWIFI/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/DS3231/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/NEXTION/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/FATFS/Target" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/FATFS/App" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Middlewares/Third_Party/FatFs/src" -I../Core/ThreadSafe -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/EEPROM_Flash/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/SD_Card/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.cyclo ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

