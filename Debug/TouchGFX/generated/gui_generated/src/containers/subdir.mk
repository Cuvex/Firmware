################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/gui_generated/src/containers/boxDiceBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/close_btnBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/textAreaBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.cpp \
../TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.cpp 

OBJS += \
./TouchGFX/generated/gui_generated/src/containers/boxDiceBase.o \
./TouchGFX/generated/gui_generated/src/containers/close_btnBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.o \
./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.o \
./TouchGFX/generated/gui_generated/src/containers/textAreaBase.o \
./TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.o \
./TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.o 

CPP_DEPS += \
./TouchGFX/generated/gui_generated/src/containers/boxDiceBase.d \
./TouchGFX/generated/gui_generated/src/containers/close_btnBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.d \
./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.d \
./TouchGFX/generated/gui_generated/src/containers/textAreaBase.d \
./TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.d \
./TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/gui_generated/src/containers/%.o TouchGFX/generated/gui_generated/src/containers/%.su TouchGFX/generated/gui_generated/src/containers/%.cyclo: ../TouchGFX/generated/gui_generated/src/containers/%.cpp TouchGFX/generated/gui_generated/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-containers

clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-containers:
	-$(RM) ./TouchGFX/generated/gui_generated/src/containers/boxDiceBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/boxDiceBase.d ./TouchGFX/generated/gui_generated/src/containers/boxDiceBase.o ./TouchGFX/generated/gui_generated/src/containers/boxDiceBase.su ./TouchGFX/generated/gui_generated/src/containers/close_btnBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/close_btnBase.d ./TouchGFX/generated/gui_generated/src/containers/close_btnBase.o ./TouchGFX/generated/gui_generated/src/containers/close_btnBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_decrypt_passwordBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password1Base.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_password2Base.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_plaintextBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedNumBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedPassphraseBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_seedWordsBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_encrypt_tagAliasBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_generic_deviceAliasBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_diceNumBase.su ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.d ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.o ./TouchGFX/generated/gui_generated/src/containers/keyboard_wallet_passphraseBase.su ./TouchGFX/generated/gui_generated/src/containers/textAreaBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/textAreaBase.d ./TouchGFX/generated/gui_generated/src/containers/textAreaBase.o ./TouchGFX/generated/gui_generated/src/containers/textAreaBase.su ./TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.d ./TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.o ./TouchGFX/generated/gui_generated/src/containers/textAreaSelectedBase.su ./TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.cyclo ./TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.d ./TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.o ./TouchGFX/generated/gui_generated/src/containers/thinking_circlesBase.su

.PHONY: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-containers

