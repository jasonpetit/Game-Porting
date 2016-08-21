//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//menu.h

#ifndef MENU_H
#define MENU_H

#include "MyDirectX.h"
#include "SDLHeaders.h"
#include "State.h"
#include "Sprite.h"

using namespace std;

class Menu : public State
{
public:
	Menu() : State(), hasLoadedResources(false) {}
	virtual bool Init();
	virtual bool Run();
private:
	bool hasLoadedResources;

	Sprite playT, exitT, creditsT, title, backG;
};

#endif 