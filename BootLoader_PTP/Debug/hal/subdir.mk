################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/flash.c \
../hal/hal.c 

C_DEPS += \
./hal/flash.d \
./hal/hal.d 

OBJS += \
./hal/flash.o \
./hal/hal.o 


# Each subdirectory must supply rules for building sources it contributes
hal/%.o: ../hal/%.c hal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\drivers" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\hal" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\middle\Srec" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\middle\Queue" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\middle" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\app" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\source" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\device" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-hal

clean-hal:
	-$(RM) ./hal/flash.d ./hal/flash.o ./hal/hal.d ./hal/hal.o

.PHONY: clean-hal

