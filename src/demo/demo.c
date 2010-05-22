/* Copyright (c) 2010, Mihail Szabolcs */
#include "demo.h"
#include "../framework/framework.h"

#include "effects/resources.h"
#include "effects/garden.h"
#include "effects/grass.h"

/*!
    \file demo.c
    \brief Demo Application Implementation
*/

static TRenderer *gRnd  = NULL;
static TCamera *gCamera = NULL;
#ifdef MUSIC
static TMusic *gMusic   = NULL;
#endif

static int gCameraId = -1;
static float gT = 0.0f;

static TGarden *gGarden = NULL;

static TRenderEntity *gIntro = NULL;
static TRenderEntity *gOutro = NULL;

static TRenderEntity *gSky = NULL;
static TRenderEntity *gSegment = NULL;

#define ALPHA_INC 0.005f
static float gAlphaInc = ALPHA_INC;
static float gAlpha = 0.0f;

void TextReset(void)
{
    gAlphaInc = ALPHA_INC;
    gAlpha = 0.0f;
}

static void TextShow(TRenderEntity *this, const TRenderer *pRenderer, bool pFadeOut)
{
    CLASS_THIS();

    if(gAlpha > 1.2f && pFadeOut)
         gAlphaInc = -ALPHA_INC;
        
    if(gAlpha < 0.0f)
        return;       
        
    MaterialSetAlpha(this->mMaterial, gAlpha);
    RenderEntityDraw(this, pRenderer);
    
    gAlpha += gAlphaInc;
}

void CameraPath(const int pId, const TUpdate *pUpdate)
{
    if(gCameraId != pId)
    {
        gT = 0.0f;
        gCameraId = pId;
    }
        
    switch(pId)
    {
        case 0:
        {
            CameraRotateY(gCamera, -gT);
            gT += 0.01f;
        }
        break;
        
        case 1:
        {
            CameraSetPosition(gCamera,-70.0f+gT, 6.0f,30.0f-gT);
            CameraRotateY(gCamera, -(gT*0.005f));
            gT += 0.1f;
        }
        break;
        
        case 2:
        {
            CameraRotateX(gCamera, pUpdate->mDeltaTime * 0.01f);
        }
        break;
        
        case 3:
        {
            CameraRotateX(gCamera, -(pUpdate->mDeltaTime * 0.01f));
        }
        break;
        
        case 4:
        {
            static vec3 lPos = {0.0f, 0.0f, 0.0f};
            static vec3 lRot = {0.0f, 0.0f, 0.0f};
                
            if(VEC3ZERO(lPos)) VEC3CPY(lPos, gCamera->mPosition);
            if(VEC3ZERO(lRot)) VEC3CPY(lRot, gCamera->mRotation);
           
            CameraSetPosition(gCamera, lPos[0] - gT, lPos[1], lPos[2] + (gT * 2));
            CameraSetRotation(gCamera, lRot[0], lRot[1] + (gT * 3), lRot[2]);
              
            gT += 0.08f;
        }
        break;
        
        case 5:
        {
            static vec3 lPos = {0.0f, 0.0f, 0.0f};
            static vec3 lRot = {0.0f, 0.0f, 0.0f};
                
            if(VEC3ZERO(lPos)) VEC3CPY(lPos, gCamera->mPosition);
            if(VEC3ZERO(lRot)) VEC3CPY(lRot, gCamera->mRotation);
           
            CameraSetPosition(gCamera, lPos[0] + gT, lPos[1], lPos[2] - (gT * 2));
            CameraSetRotation(gCamera, lRot[0], lRot[1] - (gT * 3), lRot[2]);
              
            gT += 0.08f;      
        }
        break;
        
        case 6:
        {
            static vec3 lPos = {0.0f, 0.0f, 0.0f};
            static vec3 lRot = {0.0f, 0.0f, 0.0f};
                
            if(VEC3ZERO(lPos)) VEC3CPY(lPos, gCamera->mPosition);
            if(VEC3ZERO(lRot)) VEC3CPY(lRot, gCamera->mRotation);
           
            CameraSetPosition(gCamera, lPos[0] - gT, lPos[1], lPos[2] + (gT * 2));
            CameraSetRotation(gCamera, lRot[0], lRot[1] + (gT * 3), lRot[2]);
              
            gT += 0.08f;      
        }
        break;
        
        case 7:
        {
            static vec3 lPos = {0.0f, 0.0f, 0.0f};
            static vec3 lRot = {0.0f, 0.0f, 0.0f};
                
            if(VEC3ZERO(lPos)) VEC3CPY(lPos, gCamera->mPosition);
            if(VEC3ZERO(lRot)) VEC3CPY(lRot, gCamera->mRotation);
           
            CameraSetPosition(gCamera, lPos[0] + gT, lPos[1], lPos[2] - (gT * 2));
            CameraSetRotation(gCamera, lRot[0], lRot[1] - (gT * 3), lRot[2]);
              
            gT += 0.08f;            
        }
        break;
        
        case 8:
        {
            static vec3 lPos = {0.0f, 0.0f, 0.0f};
            static vec3 lRot = {0.0f, 0.0f, 0.0f};
                
            if(VEC3ZERO(lPos)) VEC3CPY(lPos, gCamera->mPosition);
            if(VEC3ZERO(lRot)) VEC3CPY(lRot, gCamera->mRotation);
            
            CameraSetPosition(gCamera, lPos[0], lPos[1], lPos[2] + (gT * 2));
            CameraSetRotation(gCamera, lRot[0], lRot[1] + (gT * 4), lRot[2]);
              
            gT += 0.08f;            
        }
        break;
        
        case 9:
        {
            static vec3 lPos = {0.0f, 0.0f, 0.0f};
            static vec3 lRot = {0.0f, 0.0f, 0.0f};
                
            if(VEC3ZERO(lPos)) VEC3CPY(lPos, gCamera->mPosition);
            if(VEC3ZERO(lRot)) VEC3CPY(lRot, gCamera->mRotation);
            
            CameraSetPosition(gCamera, lPos[0], lPos[1] + (gT * 2), lPos[2]);
            //CameraSetRotation(gCamera, lRot[0], lRot[1] + (gT * 3), lRot[2]);
              
            gT += 0.08f;            
        }
        break;
    }
}

void DemoConfig(TConfig *pConfig)
{
    pConfig->mTitle = "-== Happy Birthday ==-";
    pConfig->mMultiSampling = 4;
    pConfig->mWidth = 800;
	pConfig->mHeight= 460;
//	pConfig->mFullScreen = true;
//	pConfig->mHideCursor = true;

#ifdef MUSIC
    pConfig->mAudio = true;
#endif
}

bool DemoInit(const TConfig *pConfig)
{
	gRnd = RendererCreate(pConfig);
	gCamera = CameraCreate(-70.0f,6.0f,30.0f);

#ifdef MUSIC
    gMusic = MusicCreate(MUSIC);
    MusicPlay(gMusic, 0);    
#endif

    gIntro = RenderEntityCreate2D(256, 256, INTRO_TEXTURE);
    
    RenderEntitySetPosition2D(gIntro, ((pConfig->mWidth  - 256) / 2) + 128,
                                      ((pConfig->mHeight - 256) / 2) + 128 );
                                      
    gOutro = RenderEntityCreate2D(256, 256, OUTRO_TEXTURE);
    
    RenderEntitySetPosition2D(gOutro, ((pConfig->mWidth  - 256) / 2) + 128,
                                      ((pConfig->mHeight - 256) / 2) + 128 );
    
    gGarden = GardenCreate(45.0f, 45.0f,  0.0f, 0.0f,   0.0f);
   
    gSky = RenderEntityCreateCubeTextured(100.0f,100.0f,100.0f, SKY_TEXTURE); 
    
    gSegment = RenderEntityCreateQuadTextured(1.0f, 1.0f, FLARE_TEXTURE);
    
    TShader *lShader = ShaderCreate(BILLBOARDING_SHADER_VS, NULL);

    if(lShader!=NULL)
    {
        MaterialAddShader(gSegment->mMaterial, lShader);
        ShaderDestroy(lShader);
        lShader = 0;
    }
    
    printf("Done ...\n");
	return true;
}

bool DemoUpdate(const TConfig *pConfig, TUpdate *pUpdate)
{
    float lDeltaMove = (pUpdate->mDeltaTime*0.01f);
    
#ifdef DEBUG
    float lDeltaMoveRot = (pUpdate->mDeltaTime*0.01f);
    
    static int lLastX = 0;
    static int lLastY = 0;
    int lX, lY;
    
	if(pUpdate->mKeys['w'])
	    CameraMove(gCamera, -lDeltaMove);

	if(pUpdate->mKeys['s'])
	    CameraMove(gCamera,  lDeltaMove);

	if(pUpdate->mKeys['a'])
	    CameraStrafe(gCamera, -lDeltaMove);

	if(pUpdate->mKeys['d'])
	    CameraStrafe(gCamera, lDeltaMove);

    SDL_PumpEvents();  
    if(SDL_GetMouseState(&lX, &lY) & SDL_BUTTON(1))
    {
        CameraRotateY(gCamera, -((lX - lLastX) * lDeltaMoveRot));
        CameraRotateX(gCamera, -((lY - lLastY) * lDeltaMoveRot));
    }
    
    lLastX = lX;
    lLastY = lY;
#endif

    /*! Number of elapsed seconds since we started this masquerade */
    int lSex = pUpdate->mElapsedTime / 1000;
   
    if(lSex>12&&lSex<15)
        CameraPath(0, pUpdate);
    else if(lSex>15&&lSex<25)
        CameraPath(1, pUpdate);
    else if(lSex>30&&lSex<34)
        CameraPath(2, pUpdate);
    else if(lSex>35&&lSex<40)
        CameraPath(3, pUpdate);
    else if(lSex>40&&lSex<50)
        CameraPath(4, pUpdate);
    else if(lSex>50&&lSex<62) 
        CameraPath(5, pUpdate);
    else if(lSex>62&&lSex<65) 
        CameraPath(2, pUpdate);
    else if(lSex>65&&lSex<70) 
        CameraPath(6, pUpdate);
    else if(lSex>70&&lSex<73) 
        CameraPath(3, pUpdate);
    else if(lSex>75&&lSex<78) 
        CameraPath(7, pUpdate);
    else if(lSex>80&&lSex<88) 
        CameraPath(8, pUpdate);
    else if(lSex>89&&lSex<94) 
        CameraPath(2, pUpdate);
    else if(lSex>95&&lSex<102) 
        CameraPath(9, pUpdate);

        
    GardenUpdate(gGarden, pUpdate);
    
#ifdef MUSIC

    if(lSex>120&&lSex<122) MusicFadeOut(3000);
    
    if(!MusicIsPlaying())
        return false;
        
#endif
        
    return true;
}

void DemoRender(const TConfig *pConfig, TUpdate *pUpdate)
{
    int lSex = pUpdate->mElapsedTime / 1000;
    
#ifdef DEBUG
    //char lBuff[64] = {0,};
    //sprintf(lBuff,"Elapsed Sex: %d\r", lSex);
    //SDL_WM_SetCaption(lBuff, "Debug");
#endif

	gRnd->BeginFrame();
    gRnd->LoadMatrix(&gCamera->mModelView);

    gRnd->SetAdditiveBlending();
    gRnd->SetDepthTest(true);
    gRnd->SetDepthMask(false);

    RenderEntityDraw(gSky, gRnd);

    if(lSex<10)
    {	
	    gRnd->SetAlphaBlending();
        gRnd->SetDepthTest(true);
        gRnd->SetDepthMask(true);    
        gRnd->Begin2D(pConfig->mWidth, pConfig->mHeight);
            TextShow(gIntro, gRnd, true);
        gRnd->End2D();
    }
    
    if(lSex==101) TextReset();
    
    if(lSex>102&&lSex<120)
    {
        gRnd->SetAlphaBlending();
        gRnd->SetDepthTest(true);
        gRnd->SetDepthMask(true);    
        gRnd->Begin2D(pConfig->mWidth, pConfig->mHeight);
            TextShow(gOutro, gRnd, true);
        gRnd->End2D();
    }
        
    if(lSex>10)
    {  
        GardenDraw(gGarden, gRnd, pUpdate);
    }
    
    if(lSex>30)
    {
        static int lLastTime = 0;
        static int lMax1 = 0;
        static int lMax2 = 0;
        
        if(pUpdate->mTime-lLastTime>10)
        {
            lLastTime = pUpdate->mTime;
            
            if(lMax1<512) lMax1++;
            
            if(lSex>60&&lMax2<512) lMax2++;
        }
        
        int i;
        for(i=0;i<lMax1;i++)
        {
            float x = 5.0f * cos(i*(pUpdate->mTime * 0.00001));
            float z = 5.0f * sin(i*(pUpdate->mTime * 0.00001));
        
            RenderEntitySetPosition(gSegment, x, i*0.05f, z);
            
            MaterialSetColor(gSegment->mMaterial, 1.0f, 1.0f, 1.0f, 1.0f);
            RenderEntityDrawCached(gSegment, gRnd);
        }
     
        RenderEntityFlush();
        
        for(i=0;i<lMax2;i++)
        {
            float x = 4.0f * cos(i*(pUpdate->mTime * 0.00001));
            float z = 4.0f * sin(i*(pUpdate->mTime * 0.00001));
        
            RenderEntitySetPosition(gSegment, z, i*0.05f, x);
            
            MaterialSetColor(gSegment->mMaterial, 0.8f, 0.0f, 0.0f, 1.0f);
            RenderEntityDrawCached(gSegment, gRnd);
        }
        
        RenderEntityFlush();
    }
    
	gRnd->EndFrame();
}

void DemoShutdown(void)
{        
    RenderEntityDestroy(gIntro);
    RenderEntityDestroy(gOutro);

    RenderEntityDestroy(gSegment);
    RenderEntityDestroy(gSky);
    
    GardenDestroy(gGarden);
    
#ifdef MUSIC
    MusicDestroy(gMusic);
#endif  
   
    CameraDestroy(gCamera);
	RendererDestroy(gRnd);
}
