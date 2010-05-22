/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/*!
    \file utils.h
    \brief Utilities
*/

/*! TGA Header */
#pragma pack(push, 1)
typedef struct STGAHeader
{
    char        idlength;
    char        colourmaptype;
    char        datatypecode;
    short int   colourmaporigin;
    short int   colourmaplength;
    char        colourmapdepth;
    short int   x_origin;
    short int   y_origin;
    short       width;
    short       height;
    char        bitsperpixel;
    char        imagedescriptor;
} TTGAHeader;
#pragma pack(pop)

/*! Berstein Hash */
uint32 hash(const char *pStr);
/*! Read Text File */
char *GetFileContents(const char *pFileName);
/*! Write TGA Image (24 bit, BGR) */
bool WriteTGA(const char *pFileName, const uint32 pWidth, const uint32 pHeight, const uint8 *pData);

#endif
