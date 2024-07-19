################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_lpuart.c 

C_DEPS += \
./component/uart/fsl_adapter_lpuart.d 

OBJS += \
./component/uart/fsl_adapter_lpuart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\drivers" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\hal" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\middle\Srec" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\middle\Queue" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\middle" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\app" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\source" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\component\lists" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\component\uart" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\component\serial_manager" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\device" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_Mock_MCU\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_lpuart.d ./component/uart/fsl_adapter_lpuart.o

.PHONY: clean-component-2f-uart

