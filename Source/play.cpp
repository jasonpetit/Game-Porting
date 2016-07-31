//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.cpp

#include "play.h"
#include "explode.h"
#include <string>
#include <sstream>
#include "credits.h"
#include "SDLHeaders.h"

using namespace std;

LPD3DXFONT font;

SDL_Surface *Game_Surf = NULL;
SDL_Surface *Asteroid = NULL;
SDL_Surface *Ship = NULL;
SDL_Surface *Bullet = NULL;

CSound *sound_explode = NULL;
CSound *sound_fire = NULL;

const int numasteroid = 10;
static bool ShipDestroyed = false;
int score = 0;
int lives = 3;

SPRITE asteroid[numasteroid], ship, bullet, fonts;

Explode xplode;
Credits creds;

bool Play::Game_Init(HWND window)
{
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	//I haven't added the screen variables in SDL yet, but when I do the screen will be set up here.

	sound_fire = LoadSound("blaster.wav");
	sound_explode = LoadSound("blast.wav");

	//create Font for the score
	font = MakeFont("STENCIL", 24);

	Game_Surf = load_image("Starfield.bmp");

	if (Game_Surf == NULL)
	{
		return false;
	}

	creds.Game_Init(window);

	Asteroid = load_image("asteroid.tga");

	//asteroids properties
	for (int n = 0; n < numasteroid; n++)
	{
		asteroid[n].x = (float)(rand() % (SCREENW - 65));
		asteroid[n].y = (float)(rand() % (SCREENH - 65));
		asteroid[n].width = 60;
		asteroid[n].height = 60;
		asteroid[n].columns = 8;
		asteroid[n].startframe = 0;
		asteroid[n].endframe = 63;
		asteroid[n].delay = 150;
		asteroid[n].velx = 0.25f;
		asteroid[n].vely = 0.25f;
	}

	Ship = load_image("ships.png");

	//ship properties
	ship.x = 475;
	ship.y = 350;
	ship.width = ship.height = 36;
	ship.columns = 8;
	ship.startframe = 0;
	ship.endframe = 0;
	ship.endframe = 0;
	ship.delay = 120;

	Bullet = load_image("SpaceBu.bmp");

	//bullet Properties
	bullet.width = 35;
	bullet.height = 35;
	bullet.vely = 1.0f;

	xplode.Load();

	return true;
}

void rebound(SPRITE &sprite1, SPRITE &sprite2)
{
	float centerx1 = sprite1.x + sprite1.width / 2;
	float centery1 = sprite1.y + sprite1.height / 2;

	float centerx2 = sprite2.x + sprite2.width / 2;
	float centery2 = sprite2.y + sprite2.height / 2;

	if (centerx1 < centerx2)
	{
		sprite1.velx = fabs(sprite1.velx) * -1;
	}
	else if (centerx1 > centerx2)
	{
		sprite1.velx = fabs(sprite1.velx);
	}

	if (centery1 < centery2)
	{
		sprite1.vely = fabs(sprite1.vely) * -1;
	}
	else
	{
		sprite1.vely = fabs(sprite1.vely);
	}

	sprite1.x += sprite1.velx;
	sprite1.y += sprite1.vely;
}

void Play::Game_Run(HWND window)
{
	if (!d3ddev)
		return;

	D3DXVECTOR2 trans((float)0, (float)0);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, 0, 0, 0, &trans);
	spriteobj->SetTransform(&mat);

	DirectInput_Update();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);

	//display font
	stringstream out;
	out << score;
	string s = "Score: ";
	s += out.str();

	stringstream outs;
	outs << lives;
	string l = "Lives: ";
	l += outs.str();

	FontPrint(font, 0, 0, s);
	FontPrint(font, 0, 20, l);


	static bool showBullet = false;
	static bool keyRelease = true;

	int n;

	for (n = 0; n < numasteroid; n++)
	{
		asteroid[n].x += asteroid[n].velx;
		asteroid[n].y += asteroid[n].vely;
		if (asteroid[n].x < 0 || asteroid[n].x > SCREENW - asteroid[n].width)
		{
			asteroid[n].velx *= -1;
		}
		if (asteroid[n].y < 0 || asteroid[n].y > SCREENH - asteroid[n].height)
		{
			asteroid[n].vely *= -1;
		}
	}

	//check for sprite collisions

	for (int one = 0; one < numasteroid; one++)
	{
		for (int two = 0; two < numasteroid; two++)
		{
			if (one != two)
			{
				if (CollisionD(asteroid[one], asteroid[two]))
				{
					while (CollisionD(asteroid[one], asteroid[two]))
					{
						//rebound asteroid one
						rebound(asteroid[one], asteroid[two]);

						//rebounf asteroid two
						rebound(asteroid[two], asteroid[one]);
					}
				}
			}
		}
	}

	static bool doExplosion = false;
	static bool doExplosions = false;
	static float explodeX, explodeY;
	static float shipX, shipY;

	for (int one = 0; one < numasteroid; one++)
	{
		if (CollisionD(bullet, asteroid[one]))
		{
			asteroid[one].x = -999;
			bullet.y = bullet.y - 35;
			explodeX = bullet.x;
			explodeY = bullet.y;
			score += 100;
			doExplosion = true;
			PlaySound(sound_explode);
		}
	}

	for (int one = 0; one < numasteroid; one++)
	{
		if (CollisionD(ship, asteroid[one]))
		{
			shipX = ship.x;
			shipY = ship.y;
			ship.x = -1999;
			doExplosions = true;
			PlaySound(sound_explode);
			asteroid[one].velx *= -1;
			lives -= 1;
			if (lives > 0)
			{
				ship.x = 500;
			}
		}
	}

	for (n = 0; n <numasteroid; n++)
	{
		Sprite_Animate(asteroid[n].frame, asteroid[n].startframe, asteroid[n].endframe, asteroid[n].direction, asteroid[n].starttime, asteroid[n].delay);
	}

	if (Key_Down(DIK_UP))
	{
		ship.y -= 0.55f;
		if (ship.y < 0)
			ship.y = 0;
	}

	if (Key_Down(DIK_LEFT))
	{
		ship.x -= 0.55f;
		if (ship.x < 0)
			ship.x = 0;
	}

	if (Key_Down(DIK_DOWN))
	{
		ship.y += 0.55f;
		if (ship.y > SCREENH - ship.height)
			ship.y = SCREENH - ship.height;
	}

	if (Key_Down(DIK_RIGHT))
	{
		ship.x += 0.55f;
		if (ship.x > SCREENW - ship.width)
			ship.x = SCREENW - ship.width;
	}

	if (showBullet == false)
	{
		if (Key_Down(DIK_SPACE) && keyRelease)
		{
			showBullet = true;
			bullet.x = ship.x;
			bullet.y = ship.y;
			keyRelease = false;
			PlaySound(sound_fire);
		}
		if (!Key_Down(VK_SPACE))
		{
			keyRelease = true;
		}
	}
	else
	{
		if (Key_Down(DIK_SPACE))
		{
			showBullet = false;
		}
	}

	Sprite_Animate(ship.frame, ship.startframe, ship.endframe, ship.direction, ship.starttime, ship.delay);

	//start rendering
	if (d3ddev->BeginScene())
	{
		//start sprite handler
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

		d3ddev->StretchRect(Game_Surf, NULL, backbuffer, NULL, D3DTEXF_NONE);

		for (n = 0; n < numasteroid; n++)
		{
			Sprite_Transform_Draw(Asteroid,
				asteroid[n].x,
				asteroid[n].y,
				asteroid[n].width,
				asteroid[n].height,
				asteroid[n].frame,
				asteroid[n].columns);
		}

		Sprite_Transform_Draw(Ship, ship.x, ship.y, ship.width, ship.height, ship.frame, ship.columns);

		if (showBullet == true)
		{
			Sprite_Animate(bullet.frame, bullet.startframe, bullet.endframe, bullet.direction, bullet.starttime, bullet.delay);
			Sprite_Transform_Draw(Bullet, bullet.x, bullet.y, bullet.width, bullet.height, bullet.frame, bullet.columns);
			bullet.y -= bullet.direction;
		}

		if (doExplosion)
		{
			bullet.x = -1599;
			if (!xplode.explode(explodeX, explodeY)) // if NOT explosion, i.e. it is DONE
			{
				doExplosion = false;
			}
		}
		if (doExplosions)
		{
			bullet.x = -1599;
			if (!xplode.explode(shipX, shipY)) // if NOT explosion, i.e. it is DONE
			{
				doExplosions = false;
			}
		}

		if (lives <= 0)
		{
			spriteobj->End();
			
			creds.Game_Run(window);
		}
		//stop drawing
		spriteobj->End();


		//stop rendering
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}


void Play::Game_End()
{
	Game_Surf->Release();
	Asteroid->Release();
	Ship->Release();
	Bullet->Release();
	xplode.end();
}