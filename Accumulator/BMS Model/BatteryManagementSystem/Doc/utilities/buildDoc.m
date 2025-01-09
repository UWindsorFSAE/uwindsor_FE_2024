proj = simulinkproject;

fn = dir([proj.RootFolder,'\Doc\liveScripts\*.mlx']);
for ii = 1:length(fn)
    fileName = fn(ii).name;
    liveScriptName = [proj.RootFolder, '\Doc\liveScripts\', fileName];
    htmlName = [proj.RootFolder, '\Doc\HTML\' fileName(1:end-4) '.html'];
    if ~exist(htmlName,'file')
        matlab.internal.liveeditor.openAndConvert(liveScriptName,htmlName);
    end
end