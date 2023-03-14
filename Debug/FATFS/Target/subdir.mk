################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Target/user_diskio.c 

OBJS += \
./FATFS/Target/user_diskio.o 

C_DEPS += \
./FATFS/Target/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Target/%.o FATFS/Target/%.su: ../FATFS/Target/%.c FATFS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/application/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/TelemetryMAIN/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/ModuleCAN/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/ModuleFlash/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/ModuleNEXTION/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/ModuleRTC/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/ModuleSDCard/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/features/ModuleWIFI/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/Drivers/DS3231/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/Drivers/NEXTION/Inc" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/FATFS/Target" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/FATFS/App" -I"C:/Users/ASUS/Desktop/STM/Workspace/EEM_TELEMETRY_PROJECT/Middlewares/Third_Party/FatFs/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS-2f-Target

clean-FATFS-2f-Target:
	-$(RM) ./FATFS/Target/user_diskio.d ./FATFS/Target/user_diskio.o ./FATFS/Target/user_diskio.su

.PHONY: clean-FATFS-2f-Target

