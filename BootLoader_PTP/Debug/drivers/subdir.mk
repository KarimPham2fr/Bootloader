################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/dri_adc.c \
../drivers/dri_clock.c \
../drivers/dri_gpio.c \
../drivers/dri_lpuart.c \
../drivers/lpuart.c 

C_DEPS += \
./drivers/dri_adc.d \
./drivers/dri_clock.d \
./drivers/dri_gpio.d \
./drivers/dri_lpuart.d \
./drivers/lpuart.d 

OBJS += \
./drivers/dri_adc.o \
./drivers/dri_clock.o \
./drivers/dri_gpio.o \
./drivers/dri_lpuart.o \
./drivers/lpuart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\drivers" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\hal" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\middle\Srec" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\middle\Queue" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\middle" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\app" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\source" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\device" -I"C:\NXP\MCUXpressoIDE_11.9.0_2144\Pham_Thanh_Phong_MCU_Mock\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/dri_adc.d ./drivers/dri_adc.o ./drivers/dri_clock.d ./drivers/dri_clock.o ./drivers/dri_gpio.d ./drivers/dri_gpio.o ./drivers/dri_lpuart.d ./drivers/dri_lpuart.o ./drivers/lpuart.d ./drivers/lpuart.o

.PHONY: clean-drivers

