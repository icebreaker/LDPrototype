/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef MATRIX4_H
#define MATRIX4_H

/*!
    \file matrix4.h
    \brief 4x4 Matrix Class
*/

/*! 4x4 Matrix Class */
typedef union SMatrix4
{
	struct
	{
		float m11, m21, m31, m41;
		float m12, m22, m32, m42;
		float m13, m23, m33, m43;
		float m14, m24, m34, m44;
	};
	
	float m[16];
	
} TMatrix4;

/*! Get Identity */
void Matrix4GetIdentity(TMatrix4 *this);
/*! Multiply */
void Matrix4Mult(TMatrix4 *this, const TMatrix4 *pMatrix4);
/*! Get the current GL_MODELVIEW_MATRIX */
void Matrix4Get(TMatrix4 *this);
/*! Set Translate (fast translate) */
void Matrix4SetTranslate(TMatrix4 *this, const float pX, const float pY, const float pZ);
/*! Add Translate (fast additive translate) */
void Matrix4AddTranslate(TMatrix4 *this, const float pX, const float pY, const float pZ);
/*! Translate */
void Matrix4Translate(TMatrix4 *this, const float pX, const float pY, const float pZ);
/*! Rotate */
void Matrix4Rotate(TMatrix4 *this, const float pAngle, const float pX, const float pY, const float pZ);
/*! Scale */
void Matrix4Scale(TMatrix4 *this, const float pX, const float pY, const float pZ);
/*! Copy */
void Matrix4Copy(TMatrix4 *this, const TMatrix4 *pMatrix4);
/*! Debug Print (transposed => row major order) */
void Matrix4Print(const TMatrix4 *this);

#endif
