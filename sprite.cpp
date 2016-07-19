#include "sprite.h"
#include "debug.h"
#include <cstdlib>
#include <time.h>

using namespace std;

SPRITE ships;
SPRITE asteroid;

LPDIRECT3DTEXTURE9 imgShip = NULL;
animate rightAnimate;
animate leftAnimate;
animate downAnimate;
animate upAnimate;
animate currentAn;
animate *currentAnimate;

LPDIRECT3DTEXTURE9 aster_text = NULL;

bool play;

bool ship::Game_Init(HWND window)
{

	imgShip = LoadTexture("ships.png");
    if (!imgShip) 
		return false;

	//set properties for sprites
	ships.x = 500;
	ships.y = 300;
	ships.width = ships.height = 36;
	ships.columns = 8;
	ships.width = ships.height = 36;
	ships.startframe = rightAnimate.start = 0;
	ships.endframe =rightAnimate.stop = 10;
	ships.startframe = leftAnimate.start = 21;
	ships.endframe =leftAnimate.stop = 40;
	ships.startframe = currentAn.start;
	ships.endframe = downAnimate.stop = 20;
    ships.delay = 50;

	srand(time(NULL));

	aster_text = LoadTexture("asteroid.tga");
	if(!aster_text)
		return false;

	// set the proerties
	asteroid.x = (float)(rand() %(SCREENW - 65));
	asteroid.y = (float)(rand() %(SCREENH - 65));
	asteroid.width = asteroid.height = 60;
	asteroid.columns = 8;
	asteroid.startframe = 0;
	asteroid.endframe = 63;
	asteroid.delay = 70;
	asteroid.velx = 0.0f;

	return true;
}

void ship::Game_Run(HWND window)
{
	if (!d3ddev) 
		return;

    DirectInput_Update();

	currentAn.start = ships.frame;
	currentAn.stop = ships.frame;
	ships.startframe = currentAn.start;
	ships.endframe = currentAn.stop;

	if (Key_Down(DIK_RIGHT))
	{
		TRACE("currentAn: %d, %d\n", currentAn.start, currentAn.stop);
		TRACE("ship frames: %d, %d\n", ships.startframe, ships.endframe);
		
		if (currentAnimate != &rightAnimate)
		{
			ships.frame = currentAn.start;
			currentAnimate = &rightAnimate;
			play = false;
		}

		if(currentAn.start < rightAnimate.stop)
		{
			ships.startframe = currentAn.start;
			ships.endframe = rightAnimate.stop;
		}

		ships.x += 2.5f;
	}

	if (Key_Down(DIK_LEFT))
	{
		TRACE("currentAn: %d, %d\n", currentAn.start, currentAn.stop);
		TRACE("ship frames: %d, %d\n", ships.startframe, ships.endframe);

		if (currentAnimate != &leftAnimate)
		{
			ships.frame = currentAn.start;
			currentAnimate = &leftAnimate;
			play = false;
		}
		ships.startframe = currentAn.start;
		ships.endframe =leftAnimate.stop = 30;
		ships.x -= 2.5f;
	}

	if (KEY_DOWN(VK_UP))
	{
		if (currentAnimate != &upAnimate)
		{
			ships.frame = currentAn.start;
			currentAnimate = &upAnimate;
			play = false;
		}
		ships.startframe = currentAn.start;
		ships.endframe =upAnimate.stop = 39;
		ships.scaling = -1;
		ships.y -= 2.5f;
	}

	if (KEY_DOWN(VK_DOWN))
	{
		if (currentAnimate != &downAnimate)
		{
			ships.frame = currentAn.start;
			currentAnimate = &downAnimate;
			play = false;
		}

		ships.startframe = currentAn.start;
		ships.endframe = downAnimate.stop;
		ships.y += 2.5f;
	}

	//keep the sprite inside the screen
	if(ships.x < 0)
		ships.x = 0;
	if(ships.x > SCREENW-35)
		ships.x = SCREENW-35;
	if(ships.y < 0)
		ships.y = 0;
	if(ships.y > SCREENH-35)
		ships.y = SCREENH-35;

	if (CollisionD(ships, asteroid))
	{
		asteroid.velx *= -1;
		asteroid.vely *= 1;
	}
	//animate the ship

        Sprite_Animate( ships.frame, ships.startframe, ships.endframe, 1, ships.starttime, ships.delay, play);

		Sprite_Transform_Draw(imgShip, ships.x, ships.y, ships.width, ships.height, 
			ships.frame, ships.columns);

		Sprite_Animate(asteroid.frame, asteroid.startframe, asteroid.endframe, asteroid.direction, asteroid.starttime, asteroid.delay, true);
		Sprite_Transform_Draw(aster_text, asteroid.x, asteroid.y, asteroid.width, asteroid.height, asteroid.frame, asteroid.columns);
}

void ship::Game_End()
{
	if (imgShip) 
		imgShip->Release();
	aster_text->Release();
}