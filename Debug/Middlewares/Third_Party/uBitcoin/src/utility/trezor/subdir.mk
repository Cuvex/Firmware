################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.c \
../Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.c 

C_DEPS += \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.d \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.d 

OBJS += \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.o \
./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/uBitcoin/src/utility/trezor/%.o Middlewares/Third_Party/uBitcoin/src/utility/trezor/%.su Middlewares/Third_Party/uBitcoin/src/utility/trezor/%.cyclo: ../Middlewares/Third_Party/uBitcoin/src/utility/trezor/%.c Middlewares/Third_Party/uBitcoin/src/utility/trezor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/uBitcoin/src -I../Middlewares/Third_Party/uBitcoin/src/utility/trezor -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-src-2f-utility-2f-trezor

clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-src-2f-utility-2f-trezor:
	-$(RM) ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/address.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/base58.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bignum.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/bip39.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ecdsa.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hasher.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/hmac.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/memzero.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/pbkdf2.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rand.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/rfc6979.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/ripemd160.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/secp256k1.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha2.su ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.cyclo ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.d ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.o ./Middlewares/Third_Party/uBitcoin/src/utility/trezor/sha3.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-uBitcoin-2f-src-2f-utility-2f-trezor

