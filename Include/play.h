//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.h

#ifndef PLAY_H
#define PLAY_H

//#include "MyDirectX.h"
#include "SDLHeaders.h"
#include "DirectSound.h"
#include "libheaders.h"

class Play
{
public:
	//Game functions
	bool Game_Init();
	void Game_Run();
	void Game_End();


	void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay)
	{
		if ((int)GetTickCount() > starttime + delay)
		{
			starttime = GetTickCount();

			frame += direction;
			if (frame > endframe) frame = startframe;
			if (frame < startframe) frame = endframe;
		}
	}
};
#endif