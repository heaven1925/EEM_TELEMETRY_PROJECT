################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DS3231/Src/DS3231.c 

OBJS += \
./Drivers/DS3231/Src/DS3231.o 

C_DEPS += \
./Drivers/DS3231/Src/DS3231.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DS3231/Src/%.o Drivers/DS3231/Src/%.su Drivers/DS3231/Src/%.cyclo: ../Drivers/DS3231/Src/%.c Drivers/DS3231/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/application/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/TelemetryMAIN/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleCAN/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleFlash/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleNEXTION/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleRTC/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleSDCard/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/features/ModuleWIFI/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/DS3231/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/NEXTION/Inc" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/FATFS/Target" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/FATFS/App" -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Middlewares/Third_Party/FatFs/src" -I../Core/ThreadSafe -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/EEPROM_Flash/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/atakan.ertekin/Desktop/WorkSpace/ElectricDriver_CodeSpace/EEM_TELEMETRY_PROJECT/Drivers/SD_Card/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DS3231-2f-Src

clean-Drivers-2f-DS3231-2f-Src:
	-$(RM) ./Drivers/DS3231/Src/DS3231.cyclo ./Drivers/DS3231/Src/DS3231.d ./Drivers/DS3231/Src/DS3231.o ./Drivers/DS3231/Src/DS3231.su

.PHONY: clean-Drivers-2f-DS3231-2f-Src

