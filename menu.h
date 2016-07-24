//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//menu.h

#ifndef MENU_H
#define MENU_H

#include "MyDirectX.h"

using namespace std;

class Menu
{
public:
	bool Game_Init(HWND window);
	void Game_Run(HWND window);
	void Game_end();
};

#endif 