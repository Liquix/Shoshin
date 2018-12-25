#ifndef _MZK_H_
#define _MZK_H_

#define __fltused = 0;

#define MZK_DURATION    104
#define MZK_RATE        44100
#define MZK_NUMCHANNELS 2

#define MZK_NUMSAMPLES  (MZK_DURATION*MZK_RATE)
#define MZK_NUMSAMPLESC (MZK_NUMSAMPLES*MZK_NUMCHANNELS)

void mzk_init( short *buffer );

#endif