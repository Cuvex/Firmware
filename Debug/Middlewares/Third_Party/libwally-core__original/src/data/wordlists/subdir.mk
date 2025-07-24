################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.c \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.c \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.c \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.c \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.c \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.c \
../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.c 

C_DEPS += \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.d \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.d \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.d \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.d \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.d \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.d \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.d 

OBJS += \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.o \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.o \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.o \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.o \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.o \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.o \
./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/libwally-core__original/src/data/wordlists/%.o Middlewares/Third_Party/libwally-core__original/src/data/wordlists/%.su Middlewares/Third_Party/libwally-core__original/src/data/wordlists/%.cyclo: ../Middlewares/Third_Party/libwally-core__original/src/data/wordlists/%.c Middlewares/Third_Party/libwally-core__original/src/data/wordlists/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/Third_Party/libwally-core/include -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-libwally-2d-core__original-2f-src-2f-data-2f-wordlists

clean-Middlewares-2f-Third_Party-2f-libwally-2d-core__original-2f-src-2f-data-2f-wordlists:
	-$(RM) ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_simplified.su ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/chinese_traditional.su ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/english.su ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/french.su ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/italian.su ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/japanese.su ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.cyclo ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.d ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.o ./Middlewares/Third_Party/libwally-core__original/src/data/wordlists/spanish.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-libwally-2d-core__original-2f-src-2f-data-2f-wordlists

