################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.cpp \
../TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.cpp 

OBJS += \
./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.o \
./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.o 

CPP_DEPS += \
./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.d \
./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/screen_flow_psbt_screen/%.o TouchGFX/gui/src/screen_flow_psbt_screen/%.su TouchGFX/gui/src/screen_flow_psbt_screen/%.cyclo: ../TouchGFX/gui/src/screen_flow_psbt_screen/%.cpp TouchGFX/gui/src/screen_flow_psbt_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-screen_flow_psbt_screen

clean-TouchGFX-2f-gui-2f-src-2f-screen_flow_psbt_screen:
	-$(RM) ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.cyclo ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.d ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.o ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtPresenter.su ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.cyclo ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.d ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.o ./TouchGFX/gui/src/screen_flow_psbt_screen/screen_flow_psbtView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-screen_flow_psbt_screen

