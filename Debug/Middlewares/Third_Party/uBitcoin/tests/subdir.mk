################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/Third_Party/uBitcoin/tests/test_conversion.cpp \
../Middlewares/Third_Party/uBitcoin/tests/test_hash.cpp \
../Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.cpp \
../Middlewares/Third_Party/uBitcoin/tests/test_schnorr.cpp 

C_SRCS += \
../Middlewares/Third_Party/uBitcoin/tests/sysrand.c 

C_DEPS += \
./Middlewares/Third_Party/uBitcoin/tests/sysrand.d 

OBJS += \
./Middlewares/Third_Party/uBitcoin/tests/sysrand.o \
./Middlewares/Third_Party/uBitcoin/tests/test_conversion.o \
./Middlewares/Third_Party/uBitcoin/tests/test_hash.o \
./Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.o \
./Middlewares/Third_Party/uBitcoin/tests/test_schnorr.o 

CPP_DEPS += \
./Middlewares/Third_Party/uBitcoin/tests/test_conversion.d \
./Middlewares/Third_Party/uBitcoin/tests/test_hash.d \
./Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.d \
./Middlewares/Third_Party/uBitcoin/tests/test_schnorr.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/uBitcoin/tests/%.o Middlewares/Third_Party/uBitcoin/tests/%.su Middlewares/Third_Party/uBitcoin/tests/%.cyclo: ../Middlewares/Third_Party/uBitcoin/tests/%.c Middlewares/Third_Party/uBitcoin/tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/uBitcoin/src -I../Middlewares/Third_Party/uBitcoin/src/utility/trezor -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/uBitcoin/tests/%.o Middlewares/Third_Party/uBitcoin/tests/%.su Middlewares/Third_Party/uBitcoin/tests/%.cyclo: ../Middlewares/Third_Party/uBitcoin/tests/%.cpp Middlewares/Third_Party/uBitcoin/tests/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/uBitcoin/src -I../Middlewares/Third_Party/uBitcoin/src/utility/trezor -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-tests

clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-tests:
	-$(RM) ./Middlewares/Third_Party/uBitcoin/tests/sysrand.cyclo ./Middlewares/Third_Party/uBitcoin/tests/sysrand.d ./Middlewares/Third_Party/uBitcoin/tests/sysrand.o ./Middlewares/Third_Party/uBitcoin/tests/sysrand.su ./Middlewares/Third_Party/uBitcoin/tests/test_conversion.cyclo ./Middlewares/Third_Party/uBitcoin/tests/test_conversion.d ./Middlewares/Third_Party/uBitcoin/tests/test_conversion.o ./Middlewares/Third_Party/uBitcoin/tests/test_conversion.su ./Middlewares/Third_Party/uBitcoin/tests/test_hash.cyclo ./Middlewares/Third_Party/uBitcoin/tests/test_hash.d ./Middlewares/Third_Party/uBitcoin/tests/test_hash.o ./Middlewares/Third_Party/uBitcoin/tests/test_hash.su ./Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.cyclo ./Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.d ./Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.o ./Middlewares/Third_Party/uBitcoin/tests/test_mnemonic.su ./Middlewares/Third_Party/uBitcoin/tests/test_schnorr.cyclo ./Middlewares/Third_Party/uBitcoin/tests/test_schnorr.d ./Middlewares/Third_Party/uBitcoin/tests/test_schnorr.o ./Middlewares/Third_Party/uBitcoin/tests/test_schnorr.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-tests

