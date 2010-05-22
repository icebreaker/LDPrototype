/* Copyright (c) 2010, Mihail Szabolcs */
#include "geom.h"
#include "../../framework/class.h"

/*!
    \file geom.c
    \brief Geometry Class implementation
*/

TGeom *GeomCreate(const uint32 pNumVerts, const uint32 pNumTris)
{
    CLASS_CREATE(TGeom);

	uint32 lVertsSize = sizeof(TVertex) * pNumVerts;
	uint32 lTrisSize = sizeof(TTriangle) * pNumTris;
	
	this->mNumVerts = pNumVerts;
	this->mVerts = (TVertex *) malloc(lVertsSize);
	memset(this->mVerts,0,lVertsSize);

	this->mNumTris = pNumTris;
	this->mTris = (TTriangle *) malloc(lTrisSize);
	memset(this->mTris,0,lTrisSize);

    this->mMaterial = NULL;

    CLASS_INSTANCE();
}

void GeomFinalize(TGeom *this)
{
    CLASS_THIS();
    
	int i;
	for(i=0;i<this->mNumVerts;i++)
		VEC3NORM(this->mVerts[i].mNormal);
}

void GeomSetVert(TGeom *this, uint32 pIndex, float pU, float pV, float pX, float pY, float pZ)
{
	CLASS_THIS();
	
	TVertex *lVertex = &this->mVerts[pIndex];
	
	VEC2SET(lVertex->mTexCoord,pU,pV);
	VEC3SET(lVertex->mPosition,pX,pY,pZ);
}

void GeomSetTexCoord(TGeom *this, uint32 pIndex, float pU, float pV)
{
    CLASS_THIS();
    VEC2SET(this->mVerts[pIndex].mTexCoord,pU,pV);
}

void GeomSetTri(TGeom *this, uint32 pIndex, uint16 pA, uint16 pB, uint16 pC)
{
	CLASS_THIS();
	
	TTriangle *lTriangle = &this->mTris[pIndex];

	lTriangle->mA = pA;
	lTriangle->mB = pB;
	lTriangle->mC = pC;

	TVertex *lV1 = &this->mVerts[pA];
	TVertex *lV2 = &this->mVerts[pB];
	TVertex *lV3 = &this->mVerts[pC];

	vec3 lVec0, lVec1, lNormal;
	VEC3SUB(lVec0, lV2->mPosition, lV1->mPosition);
	VEC3SUB(lVec1, lV3->mPosition, lV1->mPosition);
	
	VEC3CROSS(lNormal, lVec0, lVec1);
	VEC3NORM(lNormal);

	VEC3ADD(lV1->mNormal, lV1->mNormal, lNormal);
	VEC3ADD(lV2->mNormal, lV2->mNormal, lNormal);
	VEC3ADD(lV3->mNormal, lV3->mNormal, lNormal);
}

void GeomSetMaterial(TGeom *this, TMaterial *pMaterial)
{
    CLASS_THIS();
    assert(pMaterial!=NULL);
    
    CLASS_ADDREF(pMaterial);
    
    MaterialDestroy(this->mMaterial);
    this->mMaterial = pMaterial;
}

void GeomDestroy(TGeom *this)
{
    CLASS_DEINSTANCE();

	SAFE_FREE(this->mVerts);
	SAFE_FREE(this->mTris);
	
	MaterialDestroy(this->mMaterial);

    CLASS_DESTROY(TGeom);
}
