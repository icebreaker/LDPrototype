/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef MUSIC_H
#define MUSIC_H

#include "../framework/class.h"

/*!
    \file music.h
    \brief Music Class
*/

/*! Music Class */
typedef struct SMusic
{
    /*! SDL_Mixer Handle */
    Mix_Music *mMusicId;
    /*! Music Ticks / Position */
    uint32 mTicks;
    /*! Reference Count */
    uint32 mRefCount;
} TMusic;

/*! Constructor */
TMusic *MusicCreate(const char *pFileName);
/*! Get Music Ticks */
uint32 MusicGetTicks(const TMusic *this);
/*! Play Music */
void MusicPlay(const TMusic *this, const int pLoop);
/*! Stop Music */
void MusicStop(void);
/*! Is Playing */
bool MusicIsPlaying(void);
/*! Fade Out */
void MusicFadeOut(const uint32 pSecs);
/*! Music Callback */
void MusicCallback(void *pData, uint8 *pMusic, int pLength);
/*! Destructor */
void MusicDestroy(TMusic *this);

#endif
