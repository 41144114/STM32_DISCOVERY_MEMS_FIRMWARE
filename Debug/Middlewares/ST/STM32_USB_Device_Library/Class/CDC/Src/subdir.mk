################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDEBUG -DSTM32F30 -DSTM32F3 -DSTM32F303VCTx -DSTM32 -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Users/student/workspace/test2/inc" -I"C:/Users/student/workspace/test2/CMSIS/core" -I"C:/Users/student/workspace/test2/CMSIS/device" -I"C:/Users/student/workspace/test2/HAL_Driver/Inc/Legacy" -I"C:/Users/student/workspace/test2/HAL_Driver/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/Template/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


