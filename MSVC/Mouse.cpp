#include "menu.h"
#include "credits.h"
#include "play.h"
#include "Enum.h"
#include "Audio.h"
#include "ImgManager.h"
#include "Sprite.h"
#include "Mouse.h"

//Mouse button sprites
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
Mouse gButtonSpriteSheetTexture;


//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

//Hard set
enum MOUSE_OVER_BUTTON
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

//Constructor
Mouse::Mouse()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Mouse::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

bool Mouse::MouseHandler()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Mouse::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Mouse::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
	}
	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (x < mPosition.x)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > mPosition.x + BUTTON_WIDTH)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < mPosition.y)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > mPosition.y + BUTTON_HEIGHT)
	{
		inside = false;
	}
	//Mouse is outside button
	if (!inside)
	{
		mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}
	//Mouse is inside button
	else
	{
		//Set mouse over sprite
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
			break;

		case SDL_MOUSEBUTTONDOWN:
			mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
			break;
		}
	}

}

void Mouse::render()
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
