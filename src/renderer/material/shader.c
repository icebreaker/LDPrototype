/* Copyright (c) 2010, Mihail Szabolcs */
#include "shader.h"
#include "../../framework/class.h"

/*!
    \file shader.c
    \brief Shader Class implementation
*/

TShader *ShaderCreate(const char *pVertexShader, const char *pPixelShader)
{
    char *lVertexSource = NULL;
    char *lPixelSource = NULL;
    
    if(pVertexShader!=NULL)
    {
        lVertexSource = GetFileContents(pVertexShader);
        if(lVertexSource == NULL)
            return NULL;
    }
        
    if(pPixelShader!=NULL)
    {
        lPixelSource = GetFileContents(pPixelShader);
        if(lPixelSource == NULL)
        {
            SAFE_FREE(lVertexSource);
            return NULL;
        }
    }

    TShader *this = ShaderCreateFromSource(lVertexSource,lPixelSource);
    
    SAFE_FREE(lVertexSource);
    SAFE_FREE(lPixelSource);

    CLASS_INSTANCE();
}

TShader *ShaderCreateFromSource(const char *pVertexSource, const char *pPixelSource)
{
    CLASS_CREATE(TShader);
    
    if(pVertexSource!=NULL)
    {
        this->mVertexShaderId = _ShaderCreateFromSource(GL_VERTEX_SHADER, pVertexSource);
        if(this->mVertexShaderId == 0)
        {
            ShaderDestroy(this);
            return NULL;
        }
    }
    else
    {
        this->mVertexShaderId = 0;
    }
    
    if(pPixelSource!=NULL)
    {
        this->mPixelShaderId = _ShaderCreateFromSource(GL_FRAGMENT_SHADER, pPixelSource);
        if(this->mPixelShaderId == 0)
        {
            ShaderDestroy(this);
            return NULL;
        }
    }
    else
    {
       this->mPixelShaderId = 0;
    }

    this->mProgramId = glCreateProgram();
    
    if(this->mVertexShaderId)
        glAttachShader(this->mProgramId, this->mVertexShaderId);
    if(this->mPixelShaderId)
        glAttachShader(this->mProgramId, this->mPixelShaderId);
        
    glLinkProgram(this->mProgramId);
    
    const char *lError = _ShaderGetProgramLog(this->mProgramId);
    if(lError!=NULL)
    {
        printf("ShaderCreateFromSource: %s\n",lError);
        ShaderDestroy(this);
        return NULL;
    }
    
    CLASS_INSTANCE();
}

void ShaderBegin(const TShader *this)
{
    CLASS_THIS();
    glUseProgram(this->mProgramId);
}

void ShaderEnd(void)
{
    glUseProgram(0);
}

void ShaderSetTime(TShader *this, const float pTime)
{
    CLASS_THIS();
    glUniform1f(glGetUniformLocation(this->mProgramId,"time"), pTime);   
}

void ShaderSetCameraPos(TShader *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    glUniform3f(glGetUniformLocation(this->mProgramId,"camera"), pX, pY, pZ);
}

void ShaderSetUniform1i(TShader *this, const char *pName, const uint32 pNumber)
{
    CLASS_THIS();
    glUniform1i(glGetUniformLocation(this->mProgramId,pName), pNumber);
}

void ShaderDestroy(TShader *this)
{
    CLASS_DEINSTANCE();
        
    ShaderEnd();    
        
    if(this->mProgramId)
    {
        if(this->mVertexShaderId)
            glDetachShader(this->mProgramId, this->mVertexShaderId);

        if(this->mPixelShaderId)
            glDetachShader(this->mProgramId, this->mPixelShaderId);

        glDeleteProgram(this->mProgramId);
    }

    if(this->mVertexShaderId)
        glDeleteShader(this->mVertexShaderId);

    if(this->mPixelShaderId)
        glDeleteShader(this->mPixelShaderId);
        
    CLASS_DESTROY(TShader);
}

const char *_ShaderGetShaderLog(uint32 pShaderId)
{
    int lParam = 0;
    
    glGetShaderiv(pShaderId, GL_COMPILE_STATUS, &lParam);
    if(lParam == GL_TRUE)
        return NULL;
    
    glGetShaderiv(pShaderId, GL_INFO_LOG_LENGTH, &lParam);
    if(lParam > 0)
    {
    	int lNumChars  = 0;
        char *lLogText = (char *) malloc(lParam);
        glGetShaderInfoLog(pShaderId, lParam, &lNumChars, lLogText);
        return lLogText;
    }
    
    return NULL;
}

const char *_ShaderGetProgramLog(uint32 pProgramId)
{
    int lParam = 0;

    glGetProgramiv(pProgramId, GL_LINK_STATUS, &lParam);
    if(lParam == GL_TRUE)
        return NULL;
    
    glGetProgramiv(pProgramId, GL_INFO_LOG_LENGTH, &lParam);
    if(lParam > 0)
    {
    	int lNumChars  = 0;
        char *lLogText = (char *) malloc(lParam);
        glGetProgramInfoLog(pProgramId, lParam, &lNumChars, lLogText);
        return lLogText;
    }
    
    return NULL;
}

uint32 _ShaderCreateFromSource(uint32 pType, const char *pSource)
{
    uint32 lShaderId = glCreateShader(pType);

    glShaderSource(lShaderId, 1, &pSource, NULL);
    glCompileShader(lShaderId);
    
    const char *lError = _ShaderGetShaderLog(lShaderId);
    if(lError!=NULL)
    {
        glDeleteShader(lShaderId);
        printf("_ShaderCreateFromSource: %s\n",lError);
        return 0;
    }

    return lShaderId;
}

