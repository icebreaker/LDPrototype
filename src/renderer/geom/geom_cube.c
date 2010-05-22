/* Copyright (c) 2010, Mihail Szabolcs */
#include "geom_cube.h"

/*!
    \file geom_cube.c
    \brief Geometry Cube Class implementation
*/

TGeom *GeomCreateCube(const float pX, const float pY, const float pZ)
{
	float lSizeX = pX ;
	float lSizeY = pY ;
	float lSizeZ = pZ ;

	float lPositions[] =
	{
		-lSizeX, -lSizeY, -lSizeZ,
		 lSizeX, -lSizeY, -lSizeZ,
		 lSizeX,  lSizeY, -lSizeZ,
		-lSizeX,  lSizeY, -lSizeZ,
		-lSizeX, -lSizeY,  lSizeZ,
		-lSizeX,  lSizeY,  lSizeZ,
		 lSizeX,  lSizeY,  lSizeZ,
		 lSizeX, -lSizeY,  lSizeZ,
		-lSizeX, -lSizeY, -lSizeZ,
		-lSizeX,  lSizeY, -lSizeZ,
		-lSizeX,  lSizeY,  lSizeZ,
		-lSizeX, -lSizeY,  lSizeZ,
		 lSizeX, -lSizeY, -lSizeZ,
		 lSizeX, -lSizeY,  lSizeZ,
		 lSizeX,  lSizeY,  lSizeZ,
		 lSizeX,  lSizeY, -lSizeZ,
		-lSizeX,  lSizeY, -lSizeZ,
		 lSizeX,  lSizeY, -lSizeZ,
		 lSizeX,  lSizeY,  lSizeZ,
		-lSizeX,  lSizeY,  lSizeZ,
		-lSizeX, -lSizeY, -lSizeZ,
		-lSizeX, -lSizeY,  lSizeZ,
		 lSizeX, -lSizeY,  lSizeZ,
		 lSizeX, -lSizeY, -lSizeZ
	};

	float lTexCoords[] =
	{
		0, 1, 1, 1, 1, 0, 0, 0, 
		0, 1, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 1, 0, 0, 0
	};

	unsigned short lIndices[] =
	{
		 0,	 2,  1,
		 0,	 3,  2,
		 4,	 6,  5,
		 4,	 7,  6,
		 8,	10,  9,
		 8,	11, 10,
		12, 14, 13,
		12, 15, 14,
		16, 18, 17,
		16, 19, 18,
		20, 22, 21,
		20, 23, 22
	};

	int i;

	TGeom *this = GeomCreate(24,12);

	for(i=0;i<24;i++)
		GeomSetVert(this, i, lTexCoords[i*2+0], lTexCoords[i*2+1], lPositions[i*3+0], lPositions[i*3+1], lPositions[i*3+2] );

	for(i=0;i<12;i++)
		GeomSetTri(this, i, lIndices[i*3+0], lIndices[i*3+1], lIndices[i*3+2] );

	GeomFinalize(this);

	return this;
}
