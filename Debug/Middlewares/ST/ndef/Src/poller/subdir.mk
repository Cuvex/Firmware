################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/ndef/Src/poller/ndef_poller.c \
../Middlewares/ST/ndef/Src/poller/ndef_t2t.c \
../Middlewares/ST/ndef/Src/poller/ndef_t3t.c \
../Middlewares/ST/ndef/Src/poller/ndef_t4t.c \
../Middlewares/ST/ndef/Src/poller/ndef_t5t.c 

C_DEPS += \
./Middlewares/ST/ndef/Src/poller/ndef_poller.d \
./Middlewares/ST/ndef/Src/poller/ndef_t2t.d \
./Middlewares/ST/ndef/Src/poller/ndef_t3t.d \
./Middlewares/ST/ndef/Src/poller/ndef_t4t.d \
./Middlewares/ST/ndef/Src/poller/ndef_t5t.d 

OBJS += \
./Middlewares/ST/ndef/Src/poller/ndef_poller.o \
./Middlewares/ST/ndef/Src/poller/ndef_t2t.o \
./Middlewares/ST/ndef/Src/poller/ndef_t3t.o \
./Middlewares/ST/ndef/Src/poller/ndef_t4t.o \
./Middlewares/ST/ndef/Src/poller/ndef_t5t.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/ndef/Src/poller/%.o Middlewares/ST/ndef/Src/poller/%.su Middlewares/ST/ndef/Src/poller/%.cyclo: ../Middlewares/ST/ndef/Src/poller/%.c Middlewares/ST/ndef/Src/poller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-ndef-2f-Src-2f-poller

clean-Middlewares-2f-ST-2f-ndef-2f-Src-2f-poller:
	-$(RM) ./Middlewares/ST/ndef/Src/poller/ndef_poller.cyclo ./Middlewares/ST/ndef/Src/poller/ndef_poller.d ./Middlewares/ST/ndef/Src/poller/ndef_poller.o ./Middlewares/ST/ndef/Src/poller/ndef_poller.su ./Middlewares/ST/ndef/Src/poller/ndef_t2t.cyclo ./Middlewares/ST/ndef/Src/poller/ndef_t2t.d ./Middlewares/ST/ndef/Src/poller/ndef_t2t.o ./Middlewares/ST/ndef/Src/poller/ndef_t2t.su ./Middlewares/ST/ndef/Src/poller/ndef_t3t.cyclo ./Middlewares/ST/ndef/Src/poller/ndef_t3t.d ./Middlewares/ST/ndef/Src/poller/ndef_t3t.o ./Middlewares/ST/ndef/Src/poller/ndef_t3t.su ./Middlewares/ST/ndef/Src/poller/ndef_t4t.cyclo ./Middlewares/ST/ndef/Src/poller/ndef_t4t.d ./Middlewares/ST/ndef/Src/poller/ndef_t4t.o ./Middlewares/ST/ndef/Src/poller/ndef_t4t.su ./Middlewares/ST/ndef/Src/poller/ndef_t5t.cyclo ./Middlewares/ST/ndef/Src/poller/ndef_t5t.d ./Middlewares/ST/ndef/Src/poller/ndef_t5t.o ./Middlewares/ST/ndef/Src/poller/ndef_t5t.su

.PHONY: clean-Middlewares-2f-ST-2f-ndef-2f-Src-2f-poller

