################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TouchGFX/target/generated/subdir.mk
-include TouchGFX/target/subdir.mk
-include TouchGFX/gui/src/widgets/qrcode/subdir.mk
-include TouchGFX/gui/src/screen_menu_screen/subdir.mk
-include TouchGFX/gui/src/screen_init_screen/subdir.mk
-include TouchGFX/gui/src/screen_flow_wallet_screen/subdir.mk
-include TouchGFX/gui/src/screen_flow_settings_screen/subdir.mk
-include TouchGFX/gui/src/screen_flow_psbt_screen/subdir.mk
-include TouchGFX/gui/src/screen_flow_encrypt_screen/subdir.mk
-include TouchGFX/gui/src/screen_flow_decrypt_screen/subdir.mk
-include TouchGFX/gui/src/screen_flow_clone_screen/subdir.mk
-include TouchGFX/gui/src/model/subdir.mk
-include TouchGFX/gui/src/containers/subdir.mk
-include TouchGFX/gui/src/common/subdir.mk
-include TouchGFX/generated/texts/src/subdir.mk
-include TouchGFX/generated/images/src/menu_images/subdir.mk
-include TouchGFX/generated/images/src/keyboard_images/numeric/subdir.mk
-include TouchGFX/generated/images/src/keyboard_images/alpha_numeric/subdir.mk
-include TouchGFX/generated/images/src/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_menu_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_init_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_flow_wallet_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_flow_settings_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_flow_psbt_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_flow_encrypt_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_flow_decrypt_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen_flow_clone_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/containers/subdir.mk
-include TouchGFX/generated/gui_generated/src/common/subdir.mk
-include TouchGFX/generated/fonts/src/subdir.mk
-include TouchGFX/App/subdir.mk
-include Middlewares/Third_Party/mbed-crypto/library/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Middlewares/ST/rfal/Src/subdir.mk
-include Middlewares/ST/ndef/Src/poller/subdir.mk
-include Middlewares/ST/ndef/Src/message/subdir.mk
-include Drivers/STM32U5xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/Components/ft5336/subdir.mk
-include Drivers/BSP/Components/ST25R95/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := sml-230109
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
sml-230109.elf \

MAP_FILES += \
sml-230109.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
sml-230109.list \

OBJCOPY_HEX += \
sml-230109.hex \

OBJCOPY_BIN += \
sml-230109.bin \


# All Target
all: main-build

# Main-build Target
main-build: sml-230109.elf secondary-outputs

# Tool invocations
sml-230109.elf sml-230109.map: $(OBJS) $(USER_OBJS) C:\Users\daniel.e\Documents\Workspace_git\sml-001-fw\sml-230109\STM32U5A9VJTXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "sml-230109.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\Users\daniel.e\Documents\Workspace_git\sml-001-fw\sml-230109\STM32U5A9VJTXQ_FLASH.ld" -Wl,-Map="sml-230109.map" -Wl,--gc-sections -static -L"C:\Users\daniel.e\Documents\Workspace_git\sml-001-fw\sml-230109\Middlewares\ST\touchgfx\lib\core\cortex_m33\gcc" -L"C:\Users\daniel.e\Documents\Workspace_git\sml-001-fw\sml-230109\Middlewares\ST\touchgfx_components\gpu2d\NemaGFX\lib\core\cortex_m33\gcc" -L"C:\Users\daniel.e\Documents\Workspace_git\sml-001-fw\sml-230109\Middlewares\ST\touchgfx_components\gpu2d\TouchGFXNema\lib\cortex_m33\gcc" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

sml-230109.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "sml-230109.list"
	@echo 'Finished building: $@'
	@echo ' '

sml-230109.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "sml-230109.hex"
	@echo 'Finished building: $@'
	@echo ' '

sml-230109.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "sml-230109.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout sml-230109.bin sml-230109.elf sml-230109.hex sml-230109.list sml-230109.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
