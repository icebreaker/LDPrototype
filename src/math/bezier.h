/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef BEZIER_H
#define BEZIER_H

/*!
    \file bezier.h
    \brief (Cubic) Bezier Curve
*/

#define B0(t) (t*t*t)
#define B1(t) (3*t*t*(1-t))
#define B2(t) (3*t*(1-t)*(1-t))
#define B3(t) ((1-t)*(1-t)*(1-t))

#define BC(p0,p1,p2,p3,t) ( p0 * B3(t) + (p1 * B2(t)) + (p2 * B1(t)) + (p3 * B0(t)) )

#define BCVEC3(p0,p1,p2,p3,t) ( BC(p0[0],p1[0],p2[0],p3[0],t) ), \
                              ( BC(p0[1],p1[1],p2[1],p3[1],t) ), \
                              ( BC(p0[2],p1[2],p2[2],p3[2],t) )
                         
#define BCVEC2(p0,p1,p2,p3,t) ( BC(p0[0],p1[0],p2[0],p3[0],t) ), \
                              ( BC(p0[1],p1[1],p2[1],p3[1],t) )

#endif
