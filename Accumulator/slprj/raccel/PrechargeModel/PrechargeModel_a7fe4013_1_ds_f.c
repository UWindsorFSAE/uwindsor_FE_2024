#include "ne_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_sys_struct.h"
#include "PrechargeModel_a7fe4013_1_ds_f.h"
#include "PrechargeModel_a7fe4013_1_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_externals.h"
#include "PrechargeModel_a7fe4013_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T PrechargeModel_a7fe4013_1_ds_f ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t4 , NeDsMethodOutput * out ) { real_T
HV_Main_Contactor0_v ; real_T HV_Main_Contactor1_p_v ; real_T
Pre_Charge_Contactor_i ; real_T t1 ; t1 = ( ( t4 -> mX . mX [ 3ULL ] * -
0.0005 + t4 -> mX . mX [ 4ULL ] * 0.0005 ) + t4 -> mX . mX [ 2ULL ] * 1.0005
) + 0.3 ; HV_Main_Contactor0_v = ( - t4 -> mX . mX [ 2ULL ] + t4 -> mX . mX [
3ULL ] ) - 600.0 ; HV_Main_Contactor1_p_v = ( - t4 -> mX . mX [ 0ULL ] + t4
-> mX . mX [ 2ULL ] * 1.0E-6 ) + t4 -> mX . mX [ 3ULL ] ;
Pre_Charge_Contactor_i = ( ( t4 -> mX . mX [ 3ULL ] * 0.0005 + t4 -> mX . mX
[ 4ULL ] * - 0.0005 ) + t4 -> mX . mX [ 2ULL ] * - 0.0005 ) - 0.3 ; if ( t4
-> mM . mX [ 0ULL ] != 0 ) { out -> mF . mX [ 2ULL ] = HV_Main_Contactor0_v -
t1 * 0.01 ; } else { out -> mF . mX [ 2ULL ] = HV_Main_Contactor0_v * 1.0E-8
- t1 ; } if ( t4 -> mM . mX [ 1ULL ] != 0 ) { out -> mF . mX [ 3ULL ] =
HV_Main_Contactor1_p_v - - t4 -> mX . mX [ 2ULL ] * 0.01 ; } else { out -> mF
. mX [ 3ULL ] = HV_Main_Contactor1_p_v * 1.0E-8 - ( - t4 -> mX . mX [ 2ULL ]
) ; } if ( t4 -> mM . mX [ 2ULL ] != 0 ) { out -> mF . mX [ 4ULL ] = t4 -> mX
. mX [ 4ULL ] - Pre_Charge_Contactor_i * 0.01 ; } else { out -> mF . mX [
4ULL ] = t4 -> mX . mX [ 4ULL ] * 1.0E-8 - Pre_Charge_Contactor_i ; } out ->
mF . mX [ 0ULL ] = - 0.0 ; out -> mF . mX [ 1ULL ] = - 0.0 ; ( void ) sys ; (
void ) out ; return 0 ; }
