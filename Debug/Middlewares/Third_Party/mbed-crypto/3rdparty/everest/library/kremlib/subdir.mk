################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.c \
../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.c 

C_DEPS += \
./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.d \
./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.d 

OBJS += \
./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.o \
./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/%.o Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/%.su Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/%.cyclo: ../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/%.c Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/mbed-crypto/tests/include -I../Middlewares/Third_Party/mbed-crypto/tests/src/external_timing -I../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/include/everest -I../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/include/everest/kremlib -I../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/include/everest/kremlin -I../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/include/everest/kremlin/internal -I../Middlewares/Third_Party/mbed-crypto/3rdparty/everest/include/everest/vs2010 -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-mbed-2d-crypto-2f-3rdparty-2f-everest-2f-library-2f-kremlib

clean-Middlewares-2f-Third_Party-2f-mbed-2d-crypto-2f-3rdparty-2f-everest-2f-library-2f-kremlib:
	-$(RM) ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.cyclo ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.d ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.o ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt128_extracted.su ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.cyclo ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.d ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.o ./Middlewares/Third_Party/mbed-crypto/3rdparty/everest/library/kremlib/FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-mbed-2d-crypto-2f-3rdparty-2f-everest-2f-library-2f-kremlib

