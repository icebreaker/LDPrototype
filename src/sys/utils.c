/* Copyright (c) 2010, Mihail Szabolcs */
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/*!
    \file utils.c
    \brief Utilities implementation
*/
    
/*!
	Berstein Hash
	
	this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c.
	another version of this algorithm (now favored by bernstein) uses
	xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33 (why it works better than
	many other constants, prime or not) has never been adequately explained.

	(source: http://www.cse.yorku.ca/~oz/hash.html)
*/
uint32 hash(const char *pStr)
{
	uint32 lHash = 5381; int lCh;

	while ( ( lCh = *pStr++ ) )
		lHash = ( ( lHash << 5 ) + lHash ) + lCh;

	return lHash;
}

char *GetFileContents(const char *pFileName)
{
    FILE *lFile = fopen(pFileName, "r");
    if(lFile==NULL)
    {
        printf("GetFileContents: Failed to open file %s ...\n", pFileName);
        return NULL;
    }

    uint32 lOldPos = fseek(lFile, 0L, SEEK_END);
    uint32 lSize = ftell(lFile);
    fseek(lFile, lOldPos, SEEK_SET);

    char *lBuffer = (char *) malloc(lSize+1);
    fread(lBuffer, lSize, 1, lFile);
    lBuffer[lSize] = '\0';
    fclose(lFile);

    return lBuffer;
}

bool WriteTGA(const char *pFileName, const uint32 pWidth, const uint32 pHeight, const uint8 *pData)
{
    TTGAHeader lTGAHeader = { 0, 0, 2, 0, 0, 0, 0, 0, pWidth, pHeight, 32, 0 };
    
    FILE *lFile = fopen(pFileName, "w");
    if(lFile==NULL)
    {
        printf("WriteTGA: Failed to open file %s for writing ...\n", pFileName);
        return false;
    }
     
    /* Write Out Header */
    fwrite(&lTGAHeader, sizeof(TTGAHeader), 1, lFile);
    /* Write Out Raw Image Data */
    fwrite(pData, pWidth * pHeight * 4, 1, lFile);
    /* Close */
    fclose(lFile);
    
    printf("WriteTGA: %s\n", pFileName);
    
    return true;
}

