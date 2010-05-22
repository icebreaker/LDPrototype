/* Copyright (c) 2010, Mihail Szabolcs */
#include "garden.h"
#include "resources.h"

/*!
    \file garden.c
    \brief Garden Class implementation
*/

TGarden *GardenCreate(const float pWidth, const float pHeight, const float pX, const float pY, const float pZ)
{
    /*! Create Ground Plane */
    TRenderEntity *lPlane = RenderEntityCreateQuadTextured(pWidth, pHeight, GARDEN_GROUND_TEXTURE);
    if(lPlane == NULL)
        return NULL;
        
    CLASS_CREATE(TGarden);

    Matrix4GetIdentity(&this->mModelView);
    Matrix4SetTranslate(&this->mModelView, pX, pY, pZ);

    this->mGround[0] = RenderEntityClone(lPlane);
    RenderEntityRotate(this->mGround[0], 90.0f, 1.0f, 0.0f, 0.0f);
    
    this->mGround[1] = RenderEntityClone(lPlane);
    RenderEntityRotate(this->mGround[1],-90.0f, 1.0f, 0.0f, 0.0f);
    
    RenderEntityDestroy(lPlane);
        
    /*! Dummy Grass which will be cloned as necessary */
    TGrass *lGrass = GrassCreate(0.0f, 0.0f, 0.0f, 0, GRASS_SIN_WAVE);
    if(lGrass!=NULL)
    {    
        int i,j;
        
        vec2 lOffsets[GARDEN_MAX_GRASS_RINGS] = 
        {
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        };
        
        for(j=0;j<GARDEN_MAX_GRASS_RINGS;j++)
        for(i=0;i<GARDEN_MAX_GRASS_LINES;i++)
        {
            TGrass *lClone = GrassClone(lGrass);
            
            float lAngle = i * (2.0*M_PI/GARDEN_MAX_GRASS_LINES);
            float lX = cos(lAngle)*(15.0f - (j*5));
            float lZ = sin(lAngle)*(15.0f - (j*5));
                        
            GrassSetPosition(lClone, lX + lOffsets[j][0], 0.0f, lZ + lOffsets[j][1]);
            
            //! Random Type
            GrassSetType(lClone, RANDOM(GRASS_MAX_TYPES));
            
            //! Random Number of Segments
            GrassSetNumSegments(lClone, RANDOM(GRASS_MAX_SEGMENTS)+16);
            
            //! Inner Ring is Red
            if(j == GARDEN_MAX_GRASS_RINGS-1)
            {
                GrassSetColor(lClone, 0.8f, 0.0f, 0.0f, 1.0f);
            }
            
            this->mGrass[j][i] = lClone;
        }
        
        GrassDestroy(lGrass);
    }
    else
    {
        printf("Garden: grass couldn't be created for some reason. Crash is ahead!\n");
    }

    CLASS_INSTANCE();
}

void GardenUpdate(TGarden *this, const TUpdate *pUpdate)
{
    CLASS_THIS();
    assert(pUpdate!=NULL);
    
    float lDeltaMove = (pUpdate->mDeltaTime*0.001f);
    int lSex = pUpdate->mElapsedTime / 1000;
    
    RenderEntityRotate(this->mGround[0],  lDeltaMove*21, 0.0f, 0.0f, 1.0f);
    RenderEntityRotate(this->mGround[1], -lDeltaMove*12, 0.0f, 0.0f, 1.0f);

    //float lDelta = cos(pUpdate->mTime * 0.005f);
    
   // RenderEntitySetPosition(this->mGround[0], 0.0f, lDelta, 0.0f);
   // RenderEntitySetPosition(this->mGround[1], 0.0f, lDelta, 0.0f);
   
    int i,j;
    static int k=1;
    
    if(lSex<20)
        return;
    
    if(lSex>60&&k==1)
        k=0;
    
    for(j=0;j<GARDEN_MAX_GRASS_RINGS-k;j++)
    for(i=0;i<GARDEN_MAX_GRASS_LINES;i++)
        GrassUpdate(this->mGrass[j][i], pUpdate);
}

void GardenDraw(const TGarden *this, const TRenderer *pRenderer, const TUpdate *pUpdate)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
    
    pRenderer->SaveMatrix();
    pRenderer->MultMatrix(&this->mModelView);

    int i,j;
    for(i=0;i<2;i++)
    {
        RenderEntitySetPosition(this->mGround[0], 0.0f, i*30.0f, 0.0f);
        RenderEntitySetPosition(this->mGround[1], 0.0f, i*30.0f, 0.0f);
    
        MaterialSetColor(this->mGround[0]->mMaterial, 0.8f, 0.8f, 0.8f, 0.6f);
        RenderEntityDraw(this->mGround[0], pRenderer);
    
        MaterialSetColor(this->mGround[1]->mMaterial, 1.0f, 1.0f, 1.0f, 0.6f);
        RenderEntityDraw(this->mGround[1], pRenderer);
    }
    
    for(j=0;j<GARDEN_MAX_GRASS_RINGS;j++)
    for(i=0;i<GARDEN_MAX_GRASS_LINES;i++)
        GrassDraw(this->mGrass[j][i], pRenderer, pUpdate);

    pRenderer->RestoreMatrix();
}

void GardenDestroy(TGarden *this)
{
    CLASS_DEINSTANCE();
    
    RenderEntityDestroy(this->mGround[0]);
    RenderEntityDestroy(this->mGround[1]);
    
    int i,j;
    
    for(j=0;j<GARDEN_MAX_GRASS_RINGS;j++)
    for(i=0;i<GARDEN_MAX_GRASS_LINES;i++)
        GrassDestroy(this->mGrass[j][i]); 
    
    CLASS_DESTROY(TGarden);
}

