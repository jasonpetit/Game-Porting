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
	virtual void ProcessInput(SDL_Event &event);
	virtual bool Init();
	virtual bool Game_Run();

	// Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render();
private:
	bool hasLoadedResources;

	Sprite playT, exitT, creditsT, title, backG;
};

#endif 