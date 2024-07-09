################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.cpp 

OBJS += \
./TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.o \
./TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.o 

CPP_DEPS += \
./TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.d \
./TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/gui_generated/src/containers/%.o TouchGFX/generated/gui_generated/src/containers/%.su TouchGFX/generated/gui_generated/src/containers/%.cyclo: ../TouchGFX/generated/gui_generated/src/containers/%.cpp TouchGFX/generated/gui_generated/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-containers

clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-containers:
	-$(RM) ./TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/close_button_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardAlias_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardDeviceAlias_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardNumeric_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardPassphrase_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardPasswordCheck_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardPassword_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardPlainText_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboardSeed_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/textAreaSelected_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/textArea_containerBase.su ./TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.d ./TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.o ./TouchGFX/generated/gui_generated/src/containers/thinking_circles_containerBase.su

.PHONY: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-containers

