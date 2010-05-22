/* Copyright (c) 2010, Mihail Szabolcs */
#include "framework.h"
#include <time.h>

/*!
    \file framework.c
    \brief Main Framework
*/

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
#else
int main(int argc, char *argv[])
#endif
{
	UNUSED(argc);
	UNUSED(argv);

	TUpdate lUpdate = {0,};
	TConfig lConfig = 
	{
		800 /* width */, 
		600 /* height */, 
		16 /* bpp */,
		false /* fullscreen */,
		"LeraPrototype", /* title */
		16, /* Hz */
		1, /* VSync */
		0, /* Multisampling (0 == disabled) */
		false, /* Grab Input */
		false, /* Hide Cursor */
		false, /* Center Cursor */
		false   /* Audio */
	};
	
	DemoConfig(&lConfig);
		
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		printf("SDL_init: %s\n", SDL_GetError());
		return -1;
	}
	
	/*! Initialize random seed */
    srand(time(NULL));
	
	if(lConfig.mAudio)
	{
	    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	    {
	        printf("Mix_OpenAudio: %s\n", Mix_GetError());
	        return -2;
	    }
	}
	
    /* Input */
	uint32 lCenterX = lConfig.mWidth / 2;
	uint32 lCenterY = lConfig.mHeight/ 2;

	if(lConfig.mGrabInput)
    	SDL_WM_GrabInput(SDL_GRAB_ON);

    if(lConfig.mHideCursor)
        SDL_ShowCursor(SDL_DISABLE);

    SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

	/* OpenGL */
    SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, lConfig.mVSync );

    if(lConfig.mMultiSampling)
    {
	    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, lConfig.mMultiSampling);
    }

    /* Window */
    uint32 lFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL;	
	if(lConfig.mFullScreen)	lFlags |= SDL_FULLSCREEN;
	
	SDL_Surface *lScreen = SDL_SetVideoMode(lConfig.mWidth, lConfig.mHeight, lConfig.mBpp, lFlags);
	if(lScreen == NULL)
	{
		printf("SDL_SetVideoMode: %s\n", SDL_GetError());
		return -3;
	}

	if(lConfig.mTitle!=NULL)
		SDL_WM_SetCaption(lConfig.mTitle, lConfig.mTitle);
    
    /* OpenGL Again */
    uint32 lError = 0;
    if((lError=glewInit()) != GLEW_OK)
    {
        printf("glewInit: %s\n", glewGetErrorString(lError));
        goto exit;
    }

    if(!GLEW_VERSION_2_0)
    {
        printf("OpenGL 2.0 is not available.\n");
        goto exit;
    }
    
    {
        int lTexImageUnits = 0;
        int lTexUnits = 0;

        glGetIntegerv(GL_MAX_TEXTURE_UNITS,&lTexUnits);
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&lTexImageUnits);

		printf("%d Texture and %d Image Units ...\n",lTexUnits, lTexImageUnits);
		if(lTexUnits<4)
		{
		    printf(" => WARNING: You don't seem to have at least 4 Texture Units ...\n");
		    goto exit;
		}
	}

    if(!GLEW_EXT_framebuffer_object)
    {
        printf(" => WARNING: GL_EXT_framebuffer_object is not supported ...\n");
        goto exit;
    }
    if(!GLEW_EXT_framebuffer_multisample)
    {
        printf(" => WARNING: GL_EXT_framebuffer_multisample is not supported ...\n");
        goto exit;
    }
    if(!GLEW_EXT_framebuffer_blit)
    {
        printf(" => WARNING: GL_EXT_framebuffer_blit is not supported ...\n");
        goto exit;
    }

    printf("Non Power Of Two Textures: %s\n", (GLEW_ARB_texture_non_power_of_two)?"yes":"no");
	
	/* Init the demo */
	if(!DemoInit(&lConfig))
		goto demo_exit;
		
    lUpdate.mStartTime = SDL_GetTicks();		
		
	/* Event Loop */
	while(1)
	{	
		SDL_Event lEvent;
		while (SDL_PollEvent(&lEvent))
		{
			switch(lEvent.type)
			{
				case SDL_QUIT:
				{
					lUpdate.mKeys[SDLK_ESCAPE] = true;
				}
				break;
			 	case SDL_KEYDOWN:
			 	{
			 		lUpdate.mKeys[lEvent.key.keysym.sym] = true;
        		}
      			break;
      			case SDL_KEYUP:
			 	{
			 		lUpdate.mKeys[lEvent.key.keysym.sym] = false;
        		}
      			break;
      			case SDL_MOUSEMOTION:
      			{
      			    lUpdate.mMouseX = lEvent.motion.x;
      			    lUpdate.mMouseY = lEvent.motion.y;
      			    lUpdate.mMouseDeltaX = lEvent.motion.xrel;
      			    lUpdate.mMouseDeltaY = lEvent.motion.yrel;
      			}
      			break;
			}
		}

		if(lUpdate.mKeys[SDLK_ESCAPE])
		{
		    lUpdate.mKeys[SDLK_ESCAPE] = false;
			goto demo_exit;
		}

		if(lConfig.mCenterCursor)
		    SDL_WarpMouse( lCenterX, lCenterY );

		if(!DemoUpdate(&lConfig, &lUpdate))
		    break;
		    
		DemoRender(&lConfig, &lUpdate);

		lUpdate.mLastTime = lUpdate.mTime;
		lUpdate.mTime = SDL_GetTicks();
		lUpdate.mElapsedTime = lUpdate.mTime - lUpdate.mStartTime;

		lUpdate.mDeltaTime = (lUpdate.mTime - lUpdate.mLastTime);		
		if(lUpdate.mDeltaTime < lConfig.mHz)
			SDL_Delay( lConfig.mHz - lUpdate.mDeltaTime );
	}

demo_exit:
	DemoShutdown();

exit:
    if(lConfig.mAudio)
    {
        Mix_CloseAudio();
    }
    
	SDL_Quit();

	printf("Sayonara ...\n");
	return 0;
}
