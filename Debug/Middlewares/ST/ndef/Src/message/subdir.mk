################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/ndef/Src/message/ndef_message.c \
../Middlewares/ST/ndef/Src/message/ndef_record.c \
../Middlewares/ST/ndef/Src/message/ndef_type_wifi.c \
../Middlewares/ST/ndef/Src/message/ndef_types.c \
../Middlewares/ST/ndef/Src/message/ndef_types_mime.c \
../Middlewares/ST/ndef/Src/message/ndef_types_rtd.c 

C_DEPS += \
./Middlewares/ST/ndef/Src/message/ndef_message.d \
./Middlewares/ST/ndef/Src/message/ndef_record.d \
./Middlewares/ST/ndef/Src/message/ndef_type_wifi.d \
./Middlewares/ST/ndef/Src/message/ndef_types.d \
./Middlewares/ST/ndef/Src/message/ndef_types_mime.d \
./Middlewares/ST/ndef/Src/message/ndef_types_rtd.d 

OBJS += \
./Middlewares/ST/ndef/Src/message/ndef_message.o \
./Middlewares/ST/ndef/Src/message/ndef_record.o \
./Middlewares/ST/ndef/Src/message/ndef_type_wifi.o \
./Middlewares/ST/ndef/Src/message/ndef_types.o \
./Middlewares/ST/ndef/Src/message/ndef_types_mime.o \
./Middlewares/ST/ndef/Src/message/ndef_types_rtd.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/ndef/Src/message/%.o Middlewares/ST/ndef/Src/message/%.su Middlewares/ST/ndef/Src/message/%.cyclo: ../Middlewares/ST/ndef/Src/message/%.c Middlewares/ST/ndef/Src/message/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-ndef-2f-Src-2f-message

clean-Middlewares-2f-ST-2f-ndef-2f-Src-2f-message:
	-$(RM) ./Middlewares/ST/ndef/Src/message/ndef_message.cyclo ./Middlewares/ST/ndef/Src/message/ndef_message.d ./Middlewares/ST/ndef/Src/message/ndef_message.o ./Middlewares/ST/ndef/Src/message/ndef_message.su ./Middlewares/ST/ndef/Src/message/ndef_record.cyclo ./Middlewares/ST/ndef/Src/message/ndef_record.d ./Middlewares/ST/ndef/Src/message/ndef_record.o ./Middlewares/ST/ndef/Src/message/ndef_record.su ./Middlewares/ST/ndef/Src/message/ndef_type_wifi.cyclo ./Middlewares/ST/ndef/Src/message/ndef_type_wifi.d ./Middlewares/ST/ndef/Src/message/ndef_type_wifi.o ./Middlewares/ST/ndef/Src/message/ndef_type_wifi.su ./Middlewares/ST/ndef/Src/message/ndef_types.cyclo ./Middlewares/ST/ndef/Src/message/ndef_types.d ./Middlewares/ST/ndef/Src/message/ndef_types.o ./Middlewares/ST/ndef/Src/message/ndef_types.su ./Middlewares/ST/ndef/Src/message/ndef_types_mime.cyclo ./Middlewares/ST/ndef/Src/message/ndef_types_mime.d ./Middlewares/ST/ndef/Src/message/ndef_types_mime.o ./Middlewares/ST/ndef/Src/message/ndef_types_mime.su ./Middlewares/ST/ndef/Src/message/ndef_types_rtd.cyclo ./Middlewares/ST/ndef/Src/message/ndef_types_rtd.d ./Middlewares/ST/ndef/Src/message/ndef_types_rtd.o ./Middlewares/ST/ndef/Src/message/ndef_types_rtd.su

.PHONY: clean-Middlewares-2f-ST-2f-ndef-2f-Src-2f-message

