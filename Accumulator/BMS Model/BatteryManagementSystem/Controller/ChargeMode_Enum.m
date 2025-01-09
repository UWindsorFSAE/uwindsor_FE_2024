classdef ChargeMode_Enum < Simulink.IntEnumType
  enumeration
    ChrgStandby(0)
    CC(1)
    CV(2)
  end
  methods (Static)
    function retVal = getDefaultValue()
      retVal = ChargeMode_Enum.ChrgStandby;
    end
  end
end 