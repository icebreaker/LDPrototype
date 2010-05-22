/* Copyright (c) 2010, Mihail Szabolcs */
#include "renderer.h"
#include "../framework/class.h"

/*!
    \file renderer.h
    \brief Renderer Class implementation
*/

void RendererBeginFrame(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void RendererEndFrame(void)
{
	glFinish();
	SDL_GL_SwapBuffers();
}

void RendererBegin2D(const uint32 pWidth, const uint32 pHeight)
{
    /*! get into 2D mode (ortho) */
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, pWidth, pHeight, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void RendererEnd2D(void)
{
    /*! get out of 2D mode */
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopMatrix();
}

void RendererResizeFrame(const uint32 pX, const uint32 pY, const uint32 pWidth, const uint32 pHeight)
{
	glViewport(pX, pY, pWidth, pHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(float)pWidth/(float)(pHeight),0.1f,RENDERER_MAX_FOV);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RendererSetupGeometry(const TGeom *pGeometry)
{
	glVertexPointer(3,GL_FLOAT,sizeof(TVertex),&pGeometry->mVerts[0].mPosition);
	glTexCoordPointer(2,GL_FLOAT,sizeof(TVertex),&pGeometry->mVerts[0].mTexCoord);
	glNormalPointer(GL_FLOAT,sizeof(TVertex),&pGeometry->mVerts[0].mNormal);
}

void RendererGeometryInstance(const TGeom *pGeometry)
{
	glDrawElements(GL_TRIANGLES, pGeometry->mNumTris*3, GL_UNSIGNED_SHORT, pGeometry->mTris);
}

void RendererGeometry(const TGeom *pGeometry)
{	
	RendererSetupGeometry(pGeometry);
	RendererGeometryInstance(pGeometry);
}

void RendererLoadMatrix(const TMatrix4 *pMatrix4)
{
    glLoadMatrixf(pMatrix4->m);
}

void RendererMultMatrix(const TMatrix4 *pMatrix4)
{
    glMultMatrixf(pMatrix4->m);
}

void RendererSaveMatrix(void)
{
    glPushMatrix();
}

void RendererRestoreMatrix(void)
{
    glPopMatrix();
}

void RendererSetBackColor(const float pR, const float pG, const float pB, const float pA)
{
    glClearColor(pR, pG, pB, pA);
}

void RendererSetColor(const float pR, const float pG, const float pB, const float pA)
{
    glColor4f(pR, pG, pB, pA);
}

void RendererSetDepthTest(const bool pState)
{
    if(pState) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
}

void RendererSetDepthMask(const bool pState)
{
    glDepthMask(pState);
}

void RendererSetBlending(const bool pState)
{
    if(pState) glEnable(GL_BLEND); else glDisable(GL_BLEND);
}

void RendererSetAdditiveBlending(void)
{
    RendererSetBlending(true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void RendererSetAlphaBlending(void)
{
    RendererSetBlending(true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RendererInit(const TConfig *pConfig)
{
    RendererSetBackColor(0.0f, 0.0f, 0.0f, 1.0f);
    
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    
    /*  
        glEnable(GL_CULL_FACE);
	    glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    */

	{
		glEnable(GL_MULTISAMPLE);
		
		int lBufs;
		int lSamples;
		glGetIntegerv(GL_SAMPLE_BUFFERS, &lBufs);
		glGetIntegerv(GL_SAMPLES, &lSamples);
		printf("Multi sampling: %d buffers and %d samples ...\n", lBufs, lSamples);
    }
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
}

void RendererShutdown(void)
{
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

TRenderer *RendererCreate(const TConfig *pConfig)
{
    CLASS_CREATE(TRenderer);
    
    this->mWidth = pConfig->mWidth;
    this->mHeight= pConfig->mHeight;
    	
    this->BeginFrame            = RendererBeginFrame;
	this->EndFrame              = RendererEndFrame;
	this->Begin2D               = RendererBegin2D;
	this->End2D                 = RendererEnd2D;
	this->ResizeFrame           = RendererResizeFrame;
	this->SetupGeometry         = RendererSetupGeometry;
	this->DrawGeometryInstance  = RendererGeometryInstance;
	this->DrawGeometry          = RendererGeometry;
	this->LoadMatrix            = RendererLoadMatrix;
	this->MultMatrix            = RendererMultMatrix;
	this->SaveMatrix            = RendererSaveMatrix;
	this->RestoreMatrix         = RendererRestoreMatrix;
	this->SetBackColor          = RendererSetBackColor;
	this->SetColor              = RendererSetColor;
	this->SetDepthTest          = RendererSetDepthTest;
	this->SetDepthMask          = RendererSetDepthMask;
	this->SetBlending           = RendererSetBlending;
	this->SetAdditiveBlending   = RendererSetAdditiveBlending;
	this->SetAlphaBlending      = RendererSetAlphaBlending;
	this->Init                  = RendererInit;
	this->Shutdown              = RendererShutdown;

	this->Init(pConfig);
	this->ResizeFrame(0, 0, this->mWidth, this->mHeight);
	
    this->mScreenshot = (uint8 *) malloc(this->mWidth * this->mHeight * 4);
	
	CLASS_INSTANCE();
}

bool RendererScreenshot(TRenderer *this, const char *pFileName)
{
    CLASS_THIS();
    glReadPixels( 0, 0, this->mWidth, this->mHeight, GL_BGRA, GL_UNSIGNED_BYTE, this->mScreenshot);
    /* glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->mScreenshot); */
    return WriteTGA(pFileName, this->mWidth, this->mHeight, this->mScreenshot);
}

void RendererDestroy(TRenderer *this)
{
    CLASS_DEINSTANCE();
        
    SAFE_FREE(this->mScreenshot);    
        
	this->Shutdown();
	
	CLASS_DESTROY(TRenderer);
}
