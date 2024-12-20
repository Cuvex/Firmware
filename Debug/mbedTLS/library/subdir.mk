################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mbedTLS/library/debug.c \
../mbedTLS/library/mps_reader.c \
../mbedTLS/library/mps_trace.c \
../mbedTLS/library/net_sockets.c \
../mbedTLS/library/pkcs7.c \
../mbedTLS/library/ssl_cache.c \
../mbedTLS/library/ssl_ciphersuites.c \
../mbedTLS/library/ssl_client.c \
../mbedTLS/library/ssl_cookie.c \
../mbedTLS/library/ssl_msg.c \
../mbedTLS/library/ssl_ticket.c \
../mbedTLS/library/ssl_tls.c \
../mbedTLS/library/ssl_tls12_client.c \
../mbedTLS/library/ssl_tls12_server.c \
../mbedTLS/library/ssl_tls13_client.c \
../mbedTLS/library/ssl_tls13_generic.c \
../mbedTLS/library/ssl_tls13_keys.c \
../mbedTLS/library/ssl_tls13_server.c \
../mbedTLS/library/version.c \
../mbedTLS/library/x509.c \
../mbedTLS/library/x509_create.c \
../mbedTLS/library/x509_crl.c \
../mbedTLS/library/x509_crt.c \
../mbedTLS/library/x509_csr.c \
../mbedTLS/library/x509write.c \
../mbedTLS/library/x509write_crt.c \
../mbedTLS/library/x509write_csr.c 

C_DEPS += \
./mbedTLS/library/debug.d \
./mbedTLS/library/mps_reader.d \
./mbedTLS/library/mps_trace.d \
./mbedTLS/library/net_sockets.d \
./mbedTLS/library/pkcs7.d \
./mbedTLS/library/ssl_cache.d \
./mbedTLS/library/ssl_ciphersuites.d \
./mbedTLS/library/ssl_client.d \
./mbedTLS/library/ssl_cookie.d \
./mbedTLS/library/ssl_msg.d \
./mbedTLS/library/ssl_ticket.d \
./mbedTLS/library/ssl_tls.d \
./mbedTLS/library/ssl_tls12_client.d \
./mbedTLS/library/ssl_tls12_server.d \
./mbedTLS/library/ssl_tls13_client.d \
./mbedTLS/library/ssl_tls13_generic.d \
./mbedTLS/library/ssl_tls13_keys.d \
./mbedTLS/library/ssl_tls13_server.d \
./mbedTLS/library/version.d \
./mbedTLS/library/x509.d \
./mbedTLS/library/x509_create.d \
./mbedTLS/library/x509_crl.d \
./mbedTLS/library/x509_crt.d \
./mbedTLS/library/x509_csr.d \
./mbedTLS/library/x509write.d \
./mbedTLS/library/x509write_crt.d \
./mbedTLS/library/x509write_csr.d 

OBJS += \
./mbedTLS/library/debug.o \
./mbedTLS/library/mps_reader.o \
./mbedTLS/library/mps_trace.o \
./mbedTLS/library/net_sockets.o \
./mbedTLS/library/pkcs7.o \
./mbedTLS/library/ssl_cache.o \
./mbedTLS/library/ssl_ciphersuites.o \
./mbedTLS/library/ssl_client.o \
./mbedTLS/library/ssl_cookie.o \
./mbedTLS/library/ssl_msg.o \
./mbedTLS/library/ssl_ticket.o \
./mbedTLS/library/ssl_tls.o \
./mbedTLS/library/ssl_tls12_client.o \
./mbedTLS/library/ssl_tls12_server.o \
./mbedTLS/library/ssl_tls13_client.o \
./mbedTLS/library/ssl_tls13_generic.o \
./mbedTLS/library/ssl_tls13_keys.o \
./mbedTLS/library/ssl_tls13_server.o \
./mbedTLS/library/version.o \
./mbedTLS/library/x509.o \
./mbedTLS/library/x509_create.o \
./mbedTLS/library/x509_crl.o \
./mbedTLS/library/x509_crt.o \
./mbedTLS/library/x509_csr.o \
./mbedTLS/library/x509write.o \
./mbedTLS/library/x509write_crt.o \
./mbedTLS/library/x509write_csr.o 


# Each subdirectory must supply rules for building sources it contributes
mbedTLS/library/%.o mbedTLS/library/%.su mbedTLS/library/%.cyclo: ../mbedTLS/library/%.c mbedTLS/library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/Components/Common -I../Middlewares/ST/rfal/Inc -I../Middlewares/ST/ndef/Inc/poller -I../Middlewares/ST/ndef/Inc/message -I../Drivers/BSP/Components/ST25R95 -I../TouchGFX/gui/include/gui/widgets/qrcode -I../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -I../mbedTLS/include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mbedTLS-2f-library

clean-mbedTLS-2f-library:
	-$(RM) ./mbedTLS/library/debug.cyclo ./mbedTLS/library/debug.d ./mbedTLS/library/debug.o ./mbedTLS/library/debug.su ./mbedTLS/library/mps_reader.cyclo ./mbedTLS/library/mps_reader.d ./mbedTLS/library/mps_reader.o ./mbedTLS/library/mps_reader.su ./mbedTLS/library/mps_trace.cyclo ./mbedTLS/library/mps_trace.d ./mbedTLS/library/mps_trace.o ./mbedTLS/library/mps_trace.su ./mbedTLS/library/net_sockets.cyclo ./mbedTLS/library/net_sockets.d ./mbedTLS/library/net_sockets.o ./mbedTLS/library/net_sockets.su ./mbedTLS/library/pkcs7.cyclo ./mbedTLS/library/pkcs7.d ./mbedTLS/library/pkcs7.o ./mbedTLS/library/pkcs7.su ./mbedTLS/library/ssl_cache.cyclo ./mbedTLS/library/ssl_cache.d ./mbedTLS/library/ssl_cache.o ./mbedTLS/library/ssl_cache.su ./mbedTLS/library/ssl_ciphersuites.cyclo ./mbedTLS/library/ssl_ciphersuites.d ./mbedTLS/library/ssl_ciphersuites.o ./mbedTLS/library/ssl_ciphersuites.su ./mbedTLS/library/ssl_client.cyclo ./mbedTLS/library/ssl_client.d ./mbedTLS/library/ssl_client.o ./mbedTLS/library/ssl_client.su ./mbedTLS/library/ssl_cookie.cyclo ./mbedTLS/library/ssl_cookie.d ./mbedTLS/library/ssl_cookie.o ./mbedTLS/library/ssl_cookie.su ./mbedTLS/library/ssl_msg.cyclo ./mbedTLS/library/ssl_msg.d ./mbedTLS/library/ssl_msg.o ./mbedTLS/library/ssl_msg.su ./mbedTLS/library/ssl_ticket.cyclo ./mbedTLS/library/ssl_ticket.d ./mbedTLS/library/ssl_ticket.o ./mbedTLS/library/ssl_ticket.su ./mbedTLS/library/ssl_tls.cyclo ./mbedTLS/library/ssl_tls.d ./mbedTLS/library/ssl_tls.o ./mbedTLS/library/ssl_tls.su ./mbedTLS/library/ssl_tls12_client.cyclo ./mbedTLS/library/ssl_tls12_client.d ./mbedTLS/library/ssl_tls12_client.o ./mbedTLS/library/ssl_tls12_client.su ./mbedTLS/library/ssl_tls12_server.cyclo ./mbedTLS/library/ssl_tls12_server.d ./mbedTLS/library/ssl_tls12_server.o ./mbedTLS/library/ssl_tls12_server.su ./mbedTLS/library/ssl_tls13_client.cyclo ./mbedTLS/library/ssl_tls13_client.d ./mbedTLS/library/ssl_tls13_client.o ./mbedTLS/library/ssl_tls13_client.su ./mbedTLS/library/ssl_tls13_generic.cyclo ./mbedTLS/library/ssl_tls13_generic.d ./mbedTLS/library/ssl_tls13_generic.o ./mbedTLS/library/ssl_tls13_generic.su ./mbedTLS/library/ssl_tls13_keys.cyclo ./mbedTLS/library/ssl_tls13_keys.d ./mbedTLS/library/ssl_tls13_keys.o ./mbedTLS/library/ssl_tls13_keys.su ./mbedTLS/library/ssl_tls13_server.cyclo ./mbedTLS/library/ssl_tls13_server.d ./mbedTLS/library/ssl_tls13_server.o ./mbedTLS/library/ssl_tls13_server.su ./mbedTLS/library/version.cyclo ./mbedTLS/library/version.d ./mbedTLS/library/version.o ./mbedTLS/library/version.su ./mbedTLS/library/x509.cyclo ./mbedTLS/library/x509.d ./mbedTLS/library/x509.o ./mbedTLS/library/x509.su ./mbedTLS/library/x509_create.cyclo ./mbedTLS/library/x509_create.d ./mbedTLS/library/x509_create.o ./mbedTLS/library/x509_create.su ./mbedTLS/library/x509_crl.cyclo ./mbedTLS/library/x509_crl.d ./mbedTLS/library/x509_crl.o ./mbedTLS/library/x509_crl.su ./mbedTLS/library/x509_crt.cyclo ./mbedTLS/library/x509_crt.d ./mbedTLS/library/x509_crt.o ./mbedTLS/library/x509_crt.su ./mbedTLS/library/x509_csr.cyclo ./mbedTLS/library/x509_csr.d ./mbedTLS/library/x509_csr.o ./mbedTLS/library/x509_csr.su ./mbedTLS/library/x509write.cyclo ./mbedTLS/library/x509write.d ./mbedTLS/library/x509write.o ./mbedTLS/library/x509write.su ./mbedTLS/library/x509write_crt.cyclo ./mbedTLS/library/x509write_crt.d ./mbedTLS/library/x509write_crt.o ./mbedTLS/library/x509write_crt.su ./mbedTLS/library/x509write_csr.cyclo ./mbedTLS/library/x509write_csr.d ./mbedTLS/library/x509write_csr.o ./mbedTLS/library/x509write_csr.su

.PHONY: clean-mbedTLS-2f-library

