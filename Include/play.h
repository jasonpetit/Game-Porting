//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.h
#pragma once

#ifndef PLAY_H
#define PLAY_H

//#include "MyDirectX.h"
#include "SDLHeaders.h"
#include "libheaders.h"
#include "State.h"
#include "Sprite.h"

const int numasteroid = 10;

void rebound(Sprite &sprite1, Sprite &sprite2);

class Play : public State
{
public:
	Play();

	//Game functions
	virtual void ProcessInput(SDL_Event &event);
	virtual bool Init();
	virtual bool Run();
	virtual void End();

	bool Collision(Sprite &sprite1, Sprite &sprite2);
	bool Intersection(SDL_Rect A, SDL_Rect B);
	/*
	bool CollisionD(Sprite &sprite1, Sprite &sprite2)
	{
		double radius1, radius2;

		//calculate radius 1
		if(sprite1.width > sprite1.height)
			radius1 = (sprite1.width * sprite1.scaling) / 2.0;
		else
			radius1 = (sprite1.height * sprite1.scaling) / 2.0;

		//center point 1
		double x1 = sprite1.x + radius1;
		double y1 = sprite1.y + radius1;
		D3DXVECTOR2 vector1((float)x1, (float)y1);

		//calculate radius 2
		if(sprite2.width > sprite2.height)
			radius2 = (sprite2.width * sprite2.scaling) / 2.0;
		else
			radius2 = (sprite2.height * sprite2.scaling) / 2.0;

		//center point 2
		double x2 = sprite2.x + radius2;
		double y2 = sprite2.y + radius2;
		D3DXVECTOR2 vector2((float)x2, (float)y2);

		//calculate distance
		double deltax = vector1.x - vector2.x;
		double deltay = vector2.y - vector1.y;
		double dist = sqrt((deltax * deltax) + (deltay * deltay));

		//return distance comparison
		r
	}
	*/
	
private:
	bool respawned;
	bool hasLoadedResources;
	bool moveUp, moveDown, moveLeft, moveRight;
	TTF_Font *font;
	Sprite asteroid[numasteroid], ship, bullet, explosion, backGroundImage;
};
#endif