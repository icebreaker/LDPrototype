/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef GARDEN_H
#define GARDEN_H

#include "grass.h"

/*! 
    \file garden.h
    \brief Garden Class
*/

/*! Maximum number of grass rings to grow in a garden */
#define GARDEN_MAX_GRASS_RINGS 3
/*! Maximum number of grass lines to grow in a garden */
#define GARDEN_MAX_GRASS_LINES 20

/*! 
    Garden Class
    Floating Garden in the skies.
*/
typedef struct SGarden
{
    /*! Ground */
    TRenderEntity *mGround[2];
    /*! Grass */
    TGrass *mGrass[GARDEN_MAX_GRASS_RINGS][GARDEN_MAX_GRASS_LINES];
    /*! World Transform */
    TMatrix4 mModelView;
    /*! Reference Count */
    uint32 mRefCount;
} TGarden;

/*! Constructor */
TGarden *GardenCreate(const float pWidth, const float pHeight, const float pX, const float pY, const float pZ);
/*! Update */
void GardenUpdate(TGarden *this, const TUpdate *pUpdate);
/*! Draw */
void GardenDraw(const TGarden *this, const TRenderer *pRenderer, const TUpdate *pUpdate);
/*! Destructor */
void GardenDestroy(TGarden *this);

#endif
