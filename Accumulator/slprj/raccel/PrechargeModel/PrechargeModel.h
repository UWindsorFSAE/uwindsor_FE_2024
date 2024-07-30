#ifndef PrechargeModel_h_
#define PrechargeModel_h_
#ifndef PrechargeModel_COMMON_INCLUDES_
#define PrechargeModel_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "dt_info.h"
#include "ext_work.h"
#include "nesl_rtw.h"
#include "PrechargeModel_a7fe4013_1_gateway.h"
#endif
#include "PrechargeModel_types.h"
#include <string.h>
#include "rt_zcfcnRefine.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "zero_crossing_types.h"
#define MODEL_NAME PrechargeModel
#define NSAMPLE_TIMES (3) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (11) 
#define NUM_ZC_EVENTS (3) 
#ifndef NCSTATES
#define NCSTATES (2)   
#elif NCSTATES != 2
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T pjlmc1lzp1 ; real_T nrxejncqrw ; real_T asepqqecqj [
4 ] ; real_T ifpoliolwo [ 4 ] ; real_T nxlv1serga ; real_T bqza00cyqn ;
real_T h5s12bgqxk ; real_T p15kjgtpsv [ 4 ] ; real_T gd1k0xmto2 [ 14 ] ;
real_T l5aisodevg [ 2 ] ; } B ; typedef struct { real_T aaswsr1rcu [ 2 ] ;
real_T argz0f5dqi [ 2 ] ; real_T fnx34i5x5n [ 2 ] ; real_T gdnhhqi5jl [ 9 ] ;
real_T pan5gcvylw [ 3 ] ; real_T k4lrp1mqqo ; real_T na4n4iguxp ; void *
hbvvke1n10 ; void * gelipinn1a ; void * cxiazli5ii ; void * o2kfwlvfww ; void
* ckagq2xb0w ; void * pfon4t4jjl ; void * elb0r4kd24 ; void * pr5kzcttse ;
void * dw0srzoblx ; void * c5twv3sylm ; struct { void * LoggedData [ 2 ] ; }
nq5hownsx1 ; int_T i0ge3te0zu [ 3 ] ; int_T otllr3ihnw ; int_T l0224yqaan ;
int_T oou11isfot ; boolean_T nfwbh1ti3i ; uint8_T lwu0ota2wt [ 3 ] ; uint8_T
g0rbolrycs [ 3 ] ; uint8_T kkgrjivyjr ; uint8_T bg0p5tdgxq ; boolean_T
dmyikon5da [ 4 ] ; boolean_T ekhogeqn0r ; boolean_T ccsx3v14fa ; } DW ;
typedef struct { real_T mmg5234zf5 [ 2 ] ; } X ; typedef struct { real_T
mmg5234zf5 [ 2 ] ; } XDot ; typedef struct { boolean_T mmg5234zf5 [ 2 ] ; }
XDis ; typedef struct { real_T mmg5234zf5 [ 2 ] ; } CStateAbsTol ; typedef
struct { real_T mmg5234zf5 [ 2 ] ; } CXPtMin ; typedef struct { real_T
mmg5234zf5 [ 2 ] ; } CXPtMax ; typedef struct { real_T n0mgwbn0co ; real_T
px5q0ifs0m ; real_T gblnr0iypr [ 4 ] ; real_T oo4l2j13md ; real_T nyjb1zn1oe
; real_T pmzyjoruoa ; } ZCV ; typedef struct { ZCSigState jdg42luxap ;
ZCSigState iiggpa4ztk ; ZCSigState jggsb5cnar ; } PrevZCX ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T
StairGenerator_RepeatPattern ; real_T StairGenerator_TimeInput [ 4 ] ;
boolean_T DetectFallNonpositive_vinit ; real_T Switch1_Threshold ; real_T
HVControlSwitch_Time ; real_T HVControlSwitch_Y0 ; real_T
HVControlSwitch_YFinal ; real_T HVControlSwitch_Time_d3xzd30hb0 ; real_T
HVControlSwitch_Y0_hwjg3kkkyh ; real_T HVControlSwitch_YFinal_mmqozp25oj ;
real_T Output_Value [ 5 ] ; real_T Constant1_Value ; real_T Switch_Threshold
; int8_T Index_Y0 ; int8_T Constant1_Value_dujvdtfujh ; int8_T
Constant2_Value ; int8_T Constant3_Value ; uint8_T Constant_Value ; } ;
extern const char_T * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X
rtX ; extern DW rtDW ; extern PrevZCX rtPrevZCX ; extern P rtP ; extern
mxArray * mr_PrechargeModel_GetDWork ( ) ; extern void
mr_PrechargeModel_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_PrechargeModel_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * PrechargeModel_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ;
extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs (
int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T tid ) ; void
MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
