#include "ne_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_sys_struct.h"
#include "PrechargeModel_a7fe4013_1_ds_dxf.h"
#include "PrechargeModel_a7fe4013_1_ds.h"
#include "PrechargeModel_a7fe4013_1_ds_externals.h"
#include "PrechargeModel_a7fe4013_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T PrechargeModel_a7fe4013_1_ds_dxf ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t10 , NeDsMethodOutput * out ) { if ( t10 -> mM
. mX [ 1ULL ] != 0 ) { out -> mDXF . mX [ 0ULL ] = - 1.0 ; } else { out ->
mDXF . mX [ 0ULL ] = - 1.0E-8 ; } if ( t10 -> mM . mX [ 0ULL ] != 0 ) { out
-> mDXF . mX [ 1ULL ] = - 1.010005 ; } else { out -> mDXF . mX [ 1ULL ] = -
1.0005000099999999 ; } if ( t10 -> mM . mX [ 1ULL ] != 0 ) { out -> mDXF . mX
[ 2ULL ] = 0.010001 ; } else { out -> mDXF . mX [ 2ULL ] = 1.00000000000001 ;
} if ( t10 -> mM . mX [ 2ULL ] != 0 ) { out -> mDXF . mX [ 3ULL ] = 5.0E-6 ;
} else { out -> mDXF . mX [ 3ULL ] = 0.0005 ; } if ( t10 -> mM . mX [ 0ULL ]
!= 0 ) { out -> mDXF . mX [ 4ULL ] = 1.000005 ; } else { out -> mDXF . mX [
4ULL ] = 0.00050001000000000006 ; } if ( t10 -> mM . mX [ 1ULL ] != 0 ) { out
-> mDXF . mX [ 5ULL ] = 1.0 ; } else { out -> mDXF . mX [ 5ULL ] = 1.0E-8 ; }
if ( t10 -> mM . mX [ 2ULL ] != 0 ) { out -> mDXF . mX [ 6ULL ] = - 5.0E-6 ;
} else { out -> mDXF . mX [ 6ULL ] = - 0.0005 ; } if ( t10 -> mM . mX [ 0ULL
] != 0 ) { out -> mDXF . mX [ 7ULL ] = - 5.0E-6 ; } else { out -> mDXF . mX [
7ULL ] = - 0.0005 ; } if ( t10 -> mM . mX [ 2ULL ] != 0 ) { out -> mDXF . mX
[ 8ULL ] = 1.000005 ; } else { out -> mDXF . mX [ 8ULL ] =
0.00050001000000000006 ; } ( void ) sys ; ( void ) out ; return 0 ; }
