/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef MATH_H
#define MATH_H

/*!
    \file math.h
    \brief Common Math Classes, and utilities
*/

#include <math.h>
#include "../sys/types.h"
#include "vector.h"
#include "matrix4.h"
#include "bezier.h"

//! Bit Maker
#define BIT(x) ((x) << 1)
//! Clamp
#define CLAMP(x,l,h) ( ( x>h ) ? h : ( x<l ) ? ( l ) : ( x ) )
//! Random
#define RANDOM(x) (rand() % x)
//! Random In A Range
#define RANDOM2R(min,max) (min+RANDOM(max))

#endif
