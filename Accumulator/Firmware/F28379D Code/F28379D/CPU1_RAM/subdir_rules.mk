################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D" --include_path="C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/device" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-60590529: ../main.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2011/ccs/utils/sysconfig_1.23.0/sysconfig_cli.bat" --script "C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/main.syscfg" -o "syscfg" -s "C:/ti/c2000/C2000Ware_5_04_00_00/.metadata/sdk.json" -d "F2837xD" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-60590529 ../main.syscfg
syscfg/board.h: build-60590529
syscfg/board.cmd.genlibs: build-60590529
syscfg/board.opt: build-60590529
syscfg/board.json: build-60590529
syscfg/pinmux.csv: build-60590529
syscfg/c2000ware_libraries.cmd.genlibs: build-60590529
syscfg/c2000ware_libraries.opt: build-60590529
syscfg/c2000ware_libraries.c: build-60590529
syscfg/c2000ware_libraries.h: build-60590529
syscfg/clocktree.h: build-60590529
syscfg: build-60590529

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D" --include_path="C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/device" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/jared/Documents/uwindsor_FE_2024/Accumulator/Firmware/F28379D Code/F28379D/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


