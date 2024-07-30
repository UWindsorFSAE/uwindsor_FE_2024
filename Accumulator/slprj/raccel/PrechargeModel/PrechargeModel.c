#include "PrechargeModel.h"
#include "rtwtypes.h"
#include "mwmathutil.h"
#include <string.h>
#include <stddef.h>
#include "PrechargeModel_private.h"
#include "rt_logging_mmi.h"
#include "PrechargeModel_capi.h"
#include "PrechargeModel_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; extern ssExecutionInfo gblExecutionInfo ; RTWExtModeInfo *
gblRTWExtModeInfo = NULL ; void raccelForceExtModeShutdown ( boolean_T
extModeStartPktReceived ) { if ( ! extModeStartPktReceived ) { boolean_T
stopRequested = false ; rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 2 , &
stopRequested ) ; } rtExtModeShutdown ( 2 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_engine_exec.h"
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 3 ; const char_T
* gbl_raccel_Version = "24.1 (R2024a) 19-Nov-2023" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1 } ; const
char * raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const char *
inportFileName , int * matFileFormat ) { return rt_RAccelReadInportsMatFile (
S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_engine_exec.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; X rtX ; DW rtDW ; PrevZCX rtPrevZCX ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ; void MdlInitialize ( void ) { rtDW .
lwu0ota2wt [ 0 ] = 29U ; rtDW . lwu0ota2wt [ 1 ] = 29U ; rtDW . lwu0ota2wt [
2 ] = 29U ; rtDW . nfwbh1ti3i = rtP . DetectFallNonpositive_vinit ; } void
MdlStart ( void ) { CXPtMax * _rtXPerturbMax ; CXPtMin * _rtXPerturbMin ;
NeModelParameters modelParameters ; NeModelParameters modelParameters_p ;
NeslSimulationData * simulationData ; NeslSimulator * tmp ;
NeuDiagnosticManager * diagnosticManager ; NeuDiagnosticTree * diagnosticTree
; NeuDiagnosticTree * diagnosticTree_e ; NeuDiagnosticTree * diagnosticTree_p
; char * msg ; char * msg_e ; char * msg_p ; real_T tmp_m [ 12 ] ; real_T
time ; real_T tmp_e ; int32_T tmp_i ; int_T tmp_g [ 4 ] ; boolean_T tmp_p ;
boolean_T val ; { bool externalInputIsInDatasetFormat = false ; void *
pISigstreamManager = rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} _rtXPerturbMax = ( ( CXPtMax * ) ssGetJacobianPerturbationBoundsMaxVec (
rtS ) ) ; _rtXPerturbMin = ( ( CXPtMin * )
ssGetJacobianPerturbationBoundsMinVec ( rtS ) ) ; tmp = nesl_lease_simulator
( "PrechargeModel/Solver Configuration_1" , 0 , 0 ) ; rtDW . hbvvke1n10 = (
void * ) tmp ; tmp_p = pointer_is_null ( rtDW . hbvvke1n10 ) ; if ( tmp_p ) {
PrechargeModel_a7fe4013_1_gateway ( ) ; tmp = nesl_lease_simulator (
"PrechargeModel/Solver Configuration_1" , 0 , 0 ) ; rtDW . hbvvke1n10 = (
void * ) tmp ; } slsaSaveRawMemoryForSimTargetOP ( rtS ,
"PrechargeModel/Solver Configuration_100" , ( void * * ) ( & rtDW .
hbvvke1n10 ) , 0U * sizeof ( real_T ) , nesl_save_simdata ,
nesl_restore_simdata ) ; simulationData = nesl_create_simulation_data ( ) ;
rtDW . gelipinn1a = ( void * ) simulationData ; diagnosticManager =
rtw_create_diagnostics ( ) ; rtDW . cxiazli5ii = ( void * ) diagnosticManager
; modelParameters . mSolverType = NE_SOLVER_TYPE_DAE ; modelParameters .
mSolverAbsTol = 0.001 ; modelParameters . mSolverRelTol = 0.001 ;
modelParameters . mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_MAYBE ;
modelParameters . mStartTime = 0.0 ; modelParameters . mLoadInitialState =
false ; modelParameters . mUseSimState = false ; modelParameters .
mLinTrimCompile = false ; modelParameters . mLoggingMode = SSC_LOGGING_OFF ;
modelParameters . mRTWModifiedTimeStamp = 6.44267892E+8 ; modelParameters .
mZcDisabled = false ; modelParameters . mUseModelRefSolver = false ;
modelParameters . mTargetFPGAHIL = false ; tmp_e = 0.001 ; modelParameters .
mSolverTolerance = tmp_e ; tmp_e = 0.0 ; modelParameters . mFixedStepSize =
tmp_e ; tmp_p = true ; modelParameters . mVariableStepSolver = tmp_p ; tmp_p
= false ; modelParameters . mIsUsingODEN = tmp_p ; tmp_p =
slIsRapidAcceleratorSimulating ( ) ; val = ssGetGlobalInitialStatesAvailable
( rtS ) ; if ( tmp_p ) { val = ( val && ssIsFirstInitCond ( rtS ) ) ; }
modelParameters . mLoadInitialState = val ; modelParameters . mZcDisabled =
false ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW . cxiazli5ii ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = nesl_initialize_simulator ( ( NeslSimulator * ) rtDW . hbvvke1n10
, & modelParameters , diagnosticManager ) ; if ( tmp_i != 0 ) { tmp_p =
error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp_p ) { msg =
rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; } }
simulationData = ( NeslSimulationData * ) rtDW . gelipinn1a ; time = ssGetT (
rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time ; simulationData -> mData -> mContStates . mN = 2 ;
simulationData -> mData -> mContStates . mX = & rtX . mmg5234zf5 [ 0 ] ;
simulationData -> mData -> mDiscStates . mN = 9 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . gdnhhqi5jl [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
i0ge3te0zu [ 0 ] ; tmp_p = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo
( rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp_p ; simulationData -> mData -> mHadEvents = false ; simulationData ->
mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp_p = (
ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp_p ; tmp_p =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp_p ; tmp_p = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp_p ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp_p = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp_p ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_g [ 0 ] = 0 ;
tmp_m [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_m [ 1 ] = rtB . asepqqecqj [ 1 ] ;
tmp_m [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_m [ 3 ] = rtB . asepqqecqj [ 3 ] ;
tmp_g [ 1 ] = 4 ; tmp_m [ 4 ] = rtB . ifpoliolwo [ 0 ] ; tmp_m [ 5 ] = rtB .
ifpoliolwo [ 1 ] ; tmp_m [ 6 ] = rtB . ifpoliolwo [ 2 ] ; tmp_m [ 7 ] = rtB .
ifpoliolwo [ 3 ] ; tmp_g [ 2 ] = 8 ; tmp_m [ 8 ] = rtB . p15kjgtpsv [ 0 ] ;
tmp_m [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_m [ 10 ] = rtB . p15kjgtpsv [ 2 ]
; tmp_m [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_g [ 3 ] = 12 ; simulationData
-> mData -> mInputValues . mN = 12 ; simulationData -> mData -> mInputValues
. mX = & tmp_m [ 0 ] ; simulationData -> mData -> mInputOffsets . mN = 4 ;
simulationData -> mData -> mInputOffsets . mX = & tmp_g [ 0 ] ;
simulationData -> mData -> mNumjacDxLo . mN = 2 ; simulationData -> mData ->
mNumjacDxLo . mX = & _rtXPerturbMin -> mmg5234zf5 [ 0 ] ; simulationData ->
mData -> mNumjacDxHi . mN = 2 ; simulationData -> mData -> mNumjacDxHi . mX =
& _rtXPerturbMax -> mmg5234zf5 [ 0 ] ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . cxiazli5ii ; diagnosticTree_p =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
ne_simulator_method ( ( NeslSimulator * ) rtDW . hbvvke1n10 ,
NESL_SIM_NUMJAC_DX_BOUNDS , simulationData , diagnosticManager ) ; if ( tmp_i
!= 0 ) { tmp_p = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if (
tmp_p ) { msg_p = rtw_diagnostics_msg ( diagnosticTree_p ) ; ssSetErrorStatus
( rtS , msg_p ) ; } } tmp = nesl_lease_simulator (
"PrechargeModel/Solver Configuration_1" , 1 , 0 ) ; rtDW . pfon4t4jjl = (
void * ) tmp ; tmp_p = pointer_is_null ( rtDW . pfon4t4jjl ) ; if ( tmp_p ) {
PrechargeModel_a7fe4013_1_gateway ( ) ; tmp = nesl_lease_simulator (
"PrechargeModel/Solver Configuration_1" , 1 , 0 ) ; rtDW . pfon4t4jjl = (
void * ) tmp ; } slsaSaveRawMemoryForSimTargetOP ( rtS ,
"PrechargeModel/Solver Configuration_110" , ( void * * ) ( & rtDW .
pfon4t4jjl ) , 0U * sizeof ( real_T ) , nesl_save_simdata ,
nesl_restore_simdata ) ; simulationData = nesl_create_simulation_data ( ) ;
rtDW . elb0r4kd24 = ( void * ) simulationData ; diagnosticManager =
rtw_create_diagnostics ( ) ; rtDW . pr5kzcttse = ( void * ) diagnosticManager
; modelParameters_p . mSolverType = NE_SOLVER_TYPE_DAE ; modelParameters_p .
mSolverAbsTol = 0.001 ; modelParameters_p . mSolverRelTol = 0.001 ;
modelParameters_p . mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_MAYBE ;
modelParameters_p . mStartTime = 0.0 ; modelParameters_p . mLoadInitialState
= false ; modelParameters_p . mUseSimState = false ; modelParameters_p .
mLinTrimCompile = false ; modelParameters_p . mLoggingMode = SSC_LOGGING_OFF
; modelParameters_p . mRTWModifiedTimeStamp = 6.44267892E+8 ;
modelParameters_p . mZcDisabled = false ; modelParameters_p .
mUseModelRefSolver = false ; modelParameters_p . mTargetFPGAHIL = false ;
tmp_e = 0.001 ; modelParameters_p . mSolverTolerance = tmp_e ; tmp_e = 0.0 ;
modelParameters_p . mFixedStepSize = tmp_e ; tmp_p = true ; modelParameters_p
. mVariableStepSolver = tmp_p ; tmp_p = false ; modelParameters_p .
mIsUsingODEN = tmp_p ; tmp_p = slIsRapidAcceleratorSimulating ( ) ; val =
ssGetGlobalInitialStatesAvailable ( rtS ) ; if ( tmp_p ) { val = ( val &&
ssIsFirstInitCond ( rtS ) ) ; } modelParameters_p . mLoadInitialState = val ;
modelParameters_p . mZcDisabled = false ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . pr5kzcttse ; diagnosticTree_e =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
nesl_initialize_simulator ( ( NeslSimulator * ) rtDW . pfon4t4jjl , &
modelParameters_p , diagnosticManager ) ; if ( tmp_i != 0 ) { tmp_p =
error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp_p ) { msg_e =
rtw_diagnostics_msg ( diagnosticTree_e ) ; ssSetErrorStatus ( rtS , msg_e ) ;
} } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { NeslSimulationData
* simulationData ; NeuDiagnosticManager * diagnosticManager ;
NeuDiagnosticTree * diagnosticTree ; NeuDiagnosticTree * diagnosticTree_e ;
NeuDiagnosticTree * diagnosticTree_i ; NeuDiagnosticTree * diagnosticTree_p ;
ZCV * _rtZCSV ; char * msg ; char * msg_e ; char * msg_i ; char * msg_p ;
real_T tmp_f [ 26 ] ; real_T tmp [ 12 ] ; real_T tmp_g [ 12 ] ; real_T tmp_i
[ 12 ] ; real_T time ; real_T time_e ; real_T time_g ; real_T time_i ; real_T
time_m ; real_T time_p ; int32_T tmp_e ; int_T tmp_c [ 5 ] ; int_T tmp_j [ 4
] ; int_T tmp_m [ 4 ] ; int_T tmp_p [ 4 ] ; int8_T memasuedaj [ 4 ] ; int8_T
fdk4ps5zkb ; int8_T s15_iter ; boolean_T anz44mi22v ; boolean_T iw4wsgify2 ;
_rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . l0224yqaan = ( ssGetTaskTime ( rtS ,
1 ) >= rtP . HVControlSwitch_Time ) ; if ( rtDW . l0224yqaan == 1 ) { rtB .
pjlmc1lzp1 = rtP . HVControlSwitch_YFinal ; } else { rtB . pjlmc1lzp1 = rtP .
HVControlSwitch_Y0 ; } rtDW . oou11isfot = ( ssGetTaskTime ( rtS , 1 ) >= rtP
. HVControlSwitch_Time_d3xzd30hb0 ) ; if ( rtDW . oou11isfot == 1 ) { rtB .
nrxejncqrw = rtP . HVControlSwitch_YFinal_mmqozp25oj ; } else { rtB .
nrxejncqrw = rtP . HVControlSwitch_Y0_hwjg3kkkyh ; } } rtB . asepqqecqj [ 0 ]
= rtB . pjlmc1lzp1 ; rtB . asepqqecqj [ 1 ] = 0.0 ; rtB . asepqqecqj [ 2 ] =
0.0 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . aaswsr1rcu [ 0 ] = ! ( rtB .
asepqqecqj [ 0 ] == rtDW . aaswsr1rcu [ 1 ] ) ; rtDW . aaswsr1rcu [ 1 ] = rtB
. asepqqecqj [ 0 ] ; } rtB . asepqqecqj [ 0 ] = rtDW . aaswsr1rcu [ 1 ] ; rtB
. asepqqecqj [ 3 ] = rtDW . aaswsr1rcu [ 0 ] ; rtB . ifpoliolwo [ 0 ] = rtB .
nrxejncqrw ; rtB . ifpoliolwo [ 1 ] = 0.0 ; rtB . ifpoliolwo [ 2 ] = 0.0 ; if
( ssIsMajorTimeStep ( rtS ) ) { rtDW . argz0f5dqi [ 0 ] = ! ( rtB .
ifpoliolwo [ 0 ] == rtDW . argz0f5dqi [ 1 ] ) ; rtDW . argz0f5dqi [ 1 ] = rtB
. ifpoliolwo [ 0 ] ; } rtB . ifpoliolwo [ 0 ] = rtDW . argz0f5dqi [ 1 ] ; rtB
. ifpoliolwo [ 3 ] = rtDW . argz0f5dqi [ 0 ] ; if ( ssIsSampleHit ( rtS , 1 ,
0 ) ) { if ( rtP . StairGenerator_RepeatPattern > rtP . Switch_Threshold ) {
rtB . nxlv1serga = rtP . StairGenerator_TimeInput [ 3 ] ; } else { rtB .
nxlv1serga = rtP . Constant1_Value ; } } rtB . bqza00cyqn = muDoubleScalarMod
( ssGetT ( rtS ) , rtB . nxlv1serga ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) )
{ if ( ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . dmyikon5da [ 0 ] = ( rtB .
bqza00cyqn >= rtP . StairGenerator_TimeInput [ 0 ] ) ; rtDW . dmyikon5da [ 1
] = ( rtB . bqza00cyqn >= rtP . StairGenerator_TimeInput [ 1 ] ) ; rtDW .
dmyikon5da [ 2 ] = ( rtB . bqza00cyqn >= rtP . StairGenerator_TimeInput [ 2 ]
) ; rtDW . dmyikon5da [ 3 ] = ( rtB . bqza00cyqn >= rtP .
StairGenerator_TimeInput [ 3 ] ) ; } memasuedaj [ 0 ] = ( int8_T ) rtDW .
dmyikon5da [ 0 ] ; memasuedaj [ 1 ] = ( int8_T ) rtDW . dmyikon5da [ 1 ] ;
memasuedaj [ 2 ] = ( int8_T ) rtDW . dmyikon5da [ 2 ] ; memasuedaj [ 3 ] = (
int8_T ) rtDW . dmyikon5da [ 3 ] ; s15_iter = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . nfwbh1ti3i = rtP
. DetectFallNonpositive_vinit ; do { iw4wsgify2 = ( memasuedaj [ s15_iter - 1
] <= rtP . Constant_Value ) ; anz44mi22v = ( ( int32_T ) iw4wsgify2 > (
int32_T ) rtDW . nfwbh1ti3i ) ; if ( anz44mi22v ) { fdk4ps5zkb = ( int8_T ) (
s15_iter - rtP . Constant2_Value ) ; } else if ( rtB . bqza00cyqn >= rtP .
Switch1_Threshold ) { fdk4ps5zkb = rtP . Constant1_Value_dujvdtfujh ; } else
{ fdk4ps5zkb = rtP . Constant3_Value ; } rtDW . nfwbh1ti3i = iw4wsgify2 ;
s15_iter ++ ; } while ( ( ! anz44mi22v ) && ( s15_iter <= 4 ) ) ; rtB .
h5s12bgqxk = rtP . Output_Value [ fdk4ps5zkb ] ; } rtB . p15kjgtpsv [ 0 ] =
rtB . h5s12bgqxk ; rtB . p15kjgtpsv [ 1 ] = 0.0 ; rtB . p15kjgtpsv [ 2 ] =
0.0 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . fnx34i5x5n [ 0 ] = ! ( rtB .
p15kjgtpsv [ 0 ] == rtDW . fnx34i5x5n [ 1 ] ) ; rtDW . fnx34i5x5n [ 1 ] = rtB
. p15kjgtpsv [ 0 ] ; } rtB . p15kjgtpsv [ 0 ] = rtDW . fnx34i5x5n [ 1 ] ; rtB
. p15kjgtpsv [ 3 ] = rtDW . fnx34i5x5n [ 0 ] ; simulationData = (
NeslSimulationData * ) rtDW . gelipinn1a ; anz44mi22v = false ; if (
ssIsMajorTimeStep ( rtS ) ) { time = ssGetT ( rtS ) ; simulationData -> mData
-> mTime . mN = 1 ; simulationData -> mData -> mTime . mX = & time ;
simulationData -> mData -> mContStates . mN = 2 ; simulationData -> mData ->
mContStates . mX = & rtX . mmg5234zf5 [ 0 ] ; simulationData -> mData ->
mDiscStates . mN = 9 ; simulationData -> mData -> mDiscStates . mX = & rtDW .
gdnhhqi5jl [ 0 ] ; simulationData -> mData -> mModeVector . mN = 3 ;
simulationData -> mData -> mModeVector . mX = & rtDW . i0ge3te0zu [ 0 ] ;
iw4wsgify2 = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) ->
foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents = iw4wsgify2
; simulationData -> mData -> mHadEvents = false ; simulationData -> mData ->
mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; iw4wsgify2 = ( ssGetMdlInfoPtr
( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = iw4wsgify2 ; iw4wsgify2 = ssIsSolverCheckingCIC ( rtS
) ; simulationData -> mData -> mIsSolverCheckingCIC = iw4wsgify2 ; iw4wsgify2
= ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = iw4wsgify2 ; simulationData -> mData ->
mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; iw4wsgify2
= ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = iw4wsgify2 ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_p [ 0 ] = 0 ;
tmp [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp [ 1 ] = rtB . asepqqecqj [ 1 ] ; tmp
[ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp [ 3 ] = rtB . asepqqecqj [ 3 ] ; tmp_p [
1 ] = 4 ; tmp [ 4 ] = rtB . ifpoliolwo [ 0 ] ; tmp [ 5 ] = rtB . ifpoliolwo [
1 ] ; tmp [ 6 ] = rtB . ifpoliolwo [ 2 ] ; tmp [ 7 ] = rtB . ifpoliolwo [ 3 ]
; tmp_p [ 2 ] = 8 ; tmp [ 8 ] = rtB . p15kjgtpsv [ 0 ] ; tmp [ 9 ] = rtB .
p15kjgtpsv [ 1 ] ; tmp [ 10 ] = rtB . p15kjgtpsv [ 2 ] ; tmp [ 11 ] = rtB .
p15kjgtpsv [ 3 ] ; tmp_p [ 3 ] = 12 ; simulationData -> mData -> mInputValues
. mN = 12 ; simulationData -> mData -> mInputValues . mX = & tmp [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 4 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_p [ 0 ] ; simulationData -> mData ->
mNonSampledZCs . mN = 3 ; simulationData -> mData -> mNonSampledZCs . mX = &
_rtZCSV -> oo4l2j13md ; simulationData -> mData -> mNonSampledZCs . mN = 3 ;
simulationData -> mData -> mNonSampledZCs . mX = & rtDW . pan5gcvylw [ 0 ] ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . cxiazli5ii ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_e = ne_simulator_method ( ( NeslSimulator * ) rtDW . hbvvke1n10 ,
NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager ) ; if ( tmp_e !=
0 ) { iw4wsgify2 = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if (
iw4wsgify2 ) { msg = rtw_diagnostics_msg ( diagnosticTree ) ;
ssSetErrorStatus ( rtS , msg ) ; } } memcpy ( & rtDW . g0rbolrycs [ 0 ] , &
rtPrevZCX . jdg42luxap , 3 ) ; tmp_e = rt_ZCFcnRefine ( rtDW . lwu0ota2wt [ 0
] , & rtDW . g0rbolrycs [ 0 ] , ( rtDW . pan5gcvylw [ 0 ] ) ) ; anz44mi22v =
( tmp_e != 0 ) ; tmp_e = rt_ZCFcnRefine ( rtDW . lwu0ota2wt [ 1 ] , & rtDW .
g0rbolrycs [ 1 ] , ( rtDW . pan5gcvylw [ 1 ] ) ) ; anz44mi22v = ( ( tmp_e !=
0 ) || anz44mi22v ) ; tmp_e = rt_ZCFcnRefine ( rtDW . lwu0ota2wt [ 2 ] , &
rtDW . g0rbolrycs [ 2 ] , ( rtDW . pan5gcvylw [ 2 ] ) ) ; anz44mi22v = ( (
tmp_e != 0 ) || anz44mi22v ) ; memcpy ( & rtPrevZCX . jdg42luxap , & rtDW .
g0rbolrycs [ 0 ] , 3 ) ; } time_p = ssGetT ( rtS ) ; simulationData -> mData
-> mTime . mN = 1 ; simulationData -> mData -> mTime . mX = & time_p ;
simulationData -> mData -> mContStates . mN = 2 ; simulationData -> mData ->
mContStates . mX = & rtX . mmg5234zf5 [ 0 ] ; simulationData -> mData ->
mDiscStates . mN = 9 ; simulationData -> mData -> mDiscStates . mX = & rtDW .
gdnhhqi5jl [ 0 ] ; simulationData -> mData -> mModeVector . mN = 3 ;
simulationData -> mData -> mModeVector . mX = & rtDW . i0ge3te0zu [ 0 ] ;
iw4wsgify2 = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) ->
foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents = iw4wsgify2
; simulationData -> mData -> mHadEvents = false ; simulationData -> mData ->
mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; iw4wsgify2 = ( ssGetMdlInfoPtr
( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = iw4wsgify2 ; iw4wsgify2 = ssIsSolverCheckingCIC ( rtS
) ; simulationData -> mData -> mIsSolverCheckingCIC = iw4wsgify2 ; iw4wsgify2
= ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = iw4wsgify2 ; simulationData -> mData ->
mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; iw4wsgify2
= ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = iw4wsgify2 ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_m [ 0 ] = 0 ;
tmp_i [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_i [ 1 ] = rtB . asepqqecqj [ 1 ] ;
tmp_i [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_i [ 3 ] = rtB . asepqqecqj [ 3 ] ;
tmp_m [ 1 ] = 4 ; tmp_i [ 4 ] = rtB . ifpoliolwo [ 0 ] ; tmp_i [ 5 ] = rtB .
ifpoliolwo [ 1 ] ; tmp_i [ 6 ] = rtB . ifpoliolwo [ 2 ] ; tmp_i [ 7 ] = rtB .
ifpoliolwo [ 3 ] ; tmp_m [ 2 ] = 8 ; tmp_i [ 8 ] = rtB . p15kjgtpsv [ 0 ] ;
tmp_i [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_i [ 10 ] = rtB . p15kjgtpsv [ 2 ]
; tmp_i [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_m [ 3 ] = 12 ; simulationData
-> mData -> mInputValues . mN = 12 ; simulationData -> mData -> mInputValues
. mX = & tmp_i [ 0 ] ; simulationData -> mData -> mInputOffsets . mN = 4 ;
simulationData -> mData -> mInputOffsets . mX = & tmp_m [ 0 ] ;
simulationData -> mData -> mOutputs . mN = 14 ; simulationData -> mData ->
mOutputs . mX = & rtB . gd1k0xmto2 [ 0 ] ; simulationData -> mData ->
mTolerances . mN = 0 ; simulationData -> mData -> mTolerances . mX = NULL ;
simulationData -> mData -> mCstateHasChanged = false ; simulationData ->
mData -> mDstateHasChanged = false ; time_e = ssGetTaskTime ( rtS , 0 ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time_e ; simulationData -> mData -> mSampleHits . mN = 0 ;
simulationData -> mData -> mSampleHits . mX = NULL ; simulationData -> mData
-> mIsFundamentalSampleHit = false ; simulationData -> mData -> mHadEvents =
anz44mi22v ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW . cxiazli5ii
; diagnosticTree_p = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; tmp_e = ne_simulator_method ( ( NeslSimulator * ) rtDW
. hbvvke1n10 , NESL_SIM_OUTPUTS , simulationData , diagnosticManager ) ; if (
tmp_e != 0 ) { iw4wsgify2 = error_buffer_is_empty ( ssGetErrorStatus ( rtS )
) ; if ( iw4wsgify2 ) { msg_p = rtw_diagnostics_msg ( diagnosticTree_p ) ;
ssSetErrorStatus ( rtS , msg_p ) ; } } if ( ssIsMajorTimeStep ( rtS ) &&
simulationData -> mData -> mCstateHasChanged ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } if ( ssIsMajorTimeStep
( rtS ) && ( simulationData -> mData -> mCstateHasChanged || simulationData
-> mData -> mDstateHasChanged ) ) { time_i = ssGetT ( rtS ) ; simulationData
-> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime . mX = & time_i
; simulationData -> mData -> mContStates . mN = 2 ; simulationData -> mData
-> mContStates . mX = & rtX . mmg5234zf5 [ 0 ] ; simulationData -> mData ->
mDiscStates . mN = 9 ; simulationData -> mData -> mDiscStates . mX = & rtDW .
gdnhhqi5jl [ 0 ] ; simulationData -> mData -> mModeVector . mN = 3 ;
simulationData -> mData -> mModeVector . mX = & rtDW . i0ge3te0zu [ 0 ] ;
iw4wsgify2 = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) ->
foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents = iw4wsgify2
; simulationData -> mData -> mHadEvents = false ; simulationData -> mData ->
mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; iw4wsgify2 = ( ssGetMdlInfoPtr
( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = iw4wsgify2 ; iw4wsgify2 = ssIsSolverCheckingCIC ( rtS
) ; simulationData -> mData -> mIsSolverCheckingCIC = iw4wsgify2 ; iw4wsgify2
= ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = iw4wsgify2 ; simulationData -> mData ->
mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; iw4wsgify2
= ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = iw4wsgify2 ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_j [ 0 ] = 0 ;
tmp_g [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_g [ 1 ] = rtB . asepqqecqj [ 1 ] ;
tmp_g [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_g [ 3 ] = rtB . asepqqecqj [ 3 ] ;
tmp_j [ 1 ] = 4 ; tmp_g [ 4 ] = rtB . ifpoliolwo [ 0 ] ; tmp_g [ 5 ] = rtB .
ifpoliolwo [ 1 ] ; tmp_g [ 6 ] = rtB . ifpoliolwo [ 2 ] ; tmp_g [ 7 ] = rtB .
ifpoliolwo [ 3 ] ; tmp_j [ 2 ] = 8 ; tmp_g [ 8 ] = rtB . p15kjgtpsv [ 0 ] ;
tmp_g [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_g [ 10 ] = rtB . p15kjgtpsv [ 2 ]
; tmp_g [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_j [ 3 ] = 12 ; simulationData
-> mData -> mInputValues . mN = 12 ; simulationData -> mData -> mInputValues
. mX = & tmp_g [ 0 ] ; simulationData -> mData -> mInputOffsets . mN = 4 ;
simulationData -> mData -> mInputOffsets . mX = & tmp_j [ 0 ] ;
simulationData -> mData -> mNonSampledZCs . mN = 3 ; simulationData -> mData
-> mNonSampledZCs . mX = & _rtZCSV -> oo4l2j13md ; simulationData -> mData ->
mNonSampledZCs . mN = 3 ; simulationData -> mData -> mNonSampledZCs . mX = &
rtDW . pan5gcvylw [ 0 ] ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW
. cxiazli5ii ; diagnosticTree_e = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; tmp_e = ne_simulator_method ( ( NeslSimulator * ) rtDW
. hbvvke1n10 , NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager )
; if ( tmp_e != 0 ) { iw4wsgify2 = error_buffer_is_empty ( ssGetErrorStatus (
rtS ) ) ; if ( iw4wsgify2 ) { msg_e = rtw_diagnostics_msg ( diagnosticTree_e
) ; ssSetErrorStatus ( rtS , msg_e ) ; } } rt_ZCFcnRefine ( rtDW . lwu0ota2wt
[ 0 ] , & rtDW . g0rbolrycs [ 0 ] , ( rtDW . pan5gcvylw [ 0 ] ) ) ;
rt_ZCFcnRefine ( rtDW . lwu0ota2wt [ 1 ] , & rtDW . g0rbolrycs [ 1 ] , ( rtDW
. pan5gcvylw [ 1 ] ) ) ; rt_ZCFcnRefine ( rtDW . lwu0ota2wt [ 2 ] , & rtDW .
g0rbolrycs [ 2 ] , ( rtDW . pan5gcvylw [ 2 ] ) ) ; memcpy ( & rtPrevZCX .
jdg42luxap , & rtDW . g0rbolrycs [ 0 ] , 3 ) ; } simulationData = (
NeslSimulationData * ) rtDW . elb0r4kd24 ; time_m = ssGetT ( rtS ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time_m ; simulationData -> mData -> mContStates . mN = 0 ;
simulationData -> mData -> mContStates . mX = NULL ; simulationData -> mData
-> mDiscStates . mN = 0 ; simulationData -> mData -> mDiscStates . mX = &
rtDW . k4lrp1mqqo ; simulationData -> mData -> mModeVector . mN = 0 ;
simulationData -> mData -> mModeVector . mX = & rtDW . otllr3ihnw ;
iw4wsgify2 = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) ->
foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents = iw4wsgify2
; simulationData -> mData -> mHadEvents = false ; simulationData -> mData ->
mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; iw4wsgify2 = ( ssGetMdlInfoPtr
( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = iw4wsgify2 ; iw4wsgify2 = ssIsSolverCheckingCIC ( rtS
) ; simulationData -> mData -> mIsSolverCheckingCIC = iw4wsgify2 ;
simulationData -> mData -> mIsComputingJacobian = false ; simulationData ->
mData -> mIsEvaluatingF0 = false ; iw4wsgify2 = ssIsSolverRequestingReset (
rtS ) ; simulationData -> mData -> mIsSolverRequestingReset = iw4wsgify2 ;
simulationData -> mData -> mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep (
rtS ) ; tmp_c [ 0 ] = 0 ; tmp_f [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_f [ 1 ]
= rtB . asepqqecqj [ 1 ] ; tmp_f [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_f [ 3 ]
= rtB . asepqqecqj [ 3 ] ; tmp_c [ 1 ] = 4 ; tmp_f [ 4 ] = rtB . ifpoliolwo [
0 ] ; tmp_f [ 5 ] = rtB . ifpoliolwo [ 1 ] ; tmp_f [ 6 ] = rtB . ifpoliolwo [
2 ] ; tmp_f [ 7 ] = rtB . ifpoliolwo [ 3 ] ; tmp_c [ 2 ] = 8 ; tmp_f [ 8 ] =
rtB . p15kjgtpsv [ 0 ] ; tmp_f [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_f [ 10 ]
= rtB . p15kjgtpsv [ 2 ] ; tmp_f [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_c [ 3
] = 12 ; memcpy ( & tmp_f [ 12 ] , & rtB . gd1k0xmto2 [ 0 ] , 14U * sizeof (
real_T ) ) ; tmp_c [ 4 ] = 26 ; simulationData -> mData -> mInputValues . mN
= 26 ; simulationData -> mData -> mInputValues . mX = & tmp_f [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 5 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_c [ 0 ] ; simulationData -> mData -> mOutputs .
mN = 2 ; simulationData -> mData -> mOutputs . mX = & rtB . l5aisodevg [ 0 ]
; simulationData -> mData -> mTolerances . mN = 0 ; simulationData -> mData
-> mTolerances . mX = NULL ; simulationData -> mData -> mCstateHasChanged =
false ; simulationData -> mData -> mDstateHasChanged = false ; time_g =
ssGetTaskTime ( rtS , 0 ) ; simulationData -> mData -> mTime . mN = 1 ;
simulationData -> mData -> mTime . mX = & time_g ; simulationData -> mData ->
mSampleHits . mN = 0 ; simulationData -> mData -> mSampleHits . mX = NULL ;
simulationData -> mData -> mIsFundamentalSampleHit = false ; simulationData
-> mData -> mHadEvents = false ; diagnosticManager = ( NeuDiagnosticManager *
) rtDW . pr5kzcttse ; diagnosticTree_i =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_e =
ne_simulator_method ( ( NeslSimulator * ) rtDW . pfon4t4jjl ,
NESL_SIM_OUTPUTS , simulationData , diagnosticManager ) ; if ( tmp_e != 0 ) {
iw4wsgify2 = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if (
iw4wsgify2 ) { msg_i = rtw_diagnostics_msg ( diagnosticTree_i ) ;
ssSetErrorStatus ( rtS , msg_i ) ; } } if ( ssIsMajorTimeStep ( rtS ) &&
simulationData -> mData -> mCstateHasChanged ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } UNUSED_PARAMETER ( tid
) ; } void MdlOutputsTID2 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void
MdlUpdate ( int_T tid ) { NeslSimulationData * simulationData ;
NeuDiagnosticManager * diagnosticManager ; NeuDiagnosticTree * diagnosticTree
; char * msg ; real_T tmp_p [ 12 ] ; real_T time ; int32_T tmp_i ; int_T
tmp_e [ 4 ] ; boolean_T tmp ; simulationData = ( NeslSimulationData * ) rtDW
. gelipinn1a ; time = ssGetT ( rtS ) ; simulationData -> mData -> mTime . mN
= 1 ; simulationData -> mData -> mTime . mX = & time ; simulationData ->
mData -> mContStates . mN = 2 ; simulationData -> mData -> mContStates . mX =
& rtX . mmg5234zf5 [ 0 ] ; simulationData -> mData -> mDiscStates . mN = 9 ;
simulationData -> mData -> mDiscStates . mX = & rtDW . gdnhhqi5jl [ 0 ] ;
simulationData -> mData -> mModeVector . mN = 3 ; simulationData -> mData ->
mModeVector . mX = & rtDW . i0ge3te0zu [ 0 ] ; tmp = ( ssIsMajorTimeStep (
rtS ) && ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents ) ; simulationData
-> mData -> mFoundZcEvents = tmp ; simulationData -> mData -> mHadEvents =
false ; simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS
) ; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_p [ 1 ] = rtB . asepqqecqj [ 1 ] ;
tmp_p [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_p [ 3 ] = rtB . asepqqecqj [ 3 ] ;
tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ifpoliolwo [ 0 ] ; tmp_p [ 5 ] = rtB .
ifpoliolwo [ 1 ] ; tmp_p [ 6 ] = rtB . ifpoliolwo [ 2 ] ; tmp_p [ 7 ] = rtB .
ifpoliolwo [ 3 ] ; tmp_e [ 2 ] = 8 ; tmp_p [ 8 ] = rtB . p15kjgtpsv [ 0 ] ;
tmp_p [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_p [ 10 ] = rtB . p15kjgtpsv [ 2 ]
; tmp_p [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_e [ 3 ] = 12 ; simulationData
-> mData -> mInputValues . mN = 12 ; simulationData -> mData -> mInputValues
. mX = & tmp_p [ 0 ] ; simulationData -> mData -> mInputOffsets . mN = 4 ;
simulationData -> mData -> mInputOffsets . mX = & tmp_e [ 0 ] ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . cxiazli5ii ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW . hbvvke1n10 ,
NESL_SIM_UPDATE , simulationData , diagnosticManager ) ; if ( tmp_i != 0 ) {
tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) { msg =
rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; } }
UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID2 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) {
NeslSimulationData * simulationData ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; XDot * _rtXdot ;
char * msg ; real_T tmp_p [ 12 ] ; real_T time ; int32_T tmp_i ; int_T tmp_e
[ 4 ] ; boolean_T tmp ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ;
simulationData = ( NeslSimulationData * ) rtDW . gelipinn1a ; time = ssGetT (
rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time ; simulationData -> mData -> mContStates . mN = 2 ;
simulationData -> mData -> mContStates . mX = & rtX . mmg5234zf5 [ 0 ] ;
simulationData -> mData -> mDiscStates . mN = 9 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . gdnhhqi5jl [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
i0ge3te0zu [ 0 ] ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo (
rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp ; simulationData -> mData -> mHadEvents = false ; simulationData -> mData
-> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr (
rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ;
simulationData -> mData -> mIsSolverCheckingCIC = tmp ; tmp =
ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = tmp ; simulationData -> mData -> mIsEvaluatingF0 = (
ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; tmp = ssIsSolverRequestingReset
( rtS ) ; simulationData -> mData -> mIsSolverRequestingReset = tmp ;
simulationData -> mData -> mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep (
rtS ) ; tmp_e [ 0 ] = 0 ; tmp_p [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_p [ 1 ]
= rtB . asepqqecqj [ 1 ] ; tmp_p [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_p [ 3 ]
= rtB . asepqqecqj [ 3 ] ; tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ifpoliolwo [
0 ] ; tmp_p [ 5 ] = rtB . ifpoliolwo [ 1 ] ; tmp_p [ 6 ] = rtB . ifpoliolwo [
2 ] ; tmp_p [ 7 ] = rtB . ifpoliolwo [ 3 ] ; tmp_e [ 2 ] = 8 ; tmp_p [ 8 ] =
rtB . p15kjgtpsv [ 0 ] ; tmp_p [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_p [ 10 ]
= rtB . p15kjgtpsv [ 2 ] ; tmp_p [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_e [ 3
] = 12 ; simulationData -> mData -> mInputValues . mN = 12 ; simulationData
-> mData -> mInputValues . mX = & tmp_p [ 0 ] ; simulationData -> mData ->
mInputOffsets . mN = 4 ; simulationData -> mData -> mInputOffsets . mX = &
tmp_e [ 0 ] ; simulationData -> mData -> mDx . mN = 2 ; simulationData ->
mData -> mDx . mX = & _rtXdot -> mmg5234zf5 [ 0 ] ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . cxiazli5ii ; diagnosticTree =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
ne_simulator_method ( ( NeslSimulator * ) rtDW . hbvvke1n10 ,
NESL_SIM_DERIVATIVES , simulationData , diagnosticManager ) ; if ( tmp_i != 0
) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) {
msg = rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg )
; } } } void MdlProjection ( void ) { } void MdlZeroCrossings ( void ) {
NeslSimulationData * simulationData ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; ZCV * _rtZCSV ; char
* msg ; real_T tmp_p [ 12 ] ; real_T time ; int32_T tmp_i ; int_T tmp_e [ 4 ]
; boolean_T tmp ; _rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ;
_rtZCSV -> n0mgwbn0co = ssGetT ( rtS ) - rtP . HVControlSwitch_Time ; _rtZCSV
-> px5q0ifs0m = ssGetT ( rtS ) - rtP . HVControlSwitch_Time_d3xzd30hb0 ;
_rtZCSV -> gblnr0iypr [ 0 ] = rtB . bqza00cyqn - rtP .
StairGenerator_TimeInput [ 0 ] ; _rtZCSV -> gblnr0iypr [ 1 ] = rtB .
bqza00cyqn - rtP . StairGenerator_TimeInput [ 1 ] ; _rtZCSV -> gblnr0iypr [ 2
] = rtB . bqza00cyqn - rtP . StairGenerator_TimeInput [ 2 ] ; _rtZCSV ->
gblnr0iypr [ 3 ] = rtB . bqza00cyqn - rtP . StairGenerator_TimeInput [ 3 ] ;
simulationData = ( NeslSimulationData * ) rtDW . gelipinn1a ; time = ssGetT (
rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time ; simulationData -> mData -> mContStates . mN = 2 ;
simulationData -> mData -> mContStates . mX = & rtX . mmg5234zf5 [ 0 ] ;
simulationData -> mData -> mDiscStates . mN = 9 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . gdnhhqi5jl [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
i0ge3te0zu [ 0 ] ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo (
rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp ; simulationData -> mData -> mHadEvents = false ; simulationData -> mData
-> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr (
rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ;
simulationData -> mData -> mIsSolverCheckingCIC = tmp ; tmp =
ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = tmp ; simulationData -> mData -> mIsEvaluatingF0 = (
ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; tmp = ssIsSolverRequestingReset
( rtS ) ; simulationData -> mData -> mIsSolverRequestingReset = tmp ;
simulationData -> mData -> mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep (
rtS ) ; tmp_e [ 0 ] = 0 ; tmp_p [ 0 ] = rtB . asepqqecqj [ 0 ] ; tmp_p [ 1 ]
= rtB . asepqqecqj [ 1 ] ; tmp_p [ 2 ] = rtB . asepqqecqj [ 2 ] ; tmp_p [ 3 ]
= rtB . asepqqecqj [ 3 ] ; tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ifpoliolwo [
0 ] ; tmp_p [ 5 ] = rtB . ifpoliolwo [ 1 ] ; tmp_p [ 6 ] = rtB . ifpoliolwo [
2 ] ; tmp_p [ 7 ] = rtB . ifpoliolwo [ 3 ] ; tmp_e [ 2 ] = 8 ; tmp_p [ 8 ] =
rtB . p15kjgtpsv [ 0 ] ; tmp_p [ 9 ] = rtB . p15kjgtpsv [ 1 ] ; tmp_p [ 10 ]
= rtB . p15kjgtpsv [ 2 ] ; tmp_p [ 11 ] = rtB . p15kjgtpsv [ 3 ] ; tmp_e [ 3
] = 12 ; simulationData -> mData -> mInputValues . mN = 12 ; simulationData
-> mData -> mInputValues . mX = & tmp_p [ 0 ] ; simulationData -> mData ->
mInputOffsets . mN = 4 ; simulationData -> mData -> mInputOffsets . mX = &
tmp_e [ 0 ] ; simulationData -> mData -> mNonSampledZCs . mN = 3 ;
simulationData -> mData -> mNonSampledZCs . mX = & _rtZCSV -> oo4l2j13md ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . cxiazli5ii ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW . hbvvke1n10 ,
NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager ) ; if ( tmp_i !=
0 ) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) {
msg = rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg )
; } } } void MdlTerminate ( void ) { neu_destroy_diagnostic_manager ( (
NeuDiagnosticManager * ) rtDW . cxiazli5ii ) ; nesl_destroy_simulation_data (
( NeslSimulationData * ) rtDW . gelipinn1a ) ; nesl_erase_simulator (
"PrechargeModel/Solver Configuration_1" ) ; nesl_destroy_registry ( ) ;
neu_destroy_diagnostic_manager ( ( NeuDiagnosticManager * ) rtDW . pr5kzcttse
) ; nesl_destroy_simulation_data ( ( NeslSimulationData * ) rtDW . elb0r4kd24
) ; nesl_erase_simulator ( "PrechargeModel/Solver Configuration_1" ) ;
nesl_destroy_registry ( ) ; } static void
mr_PrechargeModel_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int
j , const void * srcData , size_t numBytes ) ; static void
mr_PrechargeModel_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int
j , const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_PrechargeModel_restoreDataFromMxArray ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static
void mr_PrechargeModel_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_PrechargeModel_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) ; static void
mr_PrechargeModel_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j ,
mxCreateDoubleScalar ( ( real_T ) bitVal ) ) ; } static uint_T
mr_PrechargeModel_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) ; static uint_T
mr_PrechargeModel_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T )
mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( (
1u << numBits ) - 1u ) ; } static void
mr_PrechargeModel_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
; static void mr_PrechargeModel_cacheDataToMxArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_PrechargeModel_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) ; static void mr_PrechargeModel_restoreDataFromMxArrayWithOffset (
void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex
offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * )
mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T *
) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes )
; } static void mr_PrechargeModel_cacheBitFieldToCellArrayWithOffset (
mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal )
; static void mr_PrechargeModel_cacheBitFieldToCellArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( real_T ) fieldVal ) ) ; } static uint_T
mr_PrechargeModel_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_PrechargeModel_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) {
const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_PrechargeModel_GetDWork ( ) { static
const char_T * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "rtPrevZCX" , } ;
mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_PrechargeModel_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & (
rtB ) , sizeof ( rtB ) ) ; { static const char_T * rtdwDataFieldNames [ 19 ]
= { "rtDW.aaswsr1rcu" , "rtDW.argz0f5dqi" , "rtDW.fnx34i5x5n" ,
"rtDW.gdnhhqi5jl" , "rtDW.pan5gcvylw" , "rtDW.k4lrp1mqqo" , "rtDW.na4n4iguxp"
, "rtDW.i0ge3te0zu" , "rtDW.otllr3ihnw" , "rtDW.l0224yqaan" ,
"rtDW.oou11isfot" , "rtDW.nfwbh1ti3i" , "rtDW.lwu0ota2wt" , "rtDW.g0rbolrycs"
, "rtDW.kkgrjivyjr" , "rtDW.bg0p5tdgxq" , "rtDW.dmyikon5da" ,
"rtDW.ekhogeqn0r" , "rtDW.ccsx3v14fa" , } ; mxArray * rtdwData =
mxCreateStructMatrix ( 1 , 1 , 19 , rtdwDataFieldNames ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void * ) &
( rtDW . aaswsr1rcu ) , sizeof ( rtDW . aaswsr1rcu ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) &
( rtDW . argz0f5dqi ) , sizeof ( rtDW . argz0f5dqi ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) &
( rtDW . fnx34i5x5n ) , sizeof ( rtDW . fnx34i5x5n ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) &
( rtDW . gdnhhqi5jl ) , sizeof ( rtDW . gdnhhqi5jl ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) &
( rtDW . pan5gcvylw ) , sizeof ( rtDW . pan5gcvylw ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) &
( rtDW . k4lrp1mqqo ) , sizeof ( rtDW . k4lrp1mqqo ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) &
( rtDW . na4n4iguxp ) , sizeof ( rtDW . na4n4iguxp ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) &
( rtDW . i0ge3te0zu ) , sizeof ( rtDW . i0ge3te0zu ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) &
( rtDW . otllr3ihnw ) , sizeof ( rtDW . otllr3ihnw ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) &
( rtDW . l0224yqaan ) , sizeof ( rtDW . l0224yqaan ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) &
( rtDW . oou11isfot ) , sizeof ( rtDW . oou11isfot ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const void * ) &
( rtDW . nfwbh1ti3i ) , sizeof ( rtDW . nfwbh1ti3i ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const void * ) &
( rtDW . lwu0ota2wt ) , sizeof ( rtDW . lwu0ota2wt ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const void * ) &
( rtDW . g0rbolrycs ) , sizeof ( rtDW . g0rbolrycs ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 14 , ( const void * ) &
( rtDW . kkgrjivyjr ) , sizeof ( rtDW . kkgrjivyjr ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 15 , ( const void * ) &
( rtDW . bg0p5tdgxq ) , sizeof ( rtDW . bg0p5tdgxq ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 16 , ( const void * ) &
( rtDW . dmyikon5da ) , sizeof ( rtDW . dmyikon5da ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 17 , ( const void * ) &
( rtDW . ekhogeqn0r ) , sizeof ( rtDW . ekhogeqn0r ) ) ;
mr_PrechargeModel_cacheDataAsMxArray ( rtdwData , 0 , 18 , ( const void * ) &
( rtDW . ccsx3v14fa ) , sizeof ( rtDW . ccsx3v14fa ) ) ; mxSetFieldByNumber (
ssDW , 0 , 1 , rtdwData ) ; } mr_PrechargeModel_cacheDataAsMxArray ( ssDW , 0
, 2 , ( const void * ) & ( rtPrevZCX ) , sizeof ( rtPrevZCX ) ) ; return ssDW
; } void mr_PrechargeModel_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW
; mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0
, 0 , sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber (
ssDW , 0 , 1 ) ; mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & (
rtDW . aaswsr1rcu ) , rtdwData , 0 , 0 , sizeof ( rtDW . aaswsr1rcu ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . argz0f5dqi )
, rtdwData , 0 , 1 , sizeof ( rtDW . argz0f5dqi ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . fnx34i5x5n )
, rtdwData , 0 , 2 , sizeof ( rtDW . fnx34i5x5n ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . gdnhhqi5jl )
, rtdwData , 0 , 3 , sizeof ( rtDW . gdnhhqi5jl ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . pan5gcvylw )
, rtdwData , 0 , 4 , sizeof ( rtDW . pan5gcvylw ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . k4lrp1mqqo )
, rtdwData , 0 , 5 , sizeof ( rtDW . k4lrp1mqqo ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . na4n4iguxp )
, rtdwData , 0 , 6 , sizeof ( rtDW . na4n4iguxp ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . i0ge3te0zu )
, rtdwData , 0 , 7 , sizeof ( rtDW . i0ge3te0zu ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . otllr3ihnw )
, rtdwData , 0 , 8 , sizeof ( rtDW . otllr3ihnw ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . l0224yqaan )
, rtdwData , 0 , 9 , sizeof ( rtDW . l0224yqaan ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . oou11isfot )
, rtdwData , 0 , 10 , sizeof ( rtDW . oou11isfot ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . nfwbh1ti3i )
, rtdwData , 0 , 11 , sizeof ( rtDW . nfwbh1ti3i ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . lwu0ota2wt )
, rtdwData , 0 , 12 , sizeof ( rtDW . lwu0ota2wt ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . g0rbolrycs )
, rtdwData , 0 , 13 , sizeof ( rtDW . g0rbolrycs ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . kkgrjivyjr )
, rtdwData , 0 , 14 , sizeof ( rtDW . kkgrjivyjr ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . bg0p5tdgxq )
, rtdwData , 0 , 15 , sizeof ( rtDW . bg0p5tdgxq ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . dmyikon5da )
, rtdwData , 0 , 16 , sizeof ( rtDW . dmyikon5da ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . ekhogeqn0r )
, rtdwData , 0 , 17 , sizeof ( rtDW . ekhogeqn0r ) ) ;
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . ccsx3v14fa )
, rtdwData , 0 , 18 , sizeof ( rtDW . ccsx3v14fa ) ) ; }
mr_PrechargeModel_restoreDataFromMxArray ( ( void * ) & ( rtPrevZCX ) , ssDW
, 0 , 2 , sizeof ( rtPrevZCX ) ) ; } mxArray *
mr_PrechargeModel_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 3 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char_T * blockType [ 3 ] = { "SimscapeExecutionBlock" ,
"SimscapeExecutionBlock" , "Scope" , } ; static const char_T * blockPath [ 3
] = { "PrechargeModel/Solver Configuration/EVAL_KEY/STATE_1" ,
"PrechargeModel/Solver Configuration/EVAL_KEY/OUTPUT_1_0" ,
"PrechargeModel/Scope" , } ; static const int reason [ 3 ] = { 0 , 0 , 0 , }
; for ( subs [ 0 ] = 0 ; subs [ 0 ] < 3 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] =
0 ; offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateDoubleScalar ( ( real_T ) reason [ subs [ 0 ] ] ) ) ; } }
return data ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS ,
2 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ;
ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 2 ) ; ssSetNumBlocks ( rtS , 50 ) ;
ssSetNumBlockIO ( rtS , 11 ) ; ssSetNumBlockParams ( rtS , 25 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 3405627555U ) ; ssSetChecksumVal ( rtS , 1 ,
861820321U ) ; ssSetChecksumVal ( rtS , 2 , 3847794471U ) ; ssSetChecksumVal
( rtS , 3 , 3409354729U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; executionInfo -> gblObjects_ . numToFiles = 0 ;
executionInfo -> gblObjects_ . numFrFiles = 0 ; executionInfo -> gblObjects_
. numFrWksBlocks = 0 ; executionInfo -> gblObjects_ . numModelInputs = 0 ;
executionInfo -> gblObjects_ . numRootInportBlks = 0 ; executionInfo ->
gblObjects_ . inportDataTypeIdx = NULL ; executionInfo -> gblObjects_ .
inportDims = NULL ; executionInfo -> gblObjects_ . inportComplex = NULL ;
executionInfo -> gblObjects_ . inportInterpoFlag = NULL ; executionInfo ->
gblObjects_ . inportContinuous = NULL ; ( void ) memset ( ( char_T * ) rtS ,
0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char_T * ) & mdlInfo , 0 ,
sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char_T * ) & blkInfo2 ,
0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char_T * ) &
blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ; ssSetBlkInfo2Ptr (
rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , & blkInfoSLSize ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo ( rtS ,
executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 23 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
PrechargeModel_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive (
rtS , true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "PrechargeModel" ) ;
ssSetPath ( rtS , "PrechargeModel" ) ; ssSetTStart ( rtS , 0.0 ) ;
ssSetTFinal ( rtS , 2.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
rt_DataLoggingInfo . loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1
, 2 , 2 , 2 , 9 , 1 } ; static int_T rt_LoggedStateNumDimensions [ ] = { 1 ,
1 , 1 , 1 , 1 , 1 , 1 } ; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1
, 2 , 2 , 2 , 9 , 1 } ; static boolean_T rt_LoggedStateIsVarDims [ ] = { 0 ,
0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ]
= { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_BOOLEAN } ; static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 ,
0 , 0 , 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static const char_T *
rt_LoggedStateLabels [ ] = { "CSTATE" , "CSTATE" , "Discrete" , "Discrete" ,
"Discrete" , "Discrete" , "DSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = { "PrechargeModel/TS Capacitor" ,
"PrechargeModel/600V HV  Battery Pack" ,
"PrechargeModel/Solver\nConfiguration/EVAL_KEY/INPUT_2_1_1" ,
"PrechargeModel/Solver\nConfiguration/EVAL_KEY/INPUT_3_1_1" ,
"PrechargeModel/Solver\nConfiguration/EVAL_KEY/INPUT_1_1_1" ,
"PrechargeModel/Solver\nConfiguration/EVAL_KEY/STATE_1" ,
 "PrechargeModel/Stair Generator/Continuous/While Iterator\nSubsystem/Detect Fall\nNonpositive/Delay Input1"
} ; static const char_T * rt_LoggedStateNames [ ] = {
"PrechargeModel.TS_Capacitor.vc" ,
"PrechargeModel.x600V_HV_Battery_Pack.charge" , "Discrete" , "Discrete" ,
"Discrete" , "Discrete" , "DSTATE" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 ,
0 , 0 , 1.0 , 0 , 0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 , 0
, 1 , 2 , 3 , 22 } ; static RTWLogSignalInfo rt_LoggedStateSignalInfo = { 7 ,
rt_LoggedStateWidths , rt_LoggedStateNumDimensions , rt_LoggedStateDimensions
, rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 7 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . mmg5234zf5 [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . mmg5234zf5 [ 1 ] ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) rtDW . aaswsr1rcu ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) rtDW . argz0f5dqi ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) rtDW . fnx34i5x5n ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) rtDW . gdnhhqi5jl ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtDW . nfwbh1ti3i ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"xFinal" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 2 ] ;
static real_T absTol [ 2 ] = { 1.0E-6 , 1.0E-6 } ; static uint8_T
absTolControl [ 2 ] = { 0U , 0U } ; static real_T
contStateJacPerturbBoundMinVec [ 2 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 2 ] ; static uint8_T zcAttributes [ 9 ] = {
( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL
) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( 0x80 | ZC_EVENT_P2Z |
ZC_EVENT_P2N | ZC_EVENT_Z2P | ZC_EVENT_N2P ) , ( 0x80 | ZC_EVENT_P2Z |
ZC_EVENT_P2N | ZC_EVENT_Z2P | ZC_EVENT_N2P ) , ( 0x80 | ZC_EVENT_P2Z |
ZC_EVENT_P2N | ZC_EVENT_Z2P | ZC_EVENT_N2P ) } ; static ssNonContDerivSigInfo
nonContDerivSigInfo [ 3 ] = { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
h5s12bgqxk ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
nrxejncqrw ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
pjlmc1lzp1 ) , ( NULL ) } } ; { int i ; for ( i = 0 ; i < 2 ; ++ i ) {
contStateJacPerturbBoundMinVec [ i ] = 0 ; contStateJacPerturbBoundMaxVec [ i
] = rtGetInf ( ) ; } } ssSetSolverRelTol ( rtS , 0.001 ) ; ssSetStepSize (
rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , -
1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 0.04 )
; ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 1 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 3 ) ; ssSetNonContDerivSigInfos ( rtS ,
nonContDerivSigInfo ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS
, 1 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; _ssSetSolverUpdateJacobianAtReset ( rtS , true ) ;
ssSetAbsTolVector ( rtS , absTol ) ; ssSetAbsTolControlVector ( rtS ,
absTolControl ) ; ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 9 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 9 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; } {
ZCSigState * zc = ( ZCSigState * ) & rtPrevZCX ; ssSetPrevZCSigState ( rtS ,
zc ) ; } { rtPrevZCX . jdg42luxap = UNINITIALIZED_ZCSIG ; rtPrevZCX .
iiggpa4ztk = UNINITIALIZED_ZCSIG ; rtPrevZCX . jggsb5cnar =
UNINITIALIZED_ZCSIG ; } ssSetChecksumVal ( rtS , 0 , 3405627555U ) ;
ssSetChecksumVal ( rtS , 1 , 861820321U ) ; ssSetChecksumVal ( rtS , 2 ,
3847794471U ) ; ssSetChecksumVal ( rtS , 3 , 3409354729U ) ; { static const
sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo
rt_ExtModeInfo ; static const sysRanDType * systemRan [ 4 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) ,
& ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo
( rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS
) , ssGetTPtr ( rtS ) ) ; } slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_PrechargeModel_GetSimStateDisallowedBlocks ) ;
slsaGetWorkFcnForSimTargetOP ( rtS , mr_PrechargeModel_GetDWork ) ;
slsaSetWorkFcnForSimTargetOP ( rtS , mr_PrechargeModel_SetDWork ) ;
rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if ( ssGetErrorStatus ( rtS ) )
{ return rtS ; } executionInfo -> simulationOptions_ . stateSaveName_ =
rtliGetLogX ( ssGetRTWLogInfo ( rtS ) ) ; executionInfo -> simulationOptions_
. finalStateName_ = rtliGetLogXFinal ( ssGetRTWLogInfo ( rtS ) ) ;
executionInfo -> simulationOptions_ . outputSaveName_ = rtliGetLogY (
ssGetRTWLogInfo ( rtS ) ) ; return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
void MdlOutputsParameterSampleTime ( int_T tid ) { MdlOutputsTID2 ( tid ) ; }
