#ifndef SPRITE_H
#define SPRITE_H

#include "MyDirectX.h"

using namespace std;

struct animate
{
public:
	int start;
	int stop;
};

class ship
{
public:
	bool Game_Init(HWND window);
	void Game_Run(HWND window);
	void Game_End();
	animate animates;
};

#endif