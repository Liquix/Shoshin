#ifndef _EXTENSIONES_H_
#define _EXTENSIONES_H_

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include "glext.h"

#ifdef DEBUG
#define NUMFUNCIONES 7
#else
#define NUMFUNCIONES 5
#endif

#pragma code_seg(".bindings")
extern void *myglfunc[NUMFUNCIONES];
#define oglCreateShaderProgramv         ((PFNGLCREATESHADERPROGRAMVPROC)myglfunc[0])
#define oglGenProgramPipelines          ((PFNGLGENPROGRAMPIPELINESPROC)myglfunc[1])
#define oglBindProgramPipeline          ((PFNGLBINDPROGRAMPIPELINEPROC)myglfunc[2])
#define oglUseProgramStages             ((PFNGLUSEPROGRAMSTAGESPROC)myglfunc[3])
#define oglProgramUniform4fv            ((PFNGLPROGRAMUNIFORM4FVPROC)myglfunc[4])
/*
#ifdef DEBUG
#define oglGetProgramiv          ((PFNGLGETPROGRAMIVPROC)myglfunc[5])
#define oglGetProgramInfoLog     ((PFNGLGETPROGRAMINFOLOGPROC)myglfunc[6])
#endif*/

void EXT_Init();

#endif
