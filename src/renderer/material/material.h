/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../math/math.h"
#include "texture.h"
#include "shader.h"

/*!
    \file material.h
    \brief Material Class
*/

/*! Maximum Number of Textures in a Material */
#define MATERIAL_MAX_TEXTURES 4

/*! Material Class */
typedef struct SMaterial
{
    /*! Maximum of 4 Textures */
    TTexture *mTextures[MATERIAL_MAX_TEXTURES];
    /*! GLSL Shader */
    TShader *mShader;
    /*! GL Color */
    vec4 mColor;
    /*! Reference Count */
    uint32 mRefCount;
} TMaterial;

/*! Constructor */
TMaterial *MaterialCreate(void);
/*! Clone a Material */
TMaterial *MaterialClone(const TMaterial *this);
/*! Add Material Texture */
bool MaterialAddTexture(TMaterial *this, TTexture *pTexture);
/*! Add Material Shader */
bool MaterialAddShader(TMaterial *this, TShader *pShader);
/*! Set Material Color */
void MaterialSetColor(TMaterial *this, const float pR, const float pG, const float pB, const float pA);
/*! Set Material RGB */
void MaterialSetRGB(TMaterial *this, const float pR, const float pG, const float pB);
/*! Set Material Alpha */
void MaterialSetAlpha(TMaterial *this, const float pA);
/*! Bind Material */
void MaterialBegin(const TMaterial *this);
/*! UnBind Material */
void MaterialEnd(void);
/*! Destructor */
void MaterialDestroy(TMaterial *this);

#endif
