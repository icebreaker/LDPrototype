/* Copyright (c) 2010, Mihail Szabolcs */
#ifndef DEMO_H
#define DEMO_H

#include "../framework/framework_private.h"

/*!
    \file demo.h
    \brief Demo Application
*/

/*! Demo Configuration */
void DemoConfig(TConfig *pConfig);
/*! Demo Initialization */
bool DemoInit(const TConfig *pConfig);
/*! Demo Update */
bool DemoUpdate(const TConfig *pConfig, TUpdate *pUpdate);
/*! Demo Render */
void DemoRender(const TConfig *pConfig, TUpdate *pUpdate);
/*! Demo Shutdown / Clean-Up */
void DemoShutdown(void);
	
#endif
