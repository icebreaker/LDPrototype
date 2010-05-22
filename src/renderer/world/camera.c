/* Copyright (c) 2010, Mihail Szabolcs */
#include "camera.h"
#include "../../framework/class.h"

/*!
    \file camera.c
    \brief Camera Class implementation
*/

TCamera *CameraCreate(const float pX, const float pY, const float pZ)
{
    CLASS_CREATE(TCamera);
        
    CameraSetPosition(this, pX, pY, pZ);
    
    CLASS_INSTANCE();
}

void CameraSetPosition(TCamera *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    
    VEC3SET(this->mPosition, pX, pY, pZ);
    CameraUpdate(this);
}

void CameraSetRotation(TCamera *this, const float pX, const float pY, const float pZ)
{
    CLASS_THIS();
    
    VEC3SET(this->mRotation, pX, pY, pZ);
    CameraUpdate(this);
}

void CameraMove(TCamera *this, const float pDist)
{
    CLASS_THIS();
    
    TMatrix4 *lM = &this->mModelView;
    vec3 lMove = {lM->m31*pDist,lM->m32*pDist,lM->m33*pDist};
    VEC3ADD(this->mPosition,this->mPosition,lMove);
    CameraUpdate(this);
}

void CameraStrafe(TCamera *this, const float pDist)
{
    CLASS_THIS();
    
    TMatrix4 *lM = &this->mModelView;
    vec3 lMove = {lM->m33*pDist,0.0f,-lM->m31*pDist};
    VEC3ADD(this->mPosition,this->mPosition,lMove);
    CameraUpdate(this);
}

void CameraRotateX(TCamera *this, const float pAngle)
{
    CLASS_THIS();
    
    this->mRotation[0] += pAngle;
    CameraUpdate(this);
}

void CameraRotateY(TCamera *this, const float pAngle)
{
    CLASS_THIS();
    
    this->mRotation[1] += pAngle;
    CameraUpdate(this);
}

void CameraUpdate(TCamera *this)
{
    CLASS_THIS();
    
    Matrix4GetIdentity(&this->mModelView);
    Matrix4Rotate(&this->mModelView,-this->mRotation[0], 1.0f, 0.0f, 0.0f);
    Matrix4Rotate(&this->mModelView,-this->mRotation[1], 0.0f, 1.0f, 0.0f);
    Matrix4Rotate(&this->mModelView,-this->mRotation[2], 0.0f, 0.0f, 1.0f);
    Matrix4Translate(&this->mModelView, -this->mPosition[0], -this->mPosition[1], -this->mPosition[2]);
}

void CameraDestroy(TCamera *this)
{
   CLASS_DEINSTANCE();
   CLASS_DESTROY(TCamera);    
}
