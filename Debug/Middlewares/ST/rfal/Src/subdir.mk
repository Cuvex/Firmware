################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/rfal/Src/rfal_analogConfig.c \
../Middlewares/ST/rfal/Src/rfal_crc.c \
../Middlewares/ST/rfal/Src/rfal_iso15693_2.c \
../Middlewares/ST/rfal/Src/rfal_isoDep.c \
../Middlewares/ST/rfal/Src/rfal_nfc.c \
../Middlewares/ST/rfal/Src/rfal_nfcDep.c \
../Middlewares/ST/rfal/Src/rfal_nfca.c \
../Middlewares/ST/rfal/Src/rfal_nfcb.c \
../Middlewares/ST/rfal/Src/rfal_nfcf.c \
../Middlewares/ST/rfal/Src/rfal_nfcv.c \
../Middlewares/ST/rfal/Src/rfal_rfst25r95.c \
../Middlewares/ST/rfal/Src/rfal_st25tb.c \
../Middlewares/ST/rfal/Src/rfal_st25xv.c \
../Middlewares/ST/rfal/Src/rfal_t1t.c \
../Middlewares/ST/rfal/Src/rfal_t2t.c \
../Middlewares/ST/rfal/Src/rfal_t4t.c 

C_DEPS += \
./Middlewares/ST/rfal/Src/rfal_analogConfig.d \
./Middlewares/ST/rfal/Src/rfal_crc.d \
./Middlewares/ST/rfal/Src/rfal_iso15693_2.d \
./Middlewares/ST/rfal/Src/rfal_isoDep.d \
./Middlewares/ST/rfal/Src/rfal_nfc.d \
./Middlewares/ST/rfal/Src/rfal_nfcDep.d \
./Middlewares/ST/rfal/Src/rfal_nfca.d \
./Middlewares/ST/rfal/Src/rfal_nfcb.d \
./Middlewares/ST/rfal/Src/rfal_nfcf.d \
./Middlewares/ST/rfal/Src/rfal_nfcv.d \
./Middlewares/ST/rfal/Src/rfal_rfst25r95.d \
./Middlewares/ST/rfal/Src/rfal_st25tb.d \
./Middlewares/ST/rfal/Src/rfal_st25xv.d \
./Middlewares/ST/rfal/Src/rfal_t1t.d \
./Middlewares/ST/rfal/Src/rfal_t2t.d \
./Middlewares/ST/rfal/Src/rfal_t4t.d 

OBJS += \
./Middlewares/ST/rfal/Src/rfal_analogConfig.o \
./Middlewares/ST/rfal/Src/rfal_crc.o \
./Middlewares/ST/rfal/Src/rfal_iso15693_2.o \
./Middlewares/ST/rfal/Src/rfal_isoDep.o \
./Middlewares/ST/rfal/Src/rfal_nfc.o \
./Middlewares/ST/rfal/Src/rfal_nfcDep.o \
./Middlewares/ST/rfal/Src/rfal_nfca.o \
./Middlewares/ST/rfal/Src/rfal_nfcb.o \
./Middlewares/ST/rfal/Src/rfal_nfcf.o \
./Middlewares/ST/rfal/Src/rfal_nfcv.o \
./Middlewares/ST/rfal/Src/rfal_rfst25r95.o \
./Middlewares/ST/rfal/Src/rfal_st25tb.o \
./Middlewares/ST/rfal/Src/rfal_st25xv.o \
./Middlewares/ST/rfal/Src/rfal_t1t.o \
./Middlewares/ST/rfal/Src/rfal_t2t.o \
./Middlewares/ST/rfal/Src/rfal_t4t.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/rfal/Src/%.o Middlewares/ST/rfal/Src/%.su Middlewares/ST/rfal/Src/%.cyclo: ../Middlewares/ST/rfal/Src/%.c Middlewares/ST/rfal/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-rfal-2f-Src

clean-Middlewares-2f-ST-2f-rfal-2f-Src:
	-$(RM) ./Middlewares/ST/rfal/Src/rfal_analogConfig.cyclo ./Middlewares/ST/rfal/Src/rfal_analogConfig.d ./Middlewares/ST/rfal/Src/rfal_analogConfig.o ./Middlewares/ST/rfal/Src/rfal_analogConfig.su ./Middlewares/ST/rfal/Src/rfal_crc.cyclo ./Middlewares/ST/rfal/Src/rfal_crc.d ./Middlewares/ST/rfal/Src/rfal_crc.o ./Middlewares/ST/rfal/Src/rfal_crc.su ./Middlewares/ST/rfal/Src/rfal_iso15693_2.cyclo ./Middlewares/ST/rfal/Src/rfal_iso15693_2.d ./Middlewares/ST/rfal/Src/rfal_iso15693_2.o ./Middlewares/ST/rfal/Src/rfal_iso15693_2.su ./Middlewares/ST/rfal/Src/rfal_isoDep.cyclo ./Middlewares/ST/rfal/Src/rfal_isoDep.d ./Middlewares/ST/rfal/Src/rfal_isoDep.o ./Middlewares/ST/rfal/Src/rfal_isoDep.su ./Middlewares/ST/rfal/Src/rfal_nfc.cyclo ./Middlewares/ST/rfal/Src/rfal_nfc.d ./Middlewares/ST/rfal/Src/rfal_nfc.o ./Middlewares/ST/rfal/Src/rfal_nfc.su ./Middlewares/ST/rfal/Src/rfal_nfcDep.cyclo ./Middlewares/ST/rfal/Src/rfal_nfcDep.d ./Middlewares/ST/rfal/Src/rfal_nfcDep.o ./Middlewares/ST/rfal/Src/rfal_nfcDep.su ./Middlewares/ST/rfal/Src/rfal_nfca.cyclo ./Middlewares/ST/rfal/Src/rfal_nfca.d ./Middlewares/ST/rfal/Src/rfal_nfca.o ./Middlewares/ST/rfal/Src/rfal_nfca.su ./Middlewares/ST/rfal/Src/rfal_nfcb.cyclo ./Middlewares/ST/rfal/Src/rfal_nfcb.d ./Middlewares/ST/rfal/Src/rfal_nfcb.o ./Middlewares/ST/rfal/Src/rfal_nfcb.su ./Middlewares/ST/rfal/Src/rfal_nfcf.cyclo ./Middlewares/ST/rfal/Src/rfal_nfcf.d ./Middlewares/ST/rfal/Src/rfal_nfcf.o ./Middlewares/ST/rfal/Src/rfal_nfcf.su ./Middlewares/ST/rfal/Src/rfal_nfcv.cyclo ./Middlewares/ST/rfal/Src/rfal_nfcv.d ./Middlewares/ST/rfal/Src/rfal_nfcv.o ./Middlewares/ST/rfal/Src/rfal_nfcv.su ./Middlewares/ST/rfal/Src/rfal_rfst25r95.cyclo ./Middlewares/ST/rfal/Src/rfal_rfst25r95.d ./Middlewares/ST/rfal/Src/rfal_rfst25r95.o ./Middlewares/ST/rfal/Src/rfal_rfst25r95.su ./Middlewares/ST/rfal/Src/rfal_st25tb.cyclo ./Middlewares/ST/rfal/Src/rfal_st25tb.d ./Middlewares/ST/rfal/Src/rfal_st25tb.o ./Middlewares/ST/rfal/Src/rfal_st25tb.su ./Middlewares/ST/rfal/Src/rfal_st25xv.cyclo ./Middlewares/ST/rfal/Src/rfal_st25xv.d ./Middlewares/ST/rfal/Src/rfal_st25xv.o ./Middlewares/ST/rfal/Src/rfal_st25xv.su ./Middlewares/ST/rfal/Src/rfal_t1t.cyclo ./Middlewares/ST/rfal/Src/rfal_t1t.d ./Middlewares/ST/rfal/Src/rfal_t1t.o ./Middlewares/ST/rfal/Src/rfal_t1t.su ./Middlewares/ST/rfal/Src/rfal_t2t.cyclo ./Middlewares/ST/rfal/Src/rfal_t2t.d ./Middlewares/ST/rfal/Src/rfal_t2t.o ./Middlewares/ST/rfal/Src/rfal_t2t.su ./Middlewares/ST/rfal/Src/rfal_t4t.cyclo ./Middlewares/ST/rfal/Src/rfal_t4t.d ./Middlewares/ST/rfal/Src/rfal_t4t.o ./Middlewares/ST/rfal/Src/rfal_t4t.su

.PHONY: clean-Middlewares-2f-ST-2f-rfal-2f-Src

