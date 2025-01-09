%% Battery parameters

dd = Simulink.data.dictionary.open('Battery_1Pack_1RC.sldd');
dataSectionObj = getSection(dd,'Design Data');
myBattStruct = getValue(getEntry(dataSectionObj,'BatteryNN'));

%% ModuleType1
ModuleType1.SOC_vec = myBattStruct.SOC_vec; % Vector of state-of-charge values, SOC
ModuleType1.T_vec = myBattStruct.T_vec; % Vector of temperatures, T, K
ModuleType1.V0_mat = myBattStruct.V0_mat; % Open-circuit voltage, V0(SOC,T), V
ModuleType1.V_range = [0, inf]; % Terminal voltage operating range [Min Max], V
ModuleType1.R0_mat = myBattStruct.R0_mat; % Terminal resistance, R0(SOC,T), Ohm
ModuleType1.AH = myBattStruct.AH; % Cell capacity, AH, A*hr
ModuleType1.thermal_mass = 45; % Thermal mass, J/K
ModuleType1.CellBalancingClosedResistance = 0.01; % Cell balancing switch closed resistance, Ohm
ModuleType1.CellBalancingOpenConductance = 1e-8; % Cell balancing switch open conductance, 1/Ohm
ModuleType1.CellBalancingThreshold = 0.5; % Cell balancing switch operation threshold
ModuleType1.CellBalancingResistance = 10; % Cell balancing shunt resistance, Ohm

%% ParallelAssemblyType1
ParallelAssemblyType1.SOC_vec = myBattStruct.SOC_vec; % Vector of state-of-charge values, SOC
ParallelAssemblyType1.T_vec = myBattStruct.T_vec; % Vector of temperatures, T, K
ParallelAssemblyType1.V0_mat = myBattStruct.V0_mat; % Open-circuit voltage, V0(SOC,T), V
ParallelAssemblyType1.V_range = [0, inf]; % Terminal voltage operating range [Min Max], V
ParallelAssemblyType1.R0_mat = myBattStruct.R0_mat; % Terminal resistance, R0(SOC,T), Ohm
ParallelAssemblyType1.AH = myBattStruct.AH; % Cell capacity, AH, A*hr
ParallelAssemblyType1.thermal_mass = 45; % Thermal mass, J/K
ParallelAssemblyType1.CellBalancingClosedResistance = 0.01; % Cell balancing switch closed resistance, Ohm
ParallelAssemblyType1.CellBalancingOpenConductance = 1e-8; % Cell balancing switch open conductance, 1/Ohm
ParallelAssemblyType1.CellBalancingThreshold = 0.5; % Cell balancing switch operation threshold
ParallelAssemblyType1.CellBalancingResistance = 10; % Cell balancing shunt resistance, Ohm

%% Battery initial targets

%% ModuleAssembly1.Module1
ModuleAssembly1.Module1.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly1.Module1.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly1.Module1.socCellModel = [0.98,0.98,0.985,0.99,0.99,1]'; % Cell model state of charge
ModuleAssembly1.Module1.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly1.Module1.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly1.Module1.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly1.Module1.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly1.Module2
ModuleAssembly1.Module2.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly1.Module2.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly1.Module2.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly1.Module2.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly1.Module2.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly1.Module2.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly1.Module2.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly1.Module3
ModuleAssembly1.Module3.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly1.Module3.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly1.Module3.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly1.Module3.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly1.Module3.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly1.Module3.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly1.Module3.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly1.Module4
ModuleAssembly1.Module4.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly1.Module4.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly1.Module4.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly1.Module4.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly1.Module4.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly1.Module4.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly1.Module4.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly2.Module1
ModuleAssembly2.Module1.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly2.Module1.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly2.Module1.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly2.Module1.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly2.Module1.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly2.Module1.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly2.Module1.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly2.Module2
ModuleAssembly2.Module2.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly2.Module2.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly2.Module2.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly2.Module2.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly2.Module2.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly2.Module2.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly2.Module2.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly2.Module3
ModuleAssembly2.Module3.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly2.Module3.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly2.Module3.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly2.Module3.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly2.Module3.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly2.Module3.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly2.Module3.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly2.Module4
ModuleAssembly2.Module4.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly2.Module4.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly2.Module4.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly2.Module4.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly2.Module4.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly2.Module4.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly2.Module4.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly3.Module1
ModuleAssembly3.Module1.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly3.Module1.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly3.Module1.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly3.Module1.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly3.Module1.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly3.Module1.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly3.Module1.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly3.Module2
ModuleAssembly3.Module2.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly3.Module2.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly3.Module2.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly3.Module2.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly3.Module2.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly3.Module2.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly3.Module2.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly3.Module3
ModuleAssembly3.Module3.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly3.Module3.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly3.Module3.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly3.Module3.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly3.Module3.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly3.Module3.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly3.Module3.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly3.Module4
ModuleAssembly3.Module4.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly3.Module4.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly3.Module4.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly3.Module4.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly3.Module4.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly3.Module4.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly3.Module4.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly4.Module1
ModuleAssembly4.Module1.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly4.Module1.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly4.Module1.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly4.Module1.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly4.Module1.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly4.Module1.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly4.Module1.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly4.Module2
ModuleAssembly4.Module2.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly4.Module2.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly4.Module2.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly4.Module2.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly4.Module2.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly4.Module2.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly4.Module2.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly4.Module3
ModuleAssembly4.Module3.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly4.Module3.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly4.Module3.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly4.Module3.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly4.Module3.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly4.Module3.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly4.Module3.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

%% ModuleAssembly4.Module4
ModuleAssembly4.Module4.iCellModel = repmat(0, 6, 1); % Cell model current (positive in), A
ModuleAssembly4.Module4.vCellModel = repmat(0, 6, 1); % Cell model terminal voltage, V
ModuleAssembly4.Module4.socCellModel = repmat(1, 6, 1); % Cell model state of charge
ModuleAssembly4.Module4.numCyclesCellModel = repmat(0, 6, 1); % Cell model discharge cycles
ModuleAssembly4.Module4.temperatureCellModel = repmat(298.15, 6, 1); % Cell model temperature, K
ModuleAssembly4.Module4.vParallelAssembly = repmat(0, 6, 1); % Parallel Assembly Voltage, V
ModuleAssembly4.Module4.socParallelAssembly = repmat(1, 6, 1); % Parallel Assembly state of charge

% Suppress MATLAB editor message regarding readability of repmat
%#ok<*REPMAT>
%% Clear Variables 
clear dd dataSectionObj myBattStruct;