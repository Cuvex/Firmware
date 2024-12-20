################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/containers/boxDice.cpp \
../TouchGFX/gui/src/containers/close_btn.cpp \
../TouchGFX/gui/src/containers/keyboard_decrypt_password.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_password1.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_password2.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.cpp \
../TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.cpp \
../TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.cpp \
../TouchGFX/gui/src/containers/keyboard_wallet_diceNum.cpp \
../TouchGFX/gui/src/containers/keyboard_wallet_passphrase.cpp \
../TouchGFX/gui/src/containers/textArea.cpp \
../TouchGFX/gui/src/containers/textAreaSelected.cpp \
../TouchGFX/gui/src/containers/thinking_circles.cpp 

OBJS += \
./TouchGFX/gui/src/containers/boxDice.o \
./TouchGFX/gui/src/containers/close_btn.o \
./TouchGFX/gui/src/containers/keyboard_decrypt_password.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_password1.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_password2.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.o \
./TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.o \
./TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.o \
./TouchGFX/gui/src/containers/keyboard_wallet_diceNum.o \
./TouchGFX/gui/src/containers/keyboard_wallet_passphrase.o \
./TouchGFX/gui/src/containers/textArea.o \
./TouchGFX/gui/src/containers/textAreaSelected.o \
./TouchGFX/gui/src/containers/thinking_circles.o 

CPP_DEPS += \
./TouchGFX/gui/src/containers/boxDice.d \
./TouchGFX/gui/src/containers/close_btn.d \
./TouchGFX/gui/src/containers/keyboard_decrypt_password.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_password1.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_password2.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.d \
./TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.d \
./TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.d \
./TouchGFX/gui/src/containers/keyboard_wallet_diceNum.d \
./TouchGFX/gui/src/containers/keyboard_wallet_passphrase.d \
./TouchGFX/gui/src/containers/textArea.d \
./TouchGFX/gui/src/containers/textAreaSelected.d \
./TouchGFX/gui/src/containers/thinking_circles.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/containers/%.o TouchGFX/gui/src/containers/%.su TouchGFX/gui/src/containers/%.cyclo: ../TouchGFX/gui/src/containers/%.cpp TouchGFX/gui/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-containers

clean-TouchGFX-2f-gui-2f-src-2f-containers:
	-$(RM) ./TouchGFX/gui/src/containers/boxDice.cyclo ./TouchGFX/gui/src/containers/boxDice.d ./TouchGFX/gui/src/containers/boxDice.o ./TouchGFX/gui/src/containers/boxDice.su ./TouchGFX/gui/src/containers/close_btn.cyclo ./TouchGFX/gui/src/containers/close_btn.d ./TouchGFX/gui/src/containers/close_btn.o ./TouchGFX/gui/src/containers/close_btn.su ./TouchGFX/gui/src/containers/keyboard_decrypt_password.cyclo ./TouchGFX/gui/src/containers/keyboard_decrypt_password.d ./TouchGFX/gui/src/containers/keyboard_decrypt_password.o ./TouchGFX/gui/src/containers/keyboard_decrypt_password.su ./TouchGFX/gui/src/containers/keyboard_encrypt_password1.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_password1.d ./TouchGFX/gui/src/containers/keyboard_encrypt_password1.o ./TouchGFX/gui/src/containers/keyboard_encrypt_password1.su ./TouchGFX/gui/src/containers/keyboard_encrypt_password2.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_password2.d ./TouchGFX/gui/src/containers/keyboard_encrypt_password2.o ./TouchGFX/gui/src/containers/keyboard_encrypt_password2.su ./TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.d ./TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.o ./TouchGFX/gui/src/containers/keyboard_encrypt_plaintext.su ./TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.d ./TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.o ./TouchGFX/gui/src/containers/keyboard_encrypt_seedNum.su ./TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.d ./TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.o ./TouchGFX/gui/src/containers/keyboard_encrypt_seedPassphrase.su ./TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.d ./TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.o ./TouchGFX/gui/src/containers/keyboard_encrypt_seedWords.su ./TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.cyclo ./TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.d ./TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.o ./TouchGFX/gui/src/containers/keyboard_encrypt_tagAlias.su ./TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.cyclo ./TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.d ./TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.o ./TouchGFX/gui/src/containers/keyboard_generic_deviceAlias.su ./TouchGFX/gui/src/containers/keyboard_wallet_diceNum.cyclo ./TouchGFX/gui/src/containers/keyboard_wallet_diceNum.d ./TouchGFX/gui/src/containers/keyboard_wallet_diceNum.o ./TouchGFX/gui/src/containers/keyboard_wallet_diceNum.su ./TouchGFX/gui/src/containers/keyboard_wallet_passphrase.cyclo ./TouchGFX/gui/src/containers/keyboard_wallet_passphrase.d ./TouchGFX/gui/src/containers/keyboard_wallet_passphrase.o ./TouchGFX/gui/src/containers/keyboard_wallet_passphrase.su ./TouchGFX/gui/src/containers/textArea.cyclo ./TouchGFX/gui/src/containers/textArea.d ./TouchGFX/gui/src/containers/textArea.o ./TouchGFX/gui/src/containers/textArea.su ./TouchGFX/gui/src/containers/textAreaSelected.cyclo ./TouchGFX/gui/src/containers/textAreaSelected.d ./TouchGFX/gui/src/containers/textAreaSelected.o ./TouchGFX/gui/src/containers/textAreaSelected.su ./TouchGFX/gui/src/containers/thinking_circles.cyclo ./TouchGFX/gui/src/containers/thinking_circles.d ./TouchGFX/gui/src/containers/thinking_circles.o ./TouchGFX/gui/src/containers/thinking_circles.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-containers

