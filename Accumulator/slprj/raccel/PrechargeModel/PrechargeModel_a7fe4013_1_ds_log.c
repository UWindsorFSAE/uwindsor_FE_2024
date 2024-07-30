#include "ne_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_sys_struct.h"
#include "PrechargeModel_a7fe4013_1_ds_log.h"
#include "PrechargeModel_a7fe4013_1_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_externals.h"
#include "PrechargeModel_a7fe4013_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T PrechargeModel_a7fe4013_1_ds_log ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t2 , NeDsMethodOutput * out ) { real_T
HV_Main_Contactor0_v ; real_T HV_Main_Contactor1_p_v ; real_T
Pre_Charge_Contactor_i ; real_T Pre_Charge_Contactor_p_v ; real_T
Voltage_Sensor_V ; real_T piece3 ; HV_Main_Contactor0_v = ( - t2 -> mX . mX [
2ULL ] + t2 -> mX . mX [ 3ULL ] ) - 600.0 ; out -> mLOG . mX [ 9ULL ] = ( ( (
t2 -> mX . mX [ 3ULL ] * - 0.0005 + t2 -> mX . mX [ 4ULL ] * 0.0005 ) + t2 ->
mX . mX [ 2ULL ] * 1.0005 ) + 0.3 ) * HV_Main_Contactor0_v ;
HV_Main_Contactor1_p_v = ( - t2 -> mX . mX [ 0ULL ] + t2 -> mX . mX [ 2ULL ]
* 1.0E-6 ) + t2 -> mX . mX [ 3ULL ] ; out -> mLOG . mX [ 14ULL ] = - t2 -> mX
. mX [ 2ULL ] * HV_Main_Contactor1_p_v ; Pre_Charge_Contactor_i = ( ( t2 ->
mX . mX [ 3ULL ] * 0.0005 + t2 -> mX . mX [ 4ULL ] * - 0.0005 ) + t2 -> mX .
mX [ 2ULL ] * - 0.0005 ) - 0.3 ; Pre_Charge_Contactor_p_v = ( t2 -> mX . mX [
2ULL ] + t2 -> mX . mX [ 4ULL ] ) + 600.0 ; out -> mLOG . mX [ 20ULL ] =
Pre_Charge_Contactor_i * t2 -> mX . mX [ 4ULL ] ; out -> mLOG . mX [ 29ULL ]
= Pre_Charge_Contactor_i * Pre_Charge_Contactor_i * 2000.0 ; out -> mLOG . mX
[ 38ULL ] = - t2 -> mX . mX [ 2ULL ] * - t2 -> mX . mX [ 2ULL ] * 1.0E-9 ;
out -> mLOG . mX [ 36ULL ] = t2 -> mX . mX [ 2ULL ] * - 1.0E-6 + t2 -> mX .
mX [ 0ULL ] ; Voltage_Sensor_V = t2 -> mX . mX [ 3ULL ] -
HV_Main_Contactor1_p_v ; out -> mLOG . mX [ 46ULL ] = t2 -> mX . mX [ 2ULL ]
* t2 -> mX . mX [ 2ULL ] * 0.001 ; piece3 = ( t2 -> mX . mX [ 3ULL ] * 0.0005
+ t2 -> mX . mX [ 4ULL ] * - 0.0005 ) + t2 -> mX . mX [ 2ULL ] * - 0.0005 ;
out -> mLOG . mX [ 0ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mLOG . mX [
1ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mLOG . mX [ 2ULL ] = t2 -> mX . mX
[ 3ULL ] ; out -> mLOG . mX [ 3ULL ] = t2 -> mX . mX [ 3ULL ] ; out -> mLOG .
mX [ 4ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mLOG . mX [ 5ULL ] = 0.3 + (
( t2 -> mX . mX [ 3ULL ] * - 0.0005 + t2 -> mX . mX [ 4ULL ] * 0.0005 ) + t2
-> mX . mX [ 2ULL ] * 1.0005 ) ; out -> mLOG . mX [ 6ULL ] = t2 -> mX . mX [
2ULL ] + 600.0 ; out -> mLOG . mX [ 7ULL ] = t2 -> mX . mX [ 3ULL ] ; out ->
mLOG . mX [ 8ULL ] = HV_Main_Contactor0_v ; out -> mLOG . mX [ 10ULL ] = t2
-> mU . mX [ 0ULL ] ; out -> mLOG . mX [ 11ULL ] = - t2 -> mX . mX [ 2ULL ] ;
out -> mLOG . mX [ 12ULL ] = HV_Main_Contactor1_p_v ; out -> mLOG . mX [
13ULL ] = HV_Main_Contactor1_p_v ; out -> mLOG . mX [ 15ULL ] = t2 -> mU . mX
[ 1ULL ] ; out -> mLOG . mX [ 16ULL ] = - 0.3 + piece3 ; out -> mLOG . mX [
17ULL ] = t2 -> mX . mX [ 2ULL ] + 600.0 ; out -> mLOG . mX [ 18ULL ] =
Pre_Charge_Contactor_p_v ; out -> mLOG . mX [ 19ULL ] = t2 -> mX . mX [ 4ULL
] ; out -> mLOG . mX [ 21ULL ] = t2 -> mU . mX [ 2ULL ] ; out -> mLOG . mX [
22ULL ] = t2 -> mD . mX [ 0ULL ] ; out -> mLOG . mX [ 23ULL ] = t2 -> mX . mX
[ 3ULL ] ; out -> mLOG . mX [ 24ULL ] = Pre_Charge_Contactor_p_v ; out ->
mLOG . mX [ 25ULL ] = 0.3 - piece3 ; out -> mLOG . mX [ 26ULL ] = t2 -> mX .
mX [ 3ULL ] ; out -> mLOG . mX [ 27ULL ] = Pre_Charge_Contactor_p_v ; out ->
mLOG . mX [ 28ULL ] = Pre_Charge_Contactor_i * - 2000.0 ; out -> mLOG . mX [
30ULL ] = t2 -> mU . mX [ 0ULL ] ; out -> mLOG . mX [ 31ULL ] = t2 -> mU . mX
[ 1ULL ] ; out -> mLOG . mX [ 32ULL ] = t2 -> mU . mX [ 2ULL ] ; out -> mLOG
. mX [ 33ULL ] = - t2 -> mX . mX [ 2ULL ] ; out -> mLOG . mX [ 34ULL ] =
HV_Main_Contactor1_p_v ; out -> mLOG . mX [ 35ULL ] = t2 -> mX . mX [ 3ULL ]
; out -> mLOG . mX [ 37ULL ] = t2 -> mX . mX [ 0ULL ] ; out -> mLOG . mX [
39ULL ] = Voltage_Sensor_V ; out -> mLOG . mX [ 40ULL ] =
HV_Main_Contactor1_p_v ; out -> mLOG . mX [ 41ULL ] = t2 -> mX . mX [ 3ULL ]
; out -> mLOG . mX [ 42ULL ] = Voltage_Sensor_V ; out -> mLOG . mX [ 43ULL ]
= t2 -> mX . mX [ 2ULL ] ; out -> mLOG . mX [ 44ULL ] = t2 -> mX . mX [ 1ULL
] * 0.00027777777777777778 ; out -> mLOG . mX [ 45ULL ] = t2 -> mX . mX [
2ULL ] + 600.0 ; out -> mLOG . mX [ 47ULL ] = t2 -> mX . mX [ 1ULL ] ; out ->
mLOG . mX [ 48ULL ] = t2 -> mX . mX [ 2ULL ] + 600.0 ; ( void ) sys ; ( void
) out ; return 0 ; }
