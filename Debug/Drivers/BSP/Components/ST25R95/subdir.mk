################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/ST25R95/st25r95.c \
../Drivers/BSP/Components/ST25R95/st25r95_com.c \
../Drivers/BSP/Components/ST25R95/st25r95_com_spi.c \
../Drivers/BSP/Components/ST25R95/st25r95_com_uart.c \
../Drivers/BSP/Components/ST25R95/timer.c 

C_DEPS += \
./Drivers/BSP/Components/ST25R95/st25r95.d \
./Drivers/BSP/Components/ST25R95/st25r95_com.d \
./Drivers/BSP/Components/ST25R95/st25r95_com_spi.d \
./Drivers/BSP/Components/ST25R95/st25r95_com_uart.d \
./Drivers/BSP/Components/ST25R95/timer.d 

OBJS += \
./Drivers/BSP/Components/ST25R95/st25r95.o \
./Drivers/BSP/Components/ST25R95/st25r95_com.o \
./Drivers/BSP/Components/ST25R95/st25r95_com_spi.o \
./Drivers/BSP/Components/ST25R95/st25r95_com_uart.o \
./Drivers/BSP/Components/ST25R95/timer.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/ST25R95/%.o Drivers/BSP/Components/ST25R95/%.su Drivers/BSP/Components/ST25R95/%.cyclo: ../Drivers/BSP/Components/ST25R95/%.c Drivers/BSP/Components/ST25R95/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-ST25R95

clean-Drivers-2f-BSP-2f-Components-2f-ST25R95:
	-$(RM) ./Drivers/BSP/Components/ST25R95/st25r95.cyclo ./Drivers/BSP/Components/ST25R95/st25r95.d ./Drivers/BSP/Components/ST25R95/st25r95.o ./Drivers/BSP/Components/ST25R95/st25r95.su ./Drivers/BSP/Components/ST25R95/st25r95_com.cyclo ./Drivers/BSP/Components/ST25R95/st25r95_com.d ./Drivers/BSP/Components/ST25R95/st25r95_com.o ./Drivers/BSP/Components/ST25R95/st25r95_com.su ./Drivers/BSP/Components/ST25R95/st25r95_com_spi.cyclo ./Drivers/BSP/Components/ST25R95/st25r95_com_spi.d ./Drivers/BSP/Components/ST25R95/st25r95_com_spi.o ./Drivers/BSP/Components/ST25R95/st25r95_com_spi.su ./Drivers/BSP/Components/ST25R95/st25r95_com_uart.cyclo ./Drivers/BSP/Components/ST25R95/st25r95_com_uart.d ./Drivers/BSP/Components/ST25R95/st25r95_com_uart.o ./Drivers/BSP/Components/ST25R95/st25r95_com_uart.su ./Drivers/BSP/Components/ST25R95/timer.cyclo ./Drivers/BSP/Components/ST25R95/timer.d ./Drivers/BSP/Components/ST25R95/timer.o ./Drivers/BSP/Components/ST25R95/timer.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-ST25R95

