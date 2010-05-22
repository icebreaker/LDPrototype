/* Copyright (c) 2010, Mihail Szabolcs */
#include "grass.h"
#include "resources.h"

/*!
    \file Grass.c
    \brief Grass Class implementation
*/

TGrass *GrassCreate(const float pX,
                    const float pY,
                    const float pZ,
                    const uint32 pNumSegments,
                    const TGrassType pType)
{
    TRenderEntity *lSegment = RenderEntityCreateQuadTextured(1.0f, 1.0f, FLARE_TEXTURE);
    if(lSegment == NULL)
        return NULL;
        
    TShader *lShader = ShaderCreate(BILLBOARDING_SHADER_VS, NULL);

    if(lShader!=NULL)
    {
        MaterialAddShader(lSegment->mMaterial, lShader);
        ShaderDestroy(lShader);
        lShader = 0;
    }

    CLASS_CREATE(TGrass);
    
    Matrix4GetIdentity(&this->mModelView);
    this->mSegment = lSegment;
    this->mTTT = RANDOM(512)+10.0f;

    GrassSetColor(this, 1.0f, 1.0f, 1.0f, 1.0f);
    GrassSetPosition(this, pX, pY, pZ);
    GrassSetNumSegments(this, pNumSegments);
    GrassSetType(this, pType);
    
    CLASS_INSTANCE();
}

TGrass *GrassClone(const TGrass *pGrass)
{
    CLASS_CREATE(TGrass);
    
    Matrix4Copy(&this->mModelView, &pGrass->mModelView);
    this->mSegment = pGrass->mSegment;
    this->mTTT = RANDOM(512)+10.0f;
    this->mSegment->mRefCount++;
    
    int i;
    for(i=0;i<4;i++)
        this->mColor[i] = pGrass->mColor[i];
    
    GrassSetNumSegments(this, pGrass->mNumSegments);
    GrassSetType(this, pGrass->mType);
    
    CLASS_INSTANCE();
}

void GrassSetPosition(TGrass *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    Matrix4SetTranslate(&this->mModelView, pX, pY, pZ);
}

void GrassSetType(TGrass *this, const TGrassType pType)
{
    CLASS_THIS();
    this->mType = pType;
}

void GrassSetNumSegments(TGrass *this, const uint32 pNumSegments)
{
    CLASS_THIS();
    this->mNumSegments = pNumSegments;   
}

void GrassSetColor(TGrass *this, const float pR, const float pG, const float pB, const float pA)
{
    CLASS_THIS();
    this->mColor[0] = pR;
    this->mColor[1] = pG;
    this->mColor[2] = pB;
    this->mColor[3] = pA;
}

void GrassUpdate(TGrass *this, const TUpdate *pUpdate)
{
    CLASS_THIS();
    assert(pUpdate!=NULL);
        
    if(this->mActiveSegments == this->mNumSegments)
        return;
        
    if(++this->mTT>this->mTTT)
    {
        this->mT += 0.01f;
        this->mActiveSegments++;
    }
}

void GrassDraw(const TGrass *this, const TRenderer *pRenderer, const TUpdate *pUpdate)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
    
    int lSex = pUpdate->mElapsedTime / 1000;
    
    pRenderer->SaveMatrix();
    pRenderer->MultMatrix(&this->mModelView);
    
    vec2 p0,p1,p2,p3;

    VEC2SET(p0,0.0f, 0.0f);
    VEC2SET(p1,0.0f, 4.0f);
    VEC2SET(p2,0.0f, 4.0f);
    VEC2SET(p3,0.0f, 8.0f);    
    
    MaterialSetColor(this->mSegment->mMaterial, 
                     this->mColor[0],
                     this->mColor[1],
                     this->mColor[2],
                     this->mColor[3]);
    
    float t;
    for(t=0.0f;t<=1.0f;t+=0.01f)
    {
        if(t == this->mT)
            break;
            
        float lRandX = 1.0f;
        float lRandY = 1.0f;
        
        if(lSex>80&&lSex<100)
        {
            lRandX = RANDOM(20);
            lRandY = RANDOM(20);
        }
            
        float lDeltaSin = sin(pUpdate->mTime * 0.001f) * lRandX;
        float lDeltaCos = cos(pUpdate->mTime * 0.001f) * lRandY;
            
        float x = BC(p0[0],p1[0]+lDeltaSin,p2[0]+lDeltaCos,p3[0],t);
        float y = BC(p0[1],p1[1],p2[1],p3[1],t);
        
        RenderEntitySetPosition2D(this->mSegment, x, y);
        RenderEntityDrawCached(this->mSegment, pRenderer);
    }
    
    //! Flush Cache
    RenderEntityFlush();

    pRenderer->RestoreMatrix();
}

void GrassDestroy(TGrass *this)
{
    CLASS_DEINSTANCE();
    
    RenderEntityDestroy(this->mSegment);
    
    CLASS_DESTROY(TGrass);
}


