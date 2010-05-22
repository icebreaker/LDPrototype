/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef CLASS_H
#define CLASS_H

#include "../sys/platform.h"
#include "../sys/types.h"
#include "../sys/utils.h"

/*!
    \file class.h
    \brief C++ like class utilities.
*/

#undef assert
#ifdef DEBUG
    #define assert(x) if(!(x)) printf("ASSERTION: %s failed on line %d in file %s\n",#x,__LINE__,__FILE__)
#else
    #define assert(x)
#endif

#define UNUSED(x) (void)(x)
#define SAFE_FREE(x) if(x!=NULL) free(x)

#define CLASS_CREATE(T) T *this = (T *) malloc(sizeof(T)); memset(this,0,sizeof(T)); this->mRefCount = 1; //printf("%s created ...\n",#T)
#define CLASS_DESTROY(T) free(this); //printf("%s destroyed ...\n",#T)
#define CLASS_ADDREF(this) this->mRefCount++ 
#define CLASS_INSTANCE() return this
#define CLASS_DEINSTANCE() if(this==NULL || (--this->mRefCount>0)) return
#define CLASS_THIS() assert(this!=NULL)

#endif
