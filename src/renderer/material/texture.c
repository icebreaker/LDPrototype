/* Copyright (c) 2010, Mihail Szabolcs */
#include "texture.h"
#include "../../framework/class.h"

/*!
    \file texture.c
    \brief Texture Class implementation
*/

TTexture *TextureCreate(const char *pFileName, bool pMipMaps)
{
	SDL_Surface *lImage = IMG_Load(pFileName);
	if(lImage==NULL)
	{
		printf("TextureCreate: %s ...\n", IMG_GetError());
		return NULL;
	}
	else
	{
		printf("TextureCreate: %s ...\n", pFileName);
	}

	/* Flip Image */
	{
		uint8 *lTmpBuf = (uint8 *) malloc(lImage->pitch * sizeof(uint8));
		uint8 *lRowHi = (uint8 *) lImage->pixels;
		uint8 *lRowLo = lRowHi + ((lImage->h - 1) * lImage->pitch);

		int lMiddle = (int) lImage->h/2; int i;
		for(i=0;i<lMiddle;i++)
		{
			memcpy(lTmpBuf, lRowHi, lImage->pitch);
			memcpy(lRowHi, 	lRowLo, lImage->pitch);
			memcpy(lRowLo, 	lTmpBuf,lImage->pitch);

			lRowHi += lImage->pitch;
			lRowLo -= lImage->pitch;
		}

		free(lTmpBuf);
	}

	CLASS_CREATE(TTexture);
	
    this->mHash = hash(pFileName);
    this->mWidth = lImage->w;
    this->mHeight= lImage->h;

	glGenTextures(1, &this->mTextureId);
	
	TextureBegin(this);

    if(pMipMaps)
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    else
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    /*glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );*/

#ifdef GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#else
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#endif

	/* Determine Image Properties and Upload the Texture Data */
	{
		uint32 lFormat = GL_RGBA;
	
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		uint32 lRmask = 0xff000000;
		#else
		uint32 lRmask = 0x000000ff;
		#endif

		switch(lImage->format->BytesPerPixel)
		{
			case 4: 
				lFormat = (lImage->format->Rmask == lRmask) ? GL_RGBA : GL_BGRA;
				break;

			case 3:
			default:
				lFormat = (lImage->format->Rmask == lRmask) ? GL_RGB : GL_BGR;
				break;
		}

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, lImage->w, lImage->h, 0,
					  lFormat, GL_UNSIGNED_BYTE, lImage->pixels );
		
		if(pMipMaps)
		{			
	        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, lImage->w, lImage->h, lFormat, GL_UNSIGNED_BYTE, lImage->pixels);
	    }
	}
	
	TextureEnd();

	SDL_FreeSurface(lImage);
	CLASS_INSTANCE();
}

TTexture *TextureCreateEmpty(const uint32 pWidth, const uint32 pHeight)
{
    CLASS_CREATE(TTexture);

    glGenTextures(1, &this->mTextureId);
    
    TextureBegin(this);
    /*glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );*/
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
#ifdef GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#else
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#endif
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    TextureEnd();
    
    CLASS_INSTANCE();
}

void TextureBegin(const TTexture *this)
{
	CLASS_THIS();
	glBindTexture(GL_TEXTURE_2D, this->mTextureId);	
}

void TextureEnd(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureDestroy(TTexture *this)
{
    CLASS_DEINSTANCE();
			
    if(this->mTextureId)
    {
    	TextureEnd();
    	glDeleteTextures(1, &this->mTextureId);
    }
    
    CLASS_DESTROY(TTexture);
}
