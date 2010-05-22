/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../../math/math.h"
#include "../material/material.h"

/*!
    \file geom.h
    \brief Geometry Class
*/

/*! Vertex Structure */
typedef struct SVertex
{
    /*! Vertex Position */
	vec3 mPosition;
	/*! Texture Coordinates */
	vec3 mTexCoord;
	/*! Vertex Normal */
	vec3 mNormal;
} TVertex;

/*! Triangle Structure */
typedef struct STriangle
{
    /*! Triangle Indices */
	uint16 mA,mB,mC;
} TTriangle;

/*! Geometry Class */
typedef struct SGeom
{
    /*! Vertices Array */
	TVertex *mVerts;
	/*! Number of Vertices */
	uint32 mNumVerts;
	/*! Triangles Array */
	TTriangle *mTris;
	/*! Number of Triangles */
	uint32 mNumTris;
    /*! Geometry Material */
    TMaterial *mMaterial;
    /*! Reference Count */
	uint32 mRefCount;
} TGeom;

/*! Constructor */
TGeom *GeomCreate(const uint32 pNumVerts, const uint32 pNumTris);
/*! Finalize Geometry */
void GeomFinalize(TGeom *this);
/*! Set Vertex */
void GeomSetVert(TGeom *this, uint32 pIndex, float pU, float pV, float pX, float pY, float pZ);
/*! Set Texture Coordinates for a Vertex */
void GeomSetTexCoord(TGeom *this, uint32 pIndex, float pU, float pV);
/*! Set Triangle */
void GeomSetTri(TGeom *this, uint32 pIndex, uint16 pA, uint16 pB, uint16 pC);
/*! Set Geometry Material */
void GeomSetMaterial(TGeom *this, TMaterial *pMaterial);
/*! Destructor */
void GeomDestroy(TGeom *this);

#endif
