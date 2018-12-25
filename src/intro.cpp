#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "config.h"
#include "ext.h"
#include "shader.inl"
#include "fp.h"

#pragma data_seg(".globalvars")
static int   fsid;
static float fparams[4 * 4];

#pragma code_seg(".introinit")
void intro_init()
{
	EXT_Init();

    int vsid = oglCreateShaderProgramv( GL_VERTEX_SHADER,   1, &vsh );
        fsid = oglCreateShaderProgramv( GL_FRAGMENT_SHADER, 1, &fsh );
 
    unsigned int pid;
    oglGenProgramPipelines(1, &pid);
    oglBindProgramPipeline(pid);
    oglUseProgramStages(pid, GL_VERTEX_SHADER_BIT, vsid);
    oglUseProgramStages(pid, GL_FRAGMENT_SHADER_BIT, fsid);

    /*#ifdef DEBUG
        int		result;
        char    info[1536];
        oglGetProgramiv( vsid, GL_LINK_STATUS, &result ); oglGetProgramInfoLog( vsid, 1024, NULL, (char *)info ); if( !result ) DebugBreak();
        oglGetProgramiv( fsid, GL_LINK_STATUS, &result ); oglGetProgramInfoLog( fsid, 1024, NULL, (char *)info ); if( !result ) DebugBreak();
        oglGetProgramiv( pid,  GL_LINK_STATUS, &result ); oglGetProgramInfoLog( pid,  1024, NULL, (char *)info ); if( !result ) DebugBreak();
    #endif*/
}

#pragma code_seg(".intromain")
void intro_do( long time )
{
    const float t  = 0.001f*(float)time;

    // camera position
    //fparams[ 0] = 2.0f*sinf(1.0f*t+0.1f);
	fparams[0] = t;
    fparams[ 1] = 0.0f;
    fparams[ 2] = 2.0f*cosf(1.0f*t);
    // camera target
    fparams[ 4] = 0.0f;
    fparams[ 5] = 0.0f;
    fparams[ 6] = 0.0f;
    // sphere
    fparams[ 8] = 0.0f;
    fparams[ 9] = 0.0f;
    fparams[10] = 0.0f;
    fparams[11] = 1.0f;

    oglProgramUniform4fv( fsid, 0, 4, fparams );

    glRects( -1, -1, 1, 1 );
}