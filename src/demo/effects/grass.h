/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef GRASS_H
#define GRASS_H

#include "../../framework/framework.h"

/*!
    \file grass.h
    \brief Grass Class
*/

/*! Grass Types */
typedef enum EGrassType
{
    GRASS_SIN_WAVE          = 0,
    GRASS_COS_WAVE          = 1,
    GRASS_BEZIER_CURVE1     = 2,
    GRASS_BEZIER_CURVE2     = 3,
    GRASS_MUSIC_BEAT        = 4,
    GRASS_MAX_TYPES         = 5
    
} TGrassType;

/*! Grass Maximum Number of Segments */
#define GRASS_MAX_SEGMENTS 64

/*! Grass Class */
typedef struct SGrass
{
    /*! Segment */
    TRenderEntity *mSegment;
    /*! Active Segments */
    uint32 mActiveSegments;
    /*! Number of Segements */
    uint32 mNumSegments;
    /*! T */
    float mT;
    /*! TT */
    float mTT;
    /*! TTT */
    float mTTT;
    /*! Color */
    vec4 mColor;
    /*! Type */
    TGrassType mType;
    /*! World Transform */
    TMatrix4 mModelView;
    /*! Reference Count */
    uint32 mRefCount;
} TGrass;

/*! Constructor */
TGrass *GrassCreate(const float pX,             /*! Position on X Axis */
                    const float pY,             /*! Position on Y Axis */
                    const float pZ,             /*! Position on Z Axis */
                    const uint32 pNumSegments,  /*! Number of Grass Segments */
                    const TGrassType pType);    /*! Type of Grass */
/*! Clone */
TGrass *GrassClone(const TGrass *pGrass);
/*! Set Position */
void GrassSetPosition(TGrass *this, const float pX, const float pY, const float pZ);
/*! Set Type */
void GrassSetType(TGrass *this, const TGrassType pType);
/*! Set Number of Segments */
void GrassSetNumSegments(TGrass *this, const uint32 pNumSegments);
/*! Set Color */
void GrassSetColor(TGrass *this, const float pR, const float pG, const float pB, const float pA);
/*! Update */
void GrassUpdate(TGrass *this, const TUpdate *pUpdate);
/*! Draw */
void GrassDraw(const TGrass *this, const TRenderer *pRenderer, const TUpdate *pUpdate);
/*! Destructor */
void GrassDestroy(TGrass *this);

#endif
