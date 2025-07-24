################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/Third_Party/uBitcoin/src/BaseClasses.cpp \
../Middlewares/Third_Party/uBitcoin/src/Bitcoin.cpp \
../Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.cpp \
../Middlewares/Third_Party/uBitcoin/src/Conversion.cpp \
../Middlewares/Third_Party/uBitcoin/src/Electrum.cpp \
../Middlewares/Third_Party/uBitcoin/src/HDWallet.cpp \
../Middlewares/Third_Party/uBitcoin/src/Hash.cpp \
../Middlewares/Third_Party/uBitcoin/src/Networks.cpp \
../Middlewares/Third_Party/uBitcoin/src/PSBT.cpp \
../Middlewares/Third_Party/uBitcoin/src/Script.cpp \
../Middlewares/Third_Party/uBitcoin/src/Transaction.cpp 

OBJS += \
./Middlewares/Third_Party/uBitcoin/src/BaseClasses.o \
./Middlewares/Third_Party/uBitcoin/src/Bitcoin.o \
./Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.o \
./Middlewares/Third_Party/uBitcoin/src/Conversion.o \
./Middlewares/Third_Party/uBitcoin/src/Electrum.o \
./Middlewares/Third_Party/uBitcoin/src/HDWallet.o \
./Middlewares/Third_Party/uBitcoin/src/Hash.o \
./Middlewares/Third_Party/uBitcoin/src/Networks.o \
./Middlewares/Third_Party/uBitcoin/src/PSBT.o \
./Middlewares/Third_Party/uBitcoin/src/Script.o \
./Middlewares/Third_Party/uBitcoin/src/Transaction.o 

CPP_DEPS += \
./Middlewares/Third_Party/uBitcoin/src/BaseClasses.d \
./Middlewares/Third_Party/uBitcoin/src/Bitcoin.d \
./Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.d \
./Middlewares/Third_Party/uBitcoin/src/Conversion.d \
./Middlewares/Third_Party/uBitcoin/src/Electrum.d \
./Middlewares/Third_Party/uBitcoin/src/HDWallet.d \
./Middlewares/Third_Party/uBitcoin/src/Hash.d \
./Middlewares/Third_Party/uBitcoin/src/Networks.d \
./Middlewares/Third_Party/uBitcoin/src/PSBT.d \
./Middlewares/Third_Party/uBitcoin/src/Script.d \
./Middlewares/Third_Party/uBitcoin/src/Transaction.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/uBitcoin/src/%.o Middlewares/Third_Party/uBitcoin/src/%.su Middlewares/Third_Party/uBitcoin/src/%.cyclo: ../Middlewares/Third_Party/uBitcoin/src/%.cpp Middlewares/Third_Party/uBitcoin/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/uBitcoin/src -I../Middlewares/Third_Party/uBitcoin/src/utility/trezor -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-src

clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-src:
	-$(RM) ./Middlewares/Third_Party/uBitcoin/src/BaseClasses.cyclo ./Middlewares/Third_Party/uBitcoin/src/BaseClasses.d ./Middlewares/Third_Party/uBitcoin/src/BaseClasses.o ./Middlewares/Third_Party/uBitcoin/src/BaseClasses.su ./Middlewares/Third_Party/uBitcoin/src/Bitcoin.cyclo ./Middlewares/Third_Party/uBitcoin/src/Bitcoin.d ./Middlewares/Third_Party/uBitcoin/src/Bitcoin.o ./Middlewares/Third_Party/uBitcoin/src/Bitcoin.su ./Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.cyclo ./Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.d ./Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.o ./Middlewares/Third_Party/uBitcoin/src/BitcoinCurve.su ./Middlewares/Third_Party/uBitcoin/src/Conversion.cyclo ./Middlewares/Third_Party/uBitcoin/src/Conversion.d ./Middlewares/Third_Party/uBitcoin/src/Conversion.o ./Middlewares/Third_Party/uBitcoin/src/Conversion.su ./Middlewares/Third_Party/uBitcoin/src/Electrum.cyclo ./Middlewares/Third_Party/uBitcoin/src/Electrum.d ./Middlewares/Third_Party/uBitcoin/src/Electrum.o ./Middlewares/Third_Party/uBitcoin/src/Electrum.su ./Middlewares/Third_Party/uBitcoin/src/HDWallet.cyclo ./Middlewares/Third_Party/uBitcoin/src/HDWallet.d ./Middlewares/Third_Party/uBitcoin/src/HDWallet.o ./Middlewares/Third_Party/uBitcoin/src/HDWallet.su ./Middlewares/Third_Party/uBitcoin/src/Hash.cyclo ./Middlewares/Third_Party/uBitcoin/src/Hash.d ./Middlewares/Third_Party/uBitcoin/src/Hash.o ./Middlewares/Third_Party/uBitcoin/src/Hash.su ./Middlewares/Third_Party/uBitcoin/src/Networks.cyclo ./Middlewares/Third_Party/uBitcoin/src/Networks.d ./Middlewares/Third_Party/uBitcoin/src/Networks.o ./Middlewares/Third_Party/uBitcoin/src/Networks.su ./Middlewares/Third_Party/uBitcoin/src/PSBT.cyclo ./Middlewares/Third_Party/uBitcoin/src/PSBT.d ./Middlewares/Third_Party/uBitcoin/src/PSBT.o ./Middlewares/Third_Party/uBitcoin/src/PSBT.su ./Middlewares/Third_Party/uBitcoin/src/Script.cyclo ./Middlewares/Third_Party/uBitcoin/src/Script.d ./Middlewares/Third_Party/uBitcoin/src/Script.o ./Middlewares/Third_Party/uBitcoin/src/Script.su ./Middlewares/Third_Party/uBitcoin/src/Transaction.cyclo ./Middlewares/Third_Party/uBitcoin/src/Transaction.d ./Middlewares/Third_Party/uBitcoin/src/Transaction.o ./Middlewares/Third_Party/uBitcoin/src/Transaction.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-src

