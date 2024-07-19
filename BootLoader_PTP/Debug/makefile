################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include source/subdir.mk
-include middle/Srec/subdir.mk
-include middle/Queue/subdir.mk
-include middle/subdir.mk
-include hal/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include app/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Pham_Thanh_Phong_MCU_Mock
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Pham_Thanh_Phong_MCU_Mock.axf

# Tool invocations
Pham_Thanh_Phong_MCU_Mock.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="Pham_Thanh_Phong_MCU_Mock.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m0plus -mthumb -T Pham_Thanh_Phong_MCU_Mock_Debug.ld -o "Pham_Thanh_Phong_MCU_Mock.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Pham_Thanh_Phong_MCU_Mock.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Pham_Thanh_Phong_MCU_Mock.axf"; # arm-none-eabi-objcopy -v -O binary "Pham_Thanh_Phong_MCU_Mock.axf" "Pham_Thanh_Phong_MCU_Mock.bin" ; # checksum -p MKE16Z64xxx4 -d "Pham_Thanh_Phong_MCU_Mock.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
