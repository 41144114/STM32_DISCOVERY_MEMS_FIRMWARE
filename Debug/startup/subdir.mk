################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f303xc.s 

OBJS += \
./startup/startup_stm32f303xc.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"C:/Users/student/workspace/test2/inc" -I"C:/Users/student/workspace/test2/CMSIS/core" -I"C:/Users/student/workspace/test2/CMSIS/device" -I"C:/Users/student/workspace/test2/HAL_Driver/Inc/Legacy" -I"C:/Users/student/workspace/test2/HAL_Driver/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Class/Template/Inc" -I"C:/Users/student/workspace/test2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


