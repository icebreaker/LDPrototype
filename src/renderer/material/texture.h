/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../sys/types.h"

/*!
    \file texture.h
    \brief Texture Class
*/

/*! Texture Class */
typedef struct STexture
{
	/*! Texture Width */
	uint32 mWidth;
	/*! Texture Height */
	uint32 mHeight;
	/*! OpenGL Texture ID */
	uint32 mTextureId;
	/*! FileName Hash */
	uint32 mHash;
	/*! Reference Count */
	uint32 mRefCount;
} TTexture;

/*! Constructor */
TTexture *TextureCreate(const char *pFileName, bool pMipMaps);
/*! Constructor */
TTexture *TextureCreateEmpty(const uint32 pWidth, const uint32 pHeight);
/*! Bind Texture */
void TextureBegin(const TTexture *this);
/*! UnBind Texture */
void TextureEnd(void);
/*! Destructor */
void TextureDestroy(TTexture *this);

#endif
