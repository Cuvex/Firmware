################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.cpp \
../TouchGFX/gui/src/screen_aux_screen/Screen_auxView.cpp 

OBJS += \
./TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.o \
./TouchGFX/gui/src/screen_aux_screen/Screen_auxView.o 

CPP_DEPS += \
./TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.d \
./TouchGFX/gui/src/screen_aux_screen/Screen_auxView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/screen_aux_screen/%.o TouchGFX/gui/src/screen_aux_screen/%.su TouchGFX/gui/src/screen_aux_screen/%.cyclo: ../TouchGFX/gui/src/screen_aux_screen/%.cpp TouchGFX/gui/src/screen_aux_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/Third_Party/mbed-crypto/include -I../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../Middlewares/Third_Party/mbed-crypto/include/psa -I../Middlewares/Third_Party/mbed-crypto/library -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-screen_aux_screen

clean-TouchGFX-2f-gui-2f-src-2f-screen_aux_screen:
	-$(RM) ./TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.cyclo ./TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.d ./TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.o ./TouchGFX/gui/src/screen_aux_screen/Screen_auxPresenter.su ./TouchGFX/gui/src/screen_aux_screen/Screen_auxView.cyclo ./TouchGFX/gui/src/screen_aux_screen/Screen_auxView.d ./TouchGFX/gui/src/screen_aux_screen/Screen_auxView.o ./TouchGFX/gui/src/screen_aux_screen/Screen_auxView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-screen_aux_screen

