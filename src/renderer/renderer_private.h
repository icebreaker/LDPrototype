/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef RENDERER_PRIVATE_H
#define RENDERER_PRIVATE_H

#include "../framework/framework_private.h"
#include "geom/geom.h"

/*!
    \file renderer_private.h
    \brief Renderer Prototypes
*/
    
typedef void(*TRendererBeginFrame)(void);
typedef void(*TRendererEndFrame)(void);
typedef void(*TRendererBegin2D)(const uint32 pWidth, const uint32 pHeight);
typedef void(*TRendererEnd2D)(void);
typedef void(*TRendererResizeFrame)(const uint32 pX, const uint32 pY, const uint32 pWidth, const uint32 pHeight);
typedef void(*TRendererSetupGeometry)(const TGeom *pGeometry);
typedef void(*TRendererDrawGeometryInstance)(const TGeom *pGeometry);
typedef void(*TRendererDrawGeometry)(const TGeom *pGeometry);
typedef void(*TRendererLoadMatrix)(const TMatrix4 *pMatrix4);
typedef void(*TRendererMultMatrix)(const TMatrix4 *pMatrix4);
typedef void(*TRendererSaveMatrix)(void);
typedef void(*TRendererRestoreMatrix)(void);
typedef void(*TRendererSetBackColor)(const float pR, const float pG, const float pB, const float pA);
typedef void(*TRendererSetColor)(const float pR, const float pG, const float pB, const float pA);
typedef void(*TRendererSetDepthTest)(const bool pState);
typedef void(*TRendererSetDepthMask)(const bool pState);
typedef void(*TRendererSetBlending)(const bool pState);
typedef void(*TRendererSetAdditiveBlending)(void);
typedef void(*TRendererSetAlphaBlending)(void);
typedef void(*TRendererInit)(const TConfig *pConfig);
typedef void(*TRendererShutdown)(void);

#endif
