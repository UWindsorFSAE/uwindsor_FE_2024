#include "ne_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_sys_struct.h"
#include "PrechargeModel_a7fe4013_1_ds_obs_act.h"
#include "PrechargeModel_a7fe4013_1_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_externals.h"
#include "PrechargeModel_a7fe4013_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T PrechargeModel_a7fe4013_1_ds_obs_act ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t2 , NeDsMethodOutput * out ) { real_T
HV_Main_Contactor1_p_v ; real_T Pre_Charge_Contactor_p_v ; real_T
Voltage_Sensor_V ; real_T piece3 ; out -> mOBS_ACT . mX [ 43ULL ] = 298.15 ;
out -> mOBS_ACT . mX [ 9ULL ] = ( - t2 -> mX . mX [ 2ULL ] + t2 -> mX . mX [
3ULL ] ) - 600.0 ; HV_Main_Contactor1_p_v = ( - t2 -> mX . mX [ 0ULL ] + t2
-> mX . mX [ 2ULL ] * 1.0E-6 ) + t2 -> mX . mX [ 3ULL ] ;
Pre_Charge_Contactor_p_v = ( t2 -> mX . mX [ 2ULL ] + t2 -> mX . mX [ 4ULL ]
) + 600.0 ; out -> mOBS_ACT . mX [ 35ULL ] = t2 -> mX . mX [ 2ULL ] * -
1.0E-6 + t2 -> mX . mX [ 0ULL ] ; Voltage_Sensor_V = t2 -> mX . mX [ 3ULL ] -
HV_Main_Contactor1_p_v ; piece3 = ( t2 -> mX . mX [ 3ULL ] * 0.0005 + t2 ->
mX . mX [ 4ULL ] * - 0.0005 ) + t2 -> mX . mX [ 2ULL ] * - 0.0005 ; out ->
mOBS_ACT . mX [ 0ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mOBS_ACT . mX [
1ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mOBS_ACT . mX [ 2ULL ] = t2 -> mX
. mX [ 3ULL ] ; out -> mOBS_ACT . mX [ 3ULL ] = t2 -> mX . mX [ 3ULL ] ; out
-> mOBS_ACT . mX [ 4ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mOBS_ACT . mX [
5ULL ] = 0.0 ; out -> mOBS_ACT . mX [ 6ULL ] = 0.3 + ( ( t2 -> mX . mX [ 3ULL
] * - 0.0005 + t2 -> mX . mX [ 4ULL ] * 0.0005 ) + t2 -> mX . mX [ 2ULL ] *
1.0005 ) ; out -> mOBS_ACT . mX [ 7ULL ] = t2 -> mX . mX [ 2ULL ] + 600.0 ;
out -> mOBS_ACT . mX [ 8ULL ] = t2 -> mX . mX [ 3ULL ] ; out -> mOBS_ACT . mX
[ 10ULL ] = t2 -> mU . mX [ 0ULL ] ; out -> mOBS_ACT . mX [ 11ULL ] = - t2 ->
mX . mX [ 2ULL ] ; out -> mOBS_ACT . mX [ 12ULL ] = 0.0 ; out -> mOBS_ACT .
mX [ 13ULL ] = HV_Main_Contactor1_p_v ; out -> mOBS_ACT . mX [ 14ULL ] =
HV_Main_Contactor1_p_v ; out -> mOBS_ACT . mX [ 15ULL ] = t2 -> mU . mX [
1ULL ] ; out -> mOBS_ACT . mX [ 16ULL ] = - 0.3 + piece3 ; out -> mOBS_ACT .
mX [ 17ULL ] = t2 -> mX . mX [ 2ULL ] + 600.0 ; out -> mOBS_ACT . mX [ 18ULL
] = Pre_Charge_Contactor_p_v ; out -> mOBS_ACT . mX [ 19ULL ] = t2 -> mX . mX
[ 4ULL ] ; out -> mOBS_ACT . mX [ 20ULL ] = t2 -> mU . mX [ 2ULL ] ; out ->
mOBS_ACT . mX [ 21ULL ] = 0.0 ; out -> mOBS_ACT . mX [ 22ULL ] = t2 -> mD .
mX [ 0ULL ] ; out -> mOBS_ACT . mX [ 23ULL ] = t2 -> mX . mX [ 3ULL ] ; out
-> mOBS_ACT . mX [ 24ULL ] = Pre_Charge_Contactor_p_v ; out -> mOBS_ACT . mX
[ 25ULL ] = 0.3 - piece3 ; out -> mOBS_ACT . mX [ 26ULL ] = t2 -> mX . mX [
3ULL ] ; out -> mOBS_ACT . mX [ 27ULL ] = Pre_Charge_Contactor_p_v ; out ->
mOBS_ACT . mX [ 28ULL ] = ( ( ( t2 -> mX . mX [ 3ULL ] * 0.0005 + t2 -> mX .
mX [ 4ULL ] * - 0.0005 ) + t2 -> mX . mX [ 2ULL ] * - 0.0005 ) - 0.3 ) * -
2000.0 ; out -> mOBS_ACT . mX [ 29ULL ] = t2 -> mU . mX [ 0ULL ] ; out ->
mOBS_ACT . mX [ 30ULL ] = t2 -> mU . mX [ 1ULL ] ; out -> mOBS_ACT . mX [
31ULL ] = t2 -> mU . mX [ 2ULL ] ; out -> mOBS_ACT . mX [ 32ULL ] = - t2 ->
mX . mX [ 2ULL ] ; out -> mOBS_ACT . mX [ 33ULL ] = HV_Main_Contactor1_p_v ;
out -> mOBS_ACT . mX [ 34ULL ] = t2 -> mX . mX [ 3ULL ] ; out -> mOBS_ACT .
mX [ 36ULL ] = t2 -> mX . mX [ 0ULL ] ; out -> mOBS_ACT . mX [ 37ULL ] =
Voltage_Sensor_V ; out -> mOBS_ACT . mX [ 38ULL ] = HV_Main_Contactor1_p_v ;
out -> mOBS_ACT . mX [ 39ULL ] = t2 -> mX . mX [ 3ULL ] ; out -> mOBS_ACT .
mX [ 40ULL ] = Voltage_Sensor_V ; out -> mOBS_ACT . mX [ 41ULL ] = 0.0 ; out
-> mOBS_ACT . mX [ 42ULL ] = 0.0 ; out -> mOBS_ACT . mX [ 44ULL ] = t2 -> mX
. mX [ 2ULL ] ; out -> mOBS_ACT . mX [ 45ULL ] = t2 -> mX . mX [ 1ULL ] *
0.00027777777777777778 ; out -> mOBS_ACT . mX [ 46ULL ] = 0.0 ; out ->
mOBS_ACT . mX [ 47ULL ] = t2 -> mX . mX [ 2ULL ] + 600.0 ; out -> mOBS_ACT .
mX [ 48ULL ] = 0.0 ; out -> mOBS_ACT . mX [ 49ULL ] = 0.0 ; out -> mOBS_ACT .
mX [ 50ULL ] = 0.0 ; out -> mOBS_ACT . mX [ 51ULL ] = 0.0 ; out -> mOBS_ACT .
mX [ 52ULL ] = 0.0 ; out -> mOBS_ACT . mX [ 53ULL ] = t2 -> mX . mX [ 1ULL ]
; out -> mOBS_ACT . mX [ 54ULL ] = t2 -> mX . mX [ 2ULL ] + 600.0 ; ( void )
sys ; ( void ) out ; return 0 ; }
