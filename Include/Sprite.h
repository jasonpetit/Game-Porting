#pragma once

#include "SDLHeaders.h"


// It's a real shame we're stuck to SDL 1.2; SDL 2 has rotation and flipping options, among many other cool features

class Sprite
{
public:
	Sprite()
	{
		frame = 0;
		columns = 1;
		width = height = 0;
		startframe = endframe = 0;
		direction = 1;
		starttime = delay = 0;
		velx = vely = 0;		
	}



private:

	//offsets
	float x, y;
	//rate of movement
	float velx, vely;
	//current frame
	int frame, columns;
	//animation status
	int status;
	//frame dimensions
	int width, height;
	//controls
	int startframe, endframe;
	int starttime, delay;
	int direction;

};