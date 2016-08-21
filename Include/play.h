//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.h

#ifndef PLAY_H
#define PLAY_H

//#include "MyDirectX.h"
#include "SDLHeaders.h"
#include "libheaders.h"
#include "State.h"

const int numasteroid = 10;

class Play : public State
{
public:
	Play() : State(), hasLoadedResources(false) {}

	//Game functions
	virtual void ProcessInput(SDL_Event &event);
	virtual bool Init();
	virtual bool Run();
	
private:
	bool hasLoadedResources;
	TTF_Font *font;
	Sprite asteroid[numasteroid], ship, bullet, explosion;
};
#endif