/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef CAMERA_H
#define CAMERA_H

#include "../../math/math.h"

/*!
    \file camera.h
    \brief Camera Class
*/

/*! Camera Class */
typedef struct SCamera
{
    /*! Model View Matrix */
    TMatrix4 mModelView;
    /*! Position */
    vec3 mPosition;
    /*! Rotation */
    vec3 mRotation;
    /*! Reference Count */
    uint32 mRefCount;
} TCamera;

/*! Constructor */
TCamera *CameraCreate(const float pX, const float pY, const float pZ);
/*! Set Position */
void CameraSetPosition(TCamera *this, const float pX, const float pY, const float pZ);
/*! Set Rotation */
void CameraSetRotation(TCamera *this, const float pX, const float pY, const float pZ);
/*! Move Camera */
void CameraMove(TCamera *this, const float pDist);
/*! Strafe Camera */
void CameraStrafe(TCamera *this, const float pDist);
/*! Rotate Camera around X Axis */
void CameraRotateX(TCamera *this, const float pAngle);
/*! Rotate Camera around Y Axis */
void CameraRotateY(TCamera *this, const float pAngle);
/*! Update Camera */
void CameraUpdate(TCamera *this);
/*! Destructor */
void CameraDestroy(TCamera *this);

#endif
