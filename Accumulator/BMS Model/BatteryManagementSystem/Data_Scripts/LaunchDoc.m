ePrj = exist('proj','var');
if ~ePrj>0
    proj = simulinkproject;
end

clear ePrj;

%builddocsearchdb(fullfile(proj.RootFolder,'Doc','HTML'))
web(fullfile(docroot, '3ptoolbox/designandtestbatterymanagementsystem/doc/BMS.html'));