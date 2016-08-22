//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//credits.h
#pragma once

#ifndef CREDITS_H
#define CREDITS_H

#include "SDLHeaders.h"
#include "libheaders.h"
#include "State.h"
#include "Sprite.h"

using namespace std;

class Credits : public State
{
public:
	Credits() : State(STATE_INCREDITS), hasLoadedResources(false) {}
	virtual bool Init();
	virtual bool Run();

private:
	// Laziness~
	TTF_Font *m_creditFont;
	TTF_Font *m_roleFont;
	TTF_Font *m_nameFont;

	Sprite backSurface;

	bool hasLoadedResources;

	int gTimer, moveTimer;

	float iTextY;
};

#endif