/* Copyright (c) 2010, Mihail Szabolcs */
#include "matrix4.h"
#include "../framework/class.h"

/*!
    \file matrix4.c
    \brief Matrix4x4 Class implementation
*/

void Matrix4GetIdentity(TMatrix4 *this)
{
    this->m11 = 1.0f; this->m12 = 0.0f; this->m13 = 0.0f; this->m14 = 0.0f;
    this->m21 = 0.0f; this->m22 = 1.0f; this->m23 = 0.0f; this->m24 = 0.0f;
    this->m31 = 0.0f; this->m32 = 0.0f; this->m33 = 1.0f; this->m34 = 0.0f;
    this->m41 = 0.0f; this->m42 = 0.0f; this->m43 = 0.0f; this->m44 = 1.0f;
}

void Matrix4Mult(TMatrix4 *this, const TMatrix4 *pMatrix4)
{
    glPushMatrix();
    glLoadMatrixf(this->m);
    glMultMatrixf(pMatrix4->m);
    Matrix4Get(this);
    glPopMatrix();    
}

void Matrix4Get(TMatrix4 *this)
{
    glGetFloatv(GL_MODELVIEW_MATRIX, this->m);
}

void Matrix4SetTranslate(TMatrix4 *this, const float pX, const float pY, const float pZ)
{
    this->m14 = pX;
    this->m24 = pY;
    this->m34 = pZ;
}

void Matrix4AddTranslate(TMatrix4 *this, const float pX, const float pY, const float pZ)
{
    this->m14 += pX;
    this->m24 += pY;
    this->m34 += pZ;
}

void Matrix4Translate(TMatrix4 *this, const float pX, const float pY, const float pZ)
{
    glPushMatrix();
    glLoadMatrixf(this->m);
    glTranslatef(pX,pY,pZ);
    Matrix4Get(this);
    glPopMatrix();
}

void Matrix4Rotate(TMatrix4 *this, const float pAngle, const float pX, const float pY, const float pZ)
{
    glPushMatrix();
    glLoadMatrixf(this->m);
    glRotatef(pAngle,pX,pY,pZ);
    Matrix4Get(this);
    glPopMatrix();
}

void Matrix4Scale(TMatrix4 *this, const float pX, const float pY, const float pZ)
{
    glPushMatrix();
    glLoadMatrixf(this->m);
    glScalef(pX,pY,pZ);
    Matrix4Get(this);
    glPopMatrix();
}

void Matrix4Copy(TMatrix4 *this, const TMatrix4 *pMatrix4)
{
    int i;
    for(i=0;i<16;i++)
        this->m[i] = pMatrix4->m[i];
}

void Matrix4Print(const TMatrix4 *this)
{
    printf("Matrix4 Debug Print\n");
    printf("-------------------\n");
    printf("%.02f %.02f %.02f %.02f\n",this->m11,this->m12,this->m13,this->m14);
    printf("%.02f %.02f %.02f %.02f\n",this->m21,this->m22,this->m23,this->m24);
    printf("%.02f %.02f %.02f %.02f\n",this->m31,this->m32,this->m33,this->m34);
    printf("%.02f %.02f %.02f %.02f\n",this->m41,this->m42,this->m43,this->m44);
    printf("-------------------\n");
}
