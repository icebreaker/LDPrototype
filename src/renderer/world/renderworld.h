/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef RENDERERWORLD_H
#define RENDERERWORLD_H

#include "../renderer.h"
#include "../geom/geom.h"
#include "camera.h"

/*!
    \file renderworld.h
    \brief Render World & Entity class
*/

/*! Render Entity Class */
typedef struct SRenderEntity
{
    /*! Override Default Material */
    TMaterial *mMaterial;
    /*! Geometry To Draw */
	TGeom *mGeom;
	/*! World Transform for this entity */
	TMatrix4 mModelView;
	/*! Width of a 2D Entity */
	uint32 mWidth;
	/*! Height of a 2D Entity */
	uint32 mHeight;
    /*! Reference Count */
    uint32 mRefCount;
} TRenderEntity;

/*! Constructor */
TRenderEntity *RenderEntityCreate(void);
/*! Constructor */
TRenderEntity *RenderEntityCreateCube(const uint32 pSizeX, const uint32 pSizeY, const uint32 pSizeZ);
/*! Constructor */
TRenderEntity *RenderEntityCreateCubeTextured(const uint32 pSizeX, const uint32 pSizeY, const uint32 pSizeZ, const char *pFileName);
/*! Constrcutor */
TRenderEntity *RenderEntityCreateQuadTextured(const uint32 pSizeX, const uint32 pSizeY, const char *pFileName);
/*! Constructor */
TRenderEntity *RenderEntityCreate2D(const uint32 pWidth, const uint32 pHeight, const char *pFileName);
/*! Clone Entity */
TRenderEntity *RenderEntityClone(const TRenderEntity *this);
/*! Clone a 2D Entity */
TRenderEntity *RenderEntityClone2D(const TRenderEntity *this);
/*! Set Material */
void RenderEntitySetMaterial(TRenderEntity *this, TMaterial *pMaterial);
/*! Set Geometry */
void RenderEntitySetGeometry(TRenderEntity *this, TGeom *pGeom);
/*! Set Position */
void RenderEntitySetPosition(TRenderEntity *this, const float pX, const float pY, const float pZ);
/*! Move (position) */
void RenderEntityMove(TRenderEntity *this, const float pX, const float pY, const float pZ);
/*! Move (position) 2 */
void RenderEntityMove2(TRenderEntity *this, const float pX, const float pY, const float pZ);
/*! Move in 2D */
void RenderEntityMove2D(TRenderEntity *this, const float pX, const float pY);
/*! Set Position in 2D */
void RenderEntitySetPosition2D(TRenderEntity *this, const float pX, const float pY);
/*! Rotate */
void RenderEntityRotate(TRenderEntity *this, const float pAngle, const float pX, const float pY, const float pZ);
/*! Rotate in 2D */
void RenderEntityRotate2D(TRenderEntity *this, const float pAngle);
/*! Reset Position and Transform */
void RenderEntityReset(TRenderEntity *this);
/*! Begin Draw */
void RenderEntityDrawBegin(const TRenderEntity *this, const TRenderer *pRenderer);
/*! Draw */
void RenderEntityDrawGeom(const TRenderEntity *this, const TRenderer *pRenderer);
/*! End Draw */
void RenderEntityDrawEnd(const TRenderEntity *this, const TRenderer *pRenderer);
/*! Draw */
void RenderEntityDraw(const TRenderEntity *this, const TRenderer *pRenderer);
/*! Draw Cached */
void RenderEntityDrawCached(const TRenderEntity *this, const TRenderer *pRenderer);
/*! Flush Material and Geometry Caches */
void RenderEntityFlush(void);
/*! Destructor */
void RenderEntityDestroy(TRenderEntity *this);

/*! Maximum number of Render Entities in a Render World */
#define RENDERWORLD_MAX_RENDERENTITIES 2048

/*! Render World Class */
typedef struct SRenderWorld
{
    /*! Render World Entities */
	TRenderEntity *mEntities[ RENDERWORLD_MAX_RENDERENTITIES ];
	/*! Render World Camera */
    TCamera *mCamera;
    /*! Reference Count */
    uint32 mRefCount;
} TRenderWorld;

/*! Constructor */
TRenderWorld *RenderWorldCreate(void);
/*! Set RenderWorld Camera */
void RenderWorldSetCamera(TRenderWorld *this, TCamera *pCamera);
/*! Add a RenderWorld Entity */
bool RenderWorldAddEntity(TRenderWorld *this, TRenderEntity *pRenderEntity);
/*! Draw RenderWorld */
void RenderWorldDraw(const TRenderWorld *this, const TRenderer *pRenderer);
/*! Destructor */
void RenderWorldDestroy(TRenderWorld *this);

#endif
