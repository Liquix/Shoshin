//// shoshin // a 4k by karo // 2018 ////
// all credit to iq; all is plagarized //

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include "intro.h"
#include "mzk.h"

#define XRES 1280
#define YRES  720

#pragma data_seg(".mus")
static const int wavHeader[11] = {
    0x46464952, 
    MZK_NUMSAMPLES*2+36, 
    0x45564157, 
    0x20746D66, 
    16, 
    WAVE_FORMAT_PCM|(MZK_NUMCHANNELS<<16), 
    MZK_RATE, 
    MZK_RATE*MZK_NUMCHANNELS*sizeof(short), 
    (MZK_NUMCHANNELS*sizeof(short))|((8*sizeof(short))<<16),
    0x61746164, 
    MZK_NUMSAMPLES*sizeof(short)
};

#pragma data_seg(".pfd")
static const PIXELFORMATDESCRIPTOR pfd = {0, 0, PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER};
#pragma data_seg(".dmss")
static DEVMODE screenSettings = {{0},0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0},0};
#pragma data_seg(".mzkbuf")
static short myMuzik[MZK_NUMSAMPLESC+22];

#pragma code_seg(".main")
void entrypoint( void )
{
    // full screen
    //if( ChangeDisplaySettings(&screenSettings, NULL/*,CDS_FULLSCREEN*/)!=DISP_CHANGE_SUCCESSFUL) return;
    ShowCursor( 0 );

    HWND hWnd = CreateWindow( (LPCSTR)0xC018,0,WS_VISIBLE,0,20,XRES,YRES,0,0,0,0);
    HDC hDC = GetDC(hWnd);

	SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
    wglMakeCurrent(hDC, wglCreateContext(hDC));

	intro_init();

    mzk_init( myMuzik+22 );
    memcpy( myMuzik, wavHeader, 44 );
    //sndPlaySound( (const char*)&myMuzik, SND_ASYNC|SND_MEMORY );

	long t, to = timeGetTime();

    do 
    {
        t = timeGetTime() - to;
        intro_do( t );
        wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );
    }while ( !GetAsyncKeyState(VK_ESCAPE) );
	
    sndPlaySound( 0, 0 );
    ChangeDisplaySettings( 0, 0 );
    ShowCursor(1);

    ExitProcess(0);
}
