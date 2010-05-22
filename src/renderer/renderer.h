/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef RENDERER_H
#define RENDERER_H

#include "renderer_private.h"

/*!
    \file renderer.h
    \brief Renderer Class
*/

/*! Maximum Field of View */
#define RENDERER_MAX_FOV 3000.0f

/*! Renderer Class */
typedef struct SRenderer
{	
    /*! Begin a Frame */
	TRendererBeginFrame BeginFrame;
	/*! End a Frame */
	TRendererEndFrame EndFrame;
	/*! Enter 2D Mode */
	TRendererBegin2D Begin2D;
	/*! Exit 2D Mode */
	TRendererEnd2D End2D;
	/*! Resize a Frame (viewport and perspective) */
	TRendererResizeFrame ResizeFrame;
	/*! Setup Geometry (bind arrays / buffers, etc) */
	TRendererSetupGeometry SetupGeometry;
	/*! Draw an instance (glDrawElements) */
	TRendererDrawGeometryInstance DrawGeometryInstance;
	/*! Setup and DrawInstance */
	TRendererDrawGeometry DrawGeometry;
    /*! Load a matrix into the current GL_MODELVIEW */
	TRendererLoadMatrix LoadMatrix;
	/*! Mult a matrix with the current GL_MODELVIEW */
	TRendererMultMatrix MultMatrix;
	/*! Save matrix (glPushMatrix) */
    TRendererSaveMatrix SaveMatrix;
    /*! Restore matrix (glPopMatrix) */
	TRendererRestoreMatrix RestoreMatrix;
	/*! Set Background Color */
	TRendererSetBackColor SetBackColor;
	/*! Set Foreground Color */
	TRendererSetColor SetColor;
	/*! Set Depth Test */
	TRendererSetDepthTest SetDepthTest;
	/*! Set Depth Mask */
	TRendererSetDepthMask SetDepthMask;
	/*! Set Blending */
	TRendererSetBlending SetBlending;
	/*! Set Additive Blending */
	TRendererSetAdditiveBlending SetAdditiveBlending;
	/*! Set Alpha Blending */
	TRendererSetAlphaBlending SetAlphaBlending;
	/*! Init */
	TRendererInit Init;
	/*! Shutdown */
	TRendererShutdown Shutdown;
	/*! Screenshot data */
	uint8 *mScreenshot;
	/*! Screen Width */
	uint32 mWidth;
	/*! Screen Height */
	uint32 mHeight;
	/*! Reference Count */
	uint32 mRefCount;
} TRenderer;

/*! Constructor */
TRenderer *RendererCreate(const TConfig *pConfig);
/*! Screenshot */
bool RendererScreenshot(TRenderer *this, const char *pFileName);
/*! Destructor */
void RendererDestroy(TRenderer *this);

#endif
