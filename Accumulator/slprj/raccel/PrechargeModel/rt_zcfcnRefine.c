#include "zero_crossing_types.h"
#include "rtwtypes.h"
#include "rt_zcfcnRefine.h"
#include "solver_zc.h"
ZCEventType rt_ZCFcnRefine ( slZcEventType zcsDir , ZCSigState * prevZc ,
real_T currValue ) { slZcEventType tempEv ; ZCEventType zcEvent = NO_ZCEVENT
; static const slZcEventType eventMatrix [ 4 ] [ 4 ] = { { SL_ZCS_EVENT_NUL ,
SL_ZCS_EVENT_Z2P , SL_ZCS_EVENT_Z2N , SL_ZCS_EVENT_NUL } , { SL_ZCS_EVENT_P2Z
, SL_ZCS_EVENT_NUL , SL_ZCS_EVENT_P2N , SL_ZCS_EVENT_NUL } , {
SL_ZCS_EVENT_N2Z , SL_ZCS_EVENT_N2P , SL_ZCS_EVENT_NUL , SL_ZCS_EVENT_NUL } ,
{ SL_ZCS_EVENT_NUL , SL_ZCS_EVENT_NUL , SL_ZCS_EVENT_NUL , SL_ZCS_EVENT_NUL }
} ; const slZcEventType prevEv = ( slZcEventType ) ( ( ( uint8_T ) ( * prevZc
) ) >> 2 ) ; const slZcSignalSignType prevSign = ( slZcSignalSignType ) ( ( (
uint8_T ) ( * prevZc ) ) & ( uint8_T ) 0x03 ) ; const slZcSignalSignType
currSign = ( slZcSignalSignType ) ( ( currValue ) > 0.0 ? SL_ZCS_SIGN_POS : (
( currValue ) < 0.0 ? SL_ZCS_SIGN_NEG : SL_ZCS_SIGN_ZERO ) ) ; slZcEventType
currEv = eventMatrix [ prevSign ] [ currSign ] ; if ( slZcHadEvent ( currEv ,
zcsDir ) ) { currEv = ( slZcEventType ) ( slZcUnAliasEvents ( prevEv , currEv
) ) ; } else { currEv = SL_ZCS_EVENT_NUL ; } tempEv = ( slZcEventType ) (
currEv << 2 ) ; * prevZc = ( ZCSigState ) ( ( currSign ) | ( tempEv ) ) ; if
( ( currEv & SL_ZCS_EVENT_ALL_DN ) != 0 ) { zcEvent = FALLING_ZCEVENT ; }
else if ( ( currEv & SL_ZCS_EVENT_ALL_UP ) != 0 ) { zcEvent = RISING_ZCEVENT
; } else { zcEvent = NO_ZCEVENT ; } return zcEvent ; }
