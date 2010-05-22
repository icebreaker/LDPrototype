/* Copyright (c) 2010, Mihail Szabolcs */
#include "music.h"

/*!
    \file music.c
    \brief Music Class implementation
*/

TMusic *MusicCreate(const char *pFileName)
{
    Mix_Music *lMusic = Mix_LoadMUS(pFileName);
 	if(lMusic==NULL)
	{
		printf("MusicCreate: %s ...\n", Mix_GetError());
		return NULL;
	}
	else
	{
		printf("MusicCreate: %s ...\n", pFileName);
	}

    CLASS_CREATE(TMusic);
    
    this->mTicks = 0;
    this->mMusicId = lMusic;
    Mix_SetPostMix(MusicCallback, (void *)this);
    
    CLASS_INSTANCE();
}

uint32 MusicGetTicks(const TMusic *this)
{
    CLASS_THIS();
    return this->mTicks;
}

void MusicPlay(const TMusic *this, const int pLoop)
{
    CLASS_THIS();
    Mix_PlayMusic(this->mMusicId, pLoop);
}

void MusicStop(void)
{
    Mix_HaltMusic();
}

bool MusicIsPlaying(void)
{
    return Mix_PlayingMusic();
}

void MusicFadeOut(const uint32 pSecs)
{
    Mix_FadeOutMusic(pSecs);
}

void MusicCallback(void *pData, uint8 *pMusic, int pLength)
{
    UNUSED(pMusic);
    UNUSED(pLength);
    
    if(Mix_PlayingMusic()==0)
        return;
    
    TMusic *lMusic = (TMusic *)pData;
    lMusic->mTicks++;
}

void MusicDestroy(TMusic *this)
{
    CLASS_DEINSTANCE();
    
    if(this->mMusicId!=NULL)
    {
        MusicStop();
        Mix_FreeMusic(this->mMusicId);
    }
    
    CLASS_DESTROY(TMusic);
}
