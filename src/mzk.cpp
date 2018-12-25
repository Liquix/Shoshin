#include <math.h>
#include "mzk.h"

#pragma code_seg(".mzkinit")
void mzk_init( short *buffer )
{
    for( int i=0; i<MZK_NUMSAMPLES; i++ ) 
    {
        const float fl = sinf( 6.2831f*440.0f * (float)i/(float)MZK_RATE );
        const float fr = sinf( 6.2831f*587.3f * (float)i/(float)MZK_RATE );

        buffer[2*i+0] = fl*32767.0f;
        buffer[2*i+1] = fr*32767.0f;
    }
}
