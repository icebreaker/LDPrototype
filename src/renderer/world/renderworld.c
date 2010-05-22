/* Copyright (c) 2010, Mihail Szabolcs */
#include "renderworld.h"
#include "../geom/geom_quad.h"
#include "../geom/geom_cube.h"
#include "../material/texture.h"
#include "../../framework/class.h"

/*!
    \file renderworld.c
    \brief Render World & Entity implementation
*/

TRenderEntity *RenderEntityCreate(void)
{
    CLASS_CREATE(TRenderEntity);
    
    this->mMaterial = NULL;
    this->mGeom = NULL;
    
    RenderEntityReset(this);
    
    CLASS_INSTANCE();
}

TRenderEntity *RenderEntityCreateCube(const uint32 pSizeX, const uint32 pSizeY, const uint32 pSizeZ)
{        
    TGeom *lCube = GeomCreateCube(pSizeX, pSizeY, pSizeZ);
    
    TMaterial *lMaterial = MaterialCreate(); 
    GeomSetMaterial(lCube, lMaterial);
    MaterialDestroy(lMaterial);
    
    TRenderEntity *this = RenderEntityCreate();
    RenderEntitySetGeometry(this, lCube);
    
    GeomDestroy(lCube);
    
    CLASS_INSTANCE();
}

TRenderEntity *RenderEntityCreateQuadTextured(const uint32 pSizeX, const uint32 pSizeY, const char *pFileName)
{
    TTexture *lTexture = TextureCreate(pFileName, false);
    if(lTexture==NULL)
        return NULL;
        
    TMaterial *lMaterial = MaterialCreate();
    MaterialAddTexture(lMaterial, lTexture);
        
    TGeom *lQuad = GeomCreateQuad(pSizeX, pSizeY);
    GeomSetMaterial(lQuad, lMaterial);
    
    GeomSetTexCoord(lQuad, 0, 0.0f, 0.0f);
	GeomSetTexCoord(lQuad, 1, 1.0f, 0.0f);
	GeomSetTexCoord(lQuad, 2, 1.0f, 1.0f);
	GeomSetTexCoord(lQuad, 3, 0.0f, 1.0f);
        
    TRenderEntity *this = RenderEntityCreate();
    RenderEntitySetGeometry(this, lQuad);
    
    TextureDestroy(lTexture);
    MaterialDestroy(lMaterial);
    GeomDestroy(lQuad);
    
    CLASS_INSTANCE();
}

TRenderEntity *RenderEntityCreateCubeTextured(const uint32 pSizeX, const uint32 pSizeY, const uint32 pSizeZ, const char *pFileName)
{
    TTexture *lTexture = TextureCreate(pFileName, false);
    if(lTexture==NULL)
        return NULL;
        
    TMaterial *lMaterial = MaterialCreate();
    MaterialAddTexture(lMaterial, lTexture);
        
    TGeom *lCube = GeomCreateCube(pSizeX, pSizeY, pSizeZ);
    GeomSetMaterial(lCube, lMaterial);
        
    TRenderEntity *this = RenderEntityCreate();
    RenderEntitySetGeometry(this, lCube);
    
    TextureDestroy(lTexture);
    MaterialDestroy(lMaterial);
    GeomDestroy(lCube);
    
    CLASS_INSTANCE();
}

TRenderEntity *RenderEntityCreate2D(const uint32 pWidth, const uint32 pHeight, const char *pFileName)
{
    TTexture *lTexture = TextureCreate(pFileName, false);
    if(lTexture==NULL)
        return NULL;
        
    TMaterial *lMaterial = MaterialCreate();
    MaterialAddTexture(lMaterial, lTexture);
        
    TGeom *lQuad = GeomCreateQuad(pWidth, pHeight);
    GeomSetMaterial(lQuad, lMaterial);
        
    TRenderEntity *this = RenderEntityCreate();
    RenderEntitySetGeometry(this, lQuad);
    RenderEntityMove2D(this, pWidth/2.0f, pHeight/2.0f);
    
    this->mWidth = pWidth;
    this->mHeight= pHeight;
        
    TextureDestroy(lTexture);
    MaterialDestroy(lMaterial);
    GeomDestroy(lQuad);
    
    CLASS_INSTANCE();
}

TRenderEntity *RenderEntityClone(const TRenderEntity *this)
{
    CLASS_THIS();
    
    TRenderEntity *lClone = RenderEntityCreate();
    RenderEntitySetGeometry(lClone, this->mGeom);
    //RenderEntitySetMaterial(lClone, MaterialClone(lClone->mMaterial));
    
    return lClone;
}

TRenderEntity *RenderEntityClone2D(const TRenderEntity *this)
{
    CLASS_THIS();
    
    TRenderEntity *lClone = RenderEntityClone(this);
    RenderEntityMove2D(lClone, this->mWidth/2.0f, this->mHeight/2.0f);
  
    lClone->mWidth = this->mWidth;
    lClone->mHeight= this->mHeight;
    
    return lClone;
}

void RenderEntitySetMaterial(TRenderEntity *this, TMaterial *pMaterial)
{
    CLASS_THIS();
    assert(pMaterial!=NULL);
    
    CLASS_ADDREF(pMaterial);
    
    MaterialDestroy(this->mMaterial);
    this->mMaterial = pMaterial;
}

void RenderEntitySetGeometry(TRenderEntity *this, TGeom *pGeom)
{
    CLASS_THIS();
    assert(pGeom!=NULL);
    
    RenderEntitySetMaterial(this, pGeom->mMaterial);
    
    CLASS_ADDREF(pGeom);
    
    GeomDestroy(this->mGeom);
    this->mGeom = pGeom;
}

void RenderEntitySetPosition(TRenderEntity *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    Matrix4SetTranslate(&this->mModelView, pX, pY, pZ);
}

void RenderEntityMove(TRenderEntity *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    Matrix4Translate(&this->mModelView, pX, pY, pZ);
}

void RenderEntityMove2(TRenderEntity *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    Matrix4AddTranslate(&this->mModelView, pX, pY, pZ);
}

void RenderEntityMove2D(TRenderEntity *this, const float pX, const float pY)
{
    CLASS_THIS();
    Matrix4Translate(&this->mModelView, pX, pY, 0.0f);
}

void RenderEntitySetPosition2D(TRenderEntity *this, const float pX, const float pY)
{
    CLASS_THIS();
    Matrix4SetTranslate(&this->mModelView, pX, pY, 0.0f);
}

void RenderEntityRotate(TRenderEntity *this, const float pAngle, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    Matrix4Rotate(&this->mModelView, pAngle, pX, pY, pZ);
}

void RenderEntityRotate2D(TRenderEntity *this, const float pAngle)
{
    RenderEntityRotate(this, pAngle, 0.0f, 0.0f, 1.0f);
}

void RenderEntityReset(TRenderEntity *this)
{
    CLASS_THIS();
    Matrix4GetIdentity(&this->mModelView);
    
    /*! Move 2D Entities to 0,0 (2D origin) */
    if(this->mWidth>0&&this->mHeight>0)
        RenderEntityMove2D(this, this->mWidth/2.0f, this->mHeight/2.0f);
}

void RenderEntityDrawBegin(const TRenderEntity *this, const TRenderer *pRenderer)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
    
    pRenderer->SaveMatrix();
    pRenderer->MultMatrix(&this->mModelView);
    
    MaterialBegin(this->mMaterial);
}

void RenderEntityDrawGeom(const TRenderEntity *this, const TRenderer *pRenderer)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
    
    pRenderer->DrawGeometry(this->mGeom);
}

void RenderEntityDrawEnd(const TRenderEntity *this, const TRenderer *pRenderer)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
    
    MaterialEnd();
    pRenderer->RestoreMatrix();
}

void RenderEntityDraw(const TRenderEntity *this, const TRenderer *pRenderer)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
      
    RenderEntityDrawBegin(this, pRenderer);
    RenderEntityDrawGeom(this, pRenderer);
    RenderEntityDrawEnd(this, pRenderer);
}

/*! 
    Batch Friendly Render Entity Renderer.
    
    Minimizes Texture and Shader switches on a large set of geometry
    using the same material.
    
    Uses Fake Instance Drawing based on vertex arrays by setting up
    the array pointers once and draw using glDrawElements as many times
    as possible.
*/
/*! Last Used Material Cache */
static TMaterial *_gRenderEntityMaterial = NULL;
/*! Last Used Geometry Cache */
static TGeom *_gRenderEntityGeometry = NULL;
void RenderEntityDrawCached(const TRenderEntity *this, const TRenderer *pRenderer)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
      
    /*! Cache Last Used Material Setup */
    if(_gRenderEntityMaterial!=this->mMaterial)
    {
        MaterialEnd();
        MaterialBegin(this->mMaterial);
        _gRenderEntityMaterial = this->mMaterial;
    }
    
    /*! Cache Last Used Geometry Setup */
    if(_gRenderEntityGeometry!=this->mGeom)
    {
        pRenderer->SetupGeometry(this->mGeom);
        _gRenderEntityGeometry = this->mGeom;
    }
    
    /*! Save and Push the current transforms */
    pRenderer->SaveMatrix();
    pRenderer->MultMatrix(&this->mModelView);
    
    /*! Just Draw the Geometry Instance */
    pRenderer->DrawGeometryInstance(this->mGeom);
    
    /*! Pop */
    pRenderer->RestoreMatrix();
}

void RenderEntityFlush(void)
{
    MaterialEnd();
    
    _gRenderEntityMaterial = NULL;
    _gRenderEntityGeometry = NULL;
}

void RenderEntityDestroy(TRenderEntity *this)
{
    CLASS_DEINSTANCE();
    
    MaterialDestroy(this->mMaterial);
    GeomDestroy(this->mGeom);
    
    CLASS_DESTROY(TRenderEntity);
}

TRenderWorld *RenderWorldCreate(void)
{
    CLASS_CREATE(TRenderWorld);

    int i;
    for(i=0;i<RENDERWORLD_MAX_RENDERENTITIES;i++)
        this->mEntities[i] = NULL;
        
    this->mCamera = NULL;

    CLASS_INSTANCE();
}

void RenderWorldSetCamera(TRenderWorld *this, TCamera *pCamera)
{
    CLASS_THIS();
    
    CLASS_ADDREF(pCamera);
    
    CameraDestroy(this->mCamera);
    this->mCamera = pCamera;
}

bool RenderWorldAddEntity(TRenderWorld *this, TRenderEntity *pRenderEntity)
{
    CLASS_THIS();
    
    if(pRenderEntity == NULL)
        return false;
        
    int i;
    for(i=0;i<RENDERWORLD_MAX_RENDERENTITIES;i++)
    {
        if(this->mEntities[i]==NULL)
        {
            CLASS_ADDREF(pRenderEntity);
            this->mEntities[i] = pRenderEntity;
            return true;
        }
    }
    
    return false;
}

void RenderWorldDraw(const TRenderWorld *this, const TRenderer *pRenderer)
{
    CLASS_THIS();
    assert(pRenderer!=NULL);
        
    pRenderer->SaveMatrix();
    
    if(this->mCamera)
        pRenderer->MultMatrix(&this->mCamera->mModelView);
    
    int i;
    for(i=0;i<RENDERWORLD_MAX_RENDERENTITIES;i++)
    {
        TRenderEntity *lEntity = this->mEntities[i];
        
        if(lEntity==NULL)
            break;
            
        RenderEntityDraw(lEntity, pRenderer);
    }
    
    /*! Un-Bind the last bound material */
    MaterialEnd();
    
    pRenderer->RestoreMatrix();
}

void RenderWorldDestroy(TRenderWorld *this)
{
    CLASS_DEINSTANCE();
    
    int i;
    for(i=0;i<RENDERWORLD_MAX_RENDERENTITIES;i++)
    {
        if(this->mEntities[i]==NULL)
            break;
            
        RenderEntityDestroy(this->mEntities[i]);
    }
    
    CameraDestroy(this->mCamera);
    
    CLASS_DESTROY(TRenderWorld);
}
