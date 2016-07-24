//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.h

#ifndef PLAY_H
#define PLAY_H

#include "MyDirectX.h"
#include "DirectSound.h"
#include <time.h>
#include <cstdlib>

class Play
{
public:
	bool Game_Init(HWND window);
	void Game_Run(HWND window);
	void Game_End();
};

#endif