%%
load('BatNN.mat')
%%
% For SoC estimation piece
myDictionaryObj = ...
Simulink.data.dictionary.open('DD_SOC_Estimation.sldd');
dDataSectObj = getSection(myDictionaryObj,'Design Data');
addEntry(dDataSectObj,'BatteryNN',BatteryNN)
saveChanges(myDictionaryObj)

% For plant
myDictionaryObj = ...
Simulink.data.dictionary.open('Shared_DD.sldd');
dDataSectObj = getSection(myDictionaryObj,'Design Data');
addEntry(dDataSectObj,'BatteryNN',BatteryNN)
saveChanges(myDictionaryObj)