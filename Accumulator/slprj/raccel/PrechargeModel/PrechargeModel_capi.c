#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "PrechargeModel_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "PrechargeModel.h"
#include "PrechargeModel_capi.h"
#include "PrechargeModel_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"PrechargeModel/HV+  Control Switch" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 0 } , { 1 , 0 , TARGET_STRING ( "PrechargeModel/HV- Control Switch" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 2 , 0 , TARGET_STRING (
"PrechargeModel/Solver Configuration/EVAL_KEY/INPUT_1_1_1" ) , TARGET_STRING
( "" ) , 0 , 0 , 1 , 0 , 1 } , { 3 , 0 , TARGET_STRING (
"PrechargeModel/Solver Configuration/EVAL_KEY/INPUT_2_1_1" ) , TARGET_STRING
( "" ) , 0 , 0 , 1 , 0 , 1 } , { 4 , 0 , TARGET_STRING (
"PrechargeModel/Solver Configuration/EVAL_KEY/INPUT_3_1_1" ) , TARGET_STRING
( "" ) , 0 , 0 , 1 , 0 , 1 } , { 5 , 0 , TARGET_STRING (
"PrechargeModel/Solver Configuration/EVAL_KEY/OUTPUT_1_0" ) , TARGET_STRING (
"" ) , 0 , 0 , 2 , 0 , 1 } , { 6 , 0 , TARGET_STRING (
"PrechargeModel/Solver Configuration/EVAL_KEY/STATE_1" ) , TARGET_STRING ( ""
) , 0 , 0 , 3 , 0 , 1 } , { 7 , 0 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/Math Function" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/Selector" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 9 , 0 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/Switch" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 10 ,
TARGET_STRING ( "PrechargeModel/Stair Generator" ) , TARGET_STRING (
"TimeInput" ) , 0 , 4 , 0 } , { 11 , TARGET_STRING (
"PrechargeModel/Stair Generator" ) , TARGET_STRING ( "RepeatPattern" ) , 0 ,
0 , 0 } , { 12 , TARGET_STRING ( "PrechargeModel/HV+  Control Switch" ) ,
TARGET_STRING ( "Time" ) , 0 , 0 , 0 } , { 13 , TARGET_STRING (
"PrechargeModel/HV+  Control Switch" ) , TARGET_STRING ( "Before" ) , 0 , 0 ,
0 } , { 14 , TARGET_STRING ( "PrechargeModel/HV+  Control Switch" ) ,
TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 15 , TARGET_STRING (
"PrechargeModel/HV- Control Switch" ) , TARGET_STRING ( "Time" ) , 0 , 0 , 0
} , { 16 , TARGET_STRING ( "PrechargeModel/HV- Control Switch" ) ,
TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 17 , TARGET_STRING (
"PrechargeModel/HV- Control Switch" ) , TARGET_STRING ( "After" ) , 0 , 0 , 0
} , { 18 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/Constant1" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 19 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/Output" ) , TARGET_STRING (
"Value" ) , 0 , 5 , 0 } , { 20 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/Switch" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 21 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Index" )
, TARGET_STRING ( "InitialOutput" ) , 1 , 0 , 0 } , { 22 , TARGET_STRING (
 "PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Detect Fall Nonpositive"
) , TARGET_STRING ( "vinit" ) , 2 , 0 , 0 } , { 23 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Constant1"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 24 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Constant2"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 25 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Constant3"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 26 , TARGET_STRING (
"PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Switch1"
) , TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING (
 "PrechargeModel/Stair Generator/Continuous/While Iterator Subsystem/Detect Fall Nonpositive/Nonpositive/Constant"
) , TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 ,
0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 ,
( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0 , ( NULL ) , 0 , 0 , 0
} } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . pjlmc1lzp1 , & rtB . nrxejncqrw ,
& rtB . p15kjgtpsv [ 0 ] , & rtB . asepqqecqj [ 0 ] , & rtB . ifpoliolwo [ 0
] , & rtB . l5aisodevg [ 0 ] , & rtB . gd1k0xmto2 [ 0 ] , & rtB . bqza00cyqn
, & rtB . h5s12bgqxk , & rtB . nxlv1serga , & rtP . StairGenerator_TimeInput
[ 0 ] , & rtP . StairGenerator_RepeatPattern , & rtP . HVControlSwitch_Time ,
& rtP . HVControlSwitch_Y0 , & rtP . HVControlSwitch_YFinal , & rtP .
HVControlSwitch_Time_d3xzd30hb0 , & rtP . HVControlSwitch_Y0_hwjg3kkkyh , &
rtP . HVControlSwitch_YFinal_mmqozp25oj , & rtP . Constant1_Value , & rtP .
Output_Value [ 0 ] , & rtP . Switch_Threshold , & rtP . Index_Y0 , & rtP .
DetectFallNonpositive_vinit , & rtP . Constant1_Value_dujvdtfujh , & rtP .
Constant2_Value , & rtP . Constant3_Value , & rtP . Switch1_Threshold , & rtP
. Constant_Value , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } ,
{ "signed char" , "int8_T" , 0 , 0 , sizeof ( int8_T ) , ( uint8_T ) SS_INT8
, 0 , 0 , 0 } , { "unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T
) , ( uint8_T ) SS_BOOLEAN , 0 , 0 , 0 } , { "unsigned char" , "uint8_T" , 0
, 0 , sizeof ( uint8_T ) , ( uint8_T ) SS_UINT8 , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_VECTOR , 8 , 2 , 0 } , { rtwCAPI_VECTOR , 10 , 2 , 0 } } ; static
const uint_T rtDimensionArray [ ] = { 1 , 1 , 4 , 1 , 2 , 1 , 14 , 1 , 1 , 4
, 1 , 5 } ; static const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0 } ;
static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , (
int8_T ) 1 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 0 ]
, ( const void * ) & rtcapiStoredFloats [ 0 ] , ( int8_T ) 0 , ( uint8_T ) 0
} } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals ,
10 , rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 18 ,
rtModelParameters , 0 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 3405627555U , 861820321U , 3847794471U , 3409354729U } , ( NULL ) , 0 , (
boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * PrechargeModel_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void PrechargeModel_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void PrechargeModel_host_InitializeDataMapInfo (
PrechargeModel_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
