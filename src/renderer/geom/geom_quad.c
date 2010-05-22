/* Copyright (c) 2010, Mihail Szabolcs */
#include "geom_quad.h"

/*!
    \file geom_quad.c
    \brief Geometry Quad Class implementation
*/

TGeom *GeomCreateQuad(const float pX, const float pY)
{
	const float lSizeX = (pX / 2.0f);
	const float lSizeY = (pY / 2.0f);
	
	TGeom *this = GeomCreate(4,2);

	GeomSetVert(this, 0, 0.0f, 1.0f, -lSizeX, -lSizeY, 0.0f);
	GeomSetVert(this, 1, 1.0f, 1.0f,  lSizeX, -lSizeY, 0.0f);
	GeomSetVert(this, 2, 1.0f, 0.0f,  lSizeX,  lSizeY, 0.0f);
	GeomSetVert(this, 3, 0.0f, 0.0f, -lSizeX,  lSizeY, 0.0f);

	GeomSetTri(this, 0, 3, 2, 1);
	GeomSetTri(this, 1, 3, 1, 0);

	GeomFinalize(this);

	return this;
}
