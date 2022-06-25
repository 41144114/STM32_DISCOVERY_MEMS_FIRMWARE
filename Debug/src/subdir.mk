################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/practicalFunctions.c \
../src/stm32f3xx_hal_msp.c \
../src/stm32f3xx_it.c \
../src/syscalls.c \
../src/system_stm32f3xx.c \
../src/usb_device.c \
../src/usbd_cdc_if.c \
../src/usbd_conf.c \
../src/usbd_desc.c 

OBJS += \
./src/main.o \
./src/practicalFunctions.o \
./src/stm32f3xx_hal_msp.o \
./src/stm32f3xx_it.o \
./src/syscalls.o \
./src/system_stm32f3xx.o \
./src/usb_device.o \
./src/usbd_cdc_if.o \
./src/usbd_conf.o \
./src/usbd_desc.o 

C_DEPS += \
./src/main.d \
./src/practicalFunctions.d \
./src/stm32f3xx_hal_msp.d \
./src/stm32f3xx_it.d \
./src/syscalls.d \
./src/system_stm32f3xx.d \
./src/usb_device.d \
./src/usbd_cdc_if.d \
./src/usbd_conf.d \
./src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDEBUG -DSTM32F30 -DSTM32F3 -DSTM32F303VCTx -DSTM32 -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Users/student/workspace/test2/inc" -I"C:/Users/student/workspace/test2/CMSIS/core" -I"C:/Users/student/workspace/test2/CMSIS/device" -I"C:/Users/student/workspace/test2/HAL_Driver/Inc/Legacy" -I"C:/Users/student/workspace/test2/HAL_Driver/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/Template/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


