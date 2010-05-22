/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef SHADER_H
#define SHADER_H

#include "../../sys/types.h"

/*!
    \file shader.h
    \brief Shader Class
*/

/*! Shader Class */
typedef struct SShader
{
	/*! OpenGL Vertex Shader Id */
	uint32 mVertexShaderId;
	/*! OpenGL Pixel Shader Id */
	uint32 mPixelShaderId;
	/*! OpenGL Shader Program Id */
	uint32 mProgramId;
	/*! Reference Count */
	uint32 mRefCount;
} TShader;

/*! Constructor */
TShader *ShaderCreate(const char *pVertexShader, const char *pPixelShader);
/*! Constructor */
TShader *ShaderCreateFromSource(const char *pVertexSource, const char *pPixelSource);
/*! Bind Shader */
void ShaderBegin(const TShader *this);
/*! UnBind Shader */
void ShaderEnd(void);
/*! Set Time Uniform */
void ShaderSetTime(TShader *this, const float pTime);
/*! Set Camera Uniform */
void ShaderSetCameraPos(TShader *this, const float pX, const float pY, const float pZ);
/*! Set Integer Uniform */
void ShaderSetUniform1i(TShader *this, const char *pName, const uint32 pNumber);
/*! Destructor */
void ShaderDestroy(TShader *this);
/*! Private Get Shader Compile Log */
const char *_ShaderGetShaderLog(uint32 pShaderId);
/*! Private Get Program Compile Log */
const char *_ShaderGetProgramLog(uint32 pProgramId);
/*! Private Create a Shader From Source */
uint32 _ShaderCreateFromSource(uint32 pType, const char *pSource);

#endif
