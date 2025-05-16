################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/c2000_code_generation/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/Steven Fung/OneDrive - University of Windsor/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D" --include_path="C:/Users/Steven Fung/OneDrive - University of Windsor/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/device" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/c2000_code_generation/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="C:/Users/Steven Fung/OneDrive - University of Windsor/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/CPU1_RAM/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/c2000_code_generation/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/Steven Fung/OneDrive - University of Windsor/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D" --include_path="C:/Users/Steven Fung/OneDrive - University of Windsor/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/device" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/c2000_code_generation/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="C:/Users/Steven Fung/OneDrive - University of Windsor/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/CPU1_RAM/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


