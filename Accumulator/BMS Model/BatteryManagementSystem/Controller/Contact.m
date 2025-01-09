classdef Contact < Simulink.IntEnumType
  enumeration
    Init(0)
    Open(1)
    Close(2)
	Fault(3)
  end
  methods (Static)
    function retVal = getDefaultValue()
      retVal = Contact.Init;
    end
  end
end 