################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.c \
../Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.c \
../Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.c 

C_DEPS += \
./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.d \
./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.d \
./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.d 

OBJS += \
./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.o \
./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.o \
./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/%.o Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/%.su Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/%.cyclo: ../Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/%.c Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/libwally-core/include -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-libwally-2d-core__original-2f-src-2f-ccan-2f-ccan-2f-crypto-2f-ripemd160-2f-test

clean-Middlewares-2f-Third_Party-2f-libwally-2d-core__original-2f-src-2f-ccan-2f-ccan-2f-crypto-2f-ripemd160-2f-test:
	-$(RM) ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.cyclo ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.d ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.o ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-lotsa-data.su ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.cyclo ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.d ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.o ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-test-vectors.su ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.cyclo ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.d ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.o ./Middlewares/Third_Party/libwally-core__original/src/ccan/ccan/crypto/ripemd160/test/run-types.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-libwally-2d-core__original-2f-src-2f-ccan-2f-ccan-2f-crypto-2f-ripemd160-2f-test

