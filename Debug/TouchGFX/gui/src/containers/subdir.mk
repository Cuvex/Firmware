################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/containers/close_button_container.cpp \
../TouchGFX/gui/src/containers/keyboardAlias_container.cpp \
../TouchGFX/gui/src/containers/keyboardDeviceAlias_container.cpp \
../TouchGFX/gui/src/containers/keyboardNumeric_container.cpp \
../TouchGFX/gui/src/containers/keyboardPassphrase_container.cpp \
../TouchGFX/gui/src/containers/keyboardPasswordCheck_container.cpp \
../TouchGFX/gui/src/containers/keyboardPassword_container.cpp \
../TouchGFX/gui/src/containers/keyboardPlainText_container.cpp \
../TouchGFX/gui/src/containers/keyboardSeed_container.cpp \
../TouchGFX/gui/src/containers/textAreaSelected_container.cpp \
../TouchGFX/gui/src/containers/textArea_container.cpp \
../TouchGFX/gui/src/containers/thinking_circles_container.cpp 

OBJS += \
./TouchGFX/gui/src/containers/close_button_container.o \
./TouchGFX/gui/src/containers/keyboardAlias_container.o \
./TouchGFX/gui/src/containers/keyboardDeviceAlias_container.o \
./TouchGFX/gui/src/containers/keyboardNumeric_container.o \
./TouchGFX/gui/src/containers/keyboardPassphrase_container.o \
./TouchGFX/gui/src/containers/keyboardPasswordCheck_container.o \
./TouchGFX/gui/src/containers/keyboardPassword_container.o \
./TouchGFX/gui/src/containers/keyboardPlainText_container.o \
./TouchGFX/gui/src/containers/keyboardSeed_container.o \
./TouchGFX/gui/src/containers/textAreaSelected_container.o \
./TouchGFX/gui/src/containers/textArea_container.o \
./TouchGFX/gui/src/containers/thinking_circles_container.o 

CPP_DEPS += \
./TouchGFX/gui/src/containers/close_button_container.d \
./TouchGFX/gui/src/containers/keyboardAlias_container.d \
./TouchGFX/gui/src/containers/keyboardDeviceAlias_container.d \
./TouchGFX/gui/src/containers/keyboardNumeric_container.d \
./TouchGFX/gui/src/containers/keyboardPassphrase_container.d \
./TouchGFX/gui/src/containers/keyboardPasswordCheck_container.d \
./TouchGFX/gui/src/containers/keyboardPassword_container.d \
./TouchGFX/gui/src/containers/keyboardPlainText_container.d \
./TouchGFX/gui/src/containers/keyboardSeed_container.d \
./TouchGFX/gui/src/containers/textAreaSelected_container.d \
./TouchGFX/gui/src/containers/textArea_container.d \
./TouchGFX/gui/src/containers/thinking_circles_container.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/containers/%.o TouchGFX/gui/src/containers/%.su TouchGFX/gui/src/containers/%.cyclo: ../TouchGFX/gui/src/containers/%.cpp TouchGFX/gui/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-containers

clean-TouchGFX-2f-gui-2f-src-2f-containers:
	-$(RM) ./TouchGFX/gui/src/containers/close_button_container.cyclo ./TouchGFX/gui/src/containers/close_button_container.d ./TouchGFX/gui/src/containers/close_button_container.o ./TouchGFX/gui/src/containers/close_button_container.su ./TouchGFX/gui/src/containers/keyboardAlias_container.cyclo ./TouchGFX/gui/src/containers/keyboardAlias_container.d ./TouchGFX/gui/src/containers/keyboardAlias_container.o ./TouchGFX/gui/src/containers/keyboardAlias_container.su ./TouchGFX/gui/src/containers/keyboardDeviceAlias_container.cyclo ./TouchGFX/gui/src/containers/keyboardDeviceAlias_container.d ./TouchGFX/gui/src/containers/keyboardDeviceAlias_container.o ./TouchGFX/gui/src/containers/keyboardDeviceAlias_container.su ./TouchGFX/gui/src/containers/keyboardNumeric_container.cyclo ./TouchGFX/gui/src/containers/keyboardNumeric_container.d ./TouchGFX/gui/src/containers/keyboardNumeric_container.o ./TouchGFX/gui/src/containers/keyboardNumeric_container.su ./TouchGFX/gui/src/containers/keyboardPassphrase_container.cyclo ./TouchGFX/gui/src/containers/keyboardPassphrase_container.d ./TouchGFX/gui/src/containers/keyboardPassphrase_container.o ./TouchGFX/gui/src/containers/keyboardPassphrase_container.su ./TouchGFX/gui/src/containers/keyboardPasswordCheck_container.cyclo ./TouchGFX/gui/src/containers/keyboardPasswordCheck_container.d ./TouchGFX/gui/src/containers/keyboardPasswordCheck_container.o ./TouchGFX/gui/src/containers/keyboardPasswordCheck_container.su ./TouchGFX/gui/src/containers/keyboardPassword_container.cyclo ./TouchGFX/gui/src/containers/keyboardPassword_container.d ./TouchGFX/gui/src/containers/keyboardPassword_container.o ./TouchGFX/gui/src/containers/keyboardPassword_container.su ./TouchGFX/gui/src/containers/keyboardPlainText_container.cyclo ./TouchGFX/gui/src/containers/keyboardPlainText_container.d ./TouchGFX/gui/src/containers/keyboardPlainText_container.o ./TouchGFX/gui/src/containers/keyboardPlainText_container.su ./TouchGFX/gui/src/containers/keyboardSeed_container.cyclo ./TouchGFX/gui/src/containers/keyboardSeed_container.d ./TouchGFX/gui/src/containers/keyboardSeed_container.o ./TouchGFX/gui/src/containers/keyboardSeed_container.su ./TouchGFX/gui/src/containers/textAreaSelected_container.cyclo ./TouchGFX/gui/src/containers/textAreaSelected_container.d ./TouchGFX/gui/src/containers/textAreaSelected_container.o ./TouchGFX/gui/src/containers/textAreaSelected_container.su ./TouchGFX/gui/src/containers/textArea_container.cyclo ./TouchGFX/gui/src/containers/textArea_container.d ./TouchGFX/gui/src/containers/textArea_container.o ./TouchGFX/gui/src/containers/textArea_container.su ./TouchGFX/gui/src/containers/thinking_circles_container.cyclo ./TouchGFX/gui/src/containers/thinking_circles_container.d ./TouchGFX/gui/src/containers/thinking_circles_container.o ./TouchGFX/gui/src/containers/thinking_circles_container.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-containers

