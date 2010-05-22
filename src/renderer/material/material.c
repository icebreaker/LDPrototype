/* Copyright (c) 2010, Mihail Szabolcs */
#include "material.h"
#include "../../framework/class.h"

/*!
    \file material.c
    \brief Material Class implementation
*/

/*! Global Uniform Names used in GLSL Shaders */
static const char *gUniforms[] = 
{
    "tex1",
    "tex2",
    "tex3",
    "tex4"  
};
/*! Default Material Color */
static vec4 gColor = {1.0f,1.0f,1.0f,1.0f};

TMaterial *MaterialCreate(void)
{
    CLASS_CREATE(TMaterial);

    int i;
    for(i=0;i<MATERIAL_MAX_TEXTURES;i++)
        this->mTextures[i] = NULL;

    this->mShader = NULL;
    
    MaterialSetColor(this,gColor[0],gColor[1],gColor[2],gColor[3]);

    CLASS_INSTANCE();
}

TMaterial *MaterialClone(const TMaterial *this)
{
    TMaterial *lClone = MaterialCreate();
    
    int i;
    for(i=0;i<MATERIAL_MAX_TEXTURES;i++)
    {
        if(this->mTextures[i]==NULL)
            break;
            
        MaterialAddTexture(lClone, this->mTextures[i]);
    }

    if(this->mShader!=NULL)
        MaterialAddShader(lClone, this->mShader);
    
    MaterialSetRGB(lClone, this->mColor[0], this->mColor[1], this->mColor[2]);
    MaterialSetAlpha(lClone, this->mColor[3]);
    
    return lClone;
}

bool MaterialAddTexture(TMaterial *this, TTexture *pTexture)
{
    CLASS_THIS();
    assert(pTexture!=NULL);

    int i;
    for(i=0;i<MATERIAL_MAX_TEXTURES;i++)
    {
        if(this->mTextures[i]==NULL)
        {
            CLASS_ADDREF(pTexture);
            this->mTextures[i] = pTexture;   
            
            return true;
        }
    }
    
    return false;
}

bool MaterialAddShader(TMaterial *this, TShader *pShader)
{
    CLASS_THIS();
    assert(pShader!=NULL);
    
    CLASS_ADDREF(pShader);
    
    ShaderDestroy(this->mShader);
    this->mShader = pShader;
    
    return true;
}

void MaterialSetColor(TMaterial *this, const float pR, const float pG, const float pB, const float pA)
{
    CLASS_THIS();
    
    MaterialSetRGB(this, pR,pG,pB);
    MaterialSetAlpha(this, pA);
}

void MaterialSetRGB(TMaterial *this, const float pR, const float pG, const float pB)
{
    CLASS_THIS();
    this->mColor[0] = pR;
    this->mColor[1] = pG;
    this->mColor[2] = pB;
}

void MaterialSetAlpha(TMaterial *this, const float pA)
{
    CLASS_THIS();
    this->mColor[3] = pA;
}

void MaterialBegin(const TMaterial *this)
{
    CLASS_THIS();
    
    glColor4f(this->mColor[0], this->mColor[1], this->mColor[2], this->mColor[3]);
        
    if(this->mShader!=NULL)
        ShaderBegin(this->mShader);
        
    int i;
    for(i=0;i<MATERIAL_MAX_TEXTURES;i++)
    {
        if(this->mTextures[i]==NULL)
            break;
            
        glActiveTexture(GL_TEXTURE0+i);
        TextureBegin(this->mTextures[i]);
        
        if(this->mShader!=NULL)
            ShaderSetUniform1i(this->mShader,gUniforms[i],i);
    }
}

void MaterialEnd(void)
{   
    ShaderEnd();
     
    int i;
    for(i=0;i<MATERIAL_MAX_TEXTURES;i++)
    {
        glActiveTexture(GL_TEXTURE0+i);
        TextureEnd();
    }
    
    glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void MaterialDestroy(TMaterial *this)
{
    CLASS_DEINSTANCE();

    int i = 0;
    for(i=0;i<MATERIAL_MAX_TEXTURES;i++)
        TextureDestroy(this->mTextures[i]);
        
    ShaderDestroy(this->mShader);
    
    CLASS_DESTROY(TMaterial);
}
