#pragma once

#include "SDLHeaders.h"


struct Vector2D
{
	float x, y;
};


enum
{
	ANIMATE_FRAMES = 0,
	ANIMATE_SHEET,
};

struct AnimFrame
{
	SDL_Surface *Texture;
	float delay;
	AnimFrame *nextFrame;
};

// It's a real shame we're stuck to SDL 1.2; SDL 2 has rotation and flipping options, among many other cool features

class Sprite
{
public:
	Sprite()
	{		
	}
	
private:
	// position
	Vector2D pos;

	SDL_Rect imgRect;

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