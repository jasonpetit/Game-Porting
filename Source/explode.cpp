//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//explode.cpp

#include "explode.h"
#include "SDLHeaders.h"

SDL_Surface Xplode = NULL;

SPRITE xplode;

bool Explode::Load()
{
	Xplode = LoadTexture("Explosions.png");

	//properties
	//Xplode properties
	xplode.width = xplode.height = 64;
	xplode.columns = 8;
	xplode.startframe = 0;
	xplode.endframe = 28;
	xplode.delay = 25;

	return true;
}

bool Explode::explode(float x, float y)
{
	xplode.x = x;
	xplode.y = y;
	Sprite_Animate(xplode.frame, xplode.startframe, xplode.endframe, xplode.direction, xplode.starttime, xplode.delay);
	Sprite_Transform_Draw(Xplode, xplode.x, xplode.y, xplode.width, xplode.height, xplode.frame, xplode.columns);

	if (xplode.frame == xplode.endframe)
	{
		xplode.frame = xplode.startframe;
		return false;
	}
	else
	{
		return true;
	}
}

void Explode::end()
{
	Xplode->Release();
}