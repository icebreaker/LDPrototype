/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef FRAMEWORK_PRIVATE_H
#define FRAMEWORK_PRIVATE_H

/*!
    \file framework_private.h
    \brief Private Framework Structures
*/

#include "../sys/types.h"

/* Frame Update Structure */
typedef struct SUpdate
{
    uint32 mStartTime;
	uint32 mTime; 
	uint32 mLastTime;
	uint32 mDeltaTime;
	uint32 mElapsedTime;
	
	bool mKeys[256];
	
	uint32 mMouseX;
	uint32 mMouseY;

	uint32 mMouseDeltaX;
	uint32 mMouseDeltaY;
	
} TUpdate;

/* Configuration Structure */
typedef struct SConfig
{
	uint32 mWidth;
	uint32 mHeight;
	uint32 mBpp;
	
	bool mFullScreen;

	const char *mTitle;

	uint32 mHz;
	uint32 mVSync;
	uint32 mMultiSampling;
    
	bool mGrabInput;
    bool mHideCursor;
    bool mCenterCursor;
    
    bool mAudio;
    
	
} TConfig;

#endif
