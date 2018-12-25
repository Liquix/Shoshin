#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include "glext.h"
#include "ext.h"

#pragma data_seg(".glstrs")
static char *strs[] = {
    "glCreateShaderProgramv",
    "glGenProgramPipelines",
    "glBindProgramPipeline",
    "glUseProgramStages",
    "glProgramUniform4fv",
    #ifdef DEBUG
	"glGetProgramiv",
	"glGetProgramInfoLog",
    #endif
    };

#pragma data_seg(".glfuncs")
void *myglfunc[NUMFUNCIONES];

#pragma code_seg(".extinit")
void EXT_Init()
{
    for( int i=0; i<NUMFUNCIONES; i++ )
		myglfunc[i] = wglGetProcAddress( strs[i] );
}


