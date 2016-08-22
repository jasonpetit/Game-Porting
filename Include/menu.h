//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//menu.h
#pragma once

#ifndef MENU_H
#define MENU_H

#include "SDLHeaders.h"
#include "libheaders.h"
#include "State.h"
#include "Sprite.h"

using namespace std;

enum
{
	MENU_PLAY = 0,
	MENU_QUIT,
	MENU_CREDITS,

	MAX_MENU_ITEMS
};

class Menu : public State
{
public:
	Menu() : State(STATE_MAINMENU), hasLoadedResources(false), leavingMenu(false) {}
	virtual void ProcessInput(SDL_Event &event);
	virtual bool Init();
	virtual bool Run();

	void ProcessMenuItem(int item);
	void ProcessSelection();

	/*
	// Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render();
	*/

private:
	bool hasLoadedResources;
	bool leavingMenu;

	int menuItem;

	Sprite playT, exitT, creditsT, title, backGround;
};

#endif 