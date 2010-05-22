/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef VECTOR_H
#define VECTOR_H

/*!
    \file vector.h
    \brief Vector Classes
*/

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

#define VEC2SET(v,x,y) { v[0]=x;v[1]=y; }
#define VEC2ZERO(v) (v[0]==0.0f&&v[1]==0.0f)
#define VEC3SET(v,x,y,z) { v[0]=x;v[1]=y;v[2]=z; }
#define VEC3CPY(v,v2) VEC3SET(v,v2[0],v2[1],v2[2])
#define VEC3ZERO(v) (v[0]==0.0f&&v[1]==0.0f&&v[2]==0.0f)
#define VEC3ADD(v0,v1,v2) VEC3SET(v0,(v1[0]+v2[0]),(v1[1]+v2[1]),(v1[2]+v2[2]))
#define VEC3SUB(v0,v1,v2) VEC3SET(v0,(v1[0]-v2[0]),(v1[1]-v2[1]),(v1[2]-v2[2]))
#define VEC3DOT(v1,v2) ((v1[0]*v2[0])+(v1[1]*v2[1])+(v1[2]*v2[2]))
#define VEC3CROSS(v0,v1,v2) VEC3SET(v0, (v1[1]*v2[2]) - (v1[2]*v2[1]), \
										(v1[2]*v2[0]) - (v1[0]*v2[2]), \
										(v1[0]*v2[1]) - (v1[1]*v2[0]) )
#define VEC3LEN(v) (sqrt(VEC3DOT(v,v)))
#define VEC3MUL(v,x) VEC3SET(v,v[0]*x,v[1]*x,v[2]*x)
#define VEC3DIV(v,x) VEC3SET(v,v[0]/x,v[1]/x,v[2]/x)
#define VEC3NORM(v) VEC3MUL(v, 1.0f / VEC3LEN(v))

#endif
