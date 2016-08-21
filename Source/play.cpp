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
#include "libheaders.h"
#include "Audio.h"
#include "ImgManager.h"
#include "Sprite.h"

using namespace std;

extern Audio *audio;
extern ImageResourceManager *imgMan;

SDL_Surface *Game_Surf = NULL;
SDL_Surface *Asteroid = NULL;
SDL_Surface *Ship = NULL;
SDL_Surface *Bullet = NULL;

SDL_Event event;

Mix_Chunk *sound_explode = NULL;
Mix_Chunk *sound_fire = NULL;

static bool ShipDestroyed = false;
static bool showBullet = false;
int score = 0;
int lives = 3;

SDL_Surface *message = NULL;


Explode xplode;
Credits creds;

void Play::ProcessInput(SDL_Event &event)
{
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
		case SDLK_UP:
			ship.Move(0, -0.55f);
			if(ship.GetPosition.y < 0)
				ship.SetPosition(ship.GetPosition.x, 0);
			break;
		case SDLK_LEFT:
			ship.Move(-0.55f, 0);
			if(ship.GetPosition.x < 0)
				ship.SetPosition(0, ship.GetPosition.y);
			break;
		case SDLK_DOWN:
			ship.Move(0, 0.55f);
			if(ship.GetPosition.y > SCREENH)
				ship.SetPosition(ship.GetPosition.x, SCREENH);
			break;
		case SDLK_RIGHT:
			ship.Move(0.55f, 0);
			if(ship.GetPosition.x > SCREENW)
				ship.SetPosition(SCREENW, ship.GetPosition.y);
			break;
		case SDLK_SPACE:
			if(!showBullet)
			{
				showBullet = true;
				bullet.SetPosition(ship.GetPosition.x, ship.GetPosition.y);
				Mix_PlayChannel(-1, sound_fire, 0);
			}
			else
			{
				showBullet = false;
			}
			break;
		}
	}
}

bool Play::Init()
{
	if(!hasLoadedResources)
	{
		audio->LoadSound("sounds/blaster.wav", "sound_fire");
		audio->LoadSound("sounds/blast.wav", "sound_explode");

		//create Font for the score
		font = TTF_OpenFont("fonts/lucon.ttf", 24);

		if(!imgMan->LoadFile("Starfield.bmp", "Starfield"))
			return false;

		// TODO: Fixme
		// [NG] Credits needs to be replaced with the new State-derived class.
		// This might be a tad complex, so perhaps leave that to me.
		creds.Game_Init();

		imgMan->LoadFile("asteroid.tga", "Asteroid");

		//asteroids properties
		for(int n = 0; n < numasteroid; n++)
		{
			asteroid[n].SetupSpriteSheet(imgMan->GetImage("Asteroid"), 8, 8, 64, 60, 80, 0, 0, 60, 80);
			asteroid[n].SetPosition((float)(rand() % (SCREENW - 65)), (float)(rand() % (SCREENH - 65)));

			// [NG] this is so stupid. Don't do this in real production code. But I don't have time to make better stuff.
			for(int i = 0; i < 64; ++i)
			{
				asteroid[n].AddSheetFrame(150.f);
			}
		}

		imgMan->LoadFile("ships.png", "Ships");

		//ship properties
		ship.SetupSpriteSheet(imgMan->GetImage("Ships"), 0, 0, 1, 36, 36, 0, 0, 0, 0);
		ship.AddSheetFrame(120);
		ship.SetPosition(475, 350);


		imgMan->LoadFile("SpaceBu.bmp", "Bullet");

		//bullet Properties
		bullet.AddFrame(imgMan->GetImage("Bullet"), 300);
		bullet.SetLooping(false);
		bullet.SetInitialVelocity(0, 1.f);

		imgMan->LoadFile("Explosions.png", "Explosions");
		explosion.SetupSpriteSheet(imgMan->GetImage("Explosions"), 8, 5, 40, 64, 64, 0, 256, 64, 0);

		hasLoadedResources = true;
	}

	return true;
}

bool Play::Run()
{
	for(int i = 0; i < numasteroid; ++i)
	{
		asteroid[i].Update();
	}
	ship.Update();

	// [KB] I put in the showBullet bool again, and set it to update and draw the bullet when it is active. This should still work with the controls that I set up before.
	if (showBullet)
		bullet.Update();

	for(int i = 0; i < numasteroid; ++i)
	{
		asteroid[i].Draw();
	}
	ship.Draw();
	if (showBullet)
		bullet.Draw();
}

// TODO: fixme. This will require adding something to get the bounds of the sprite to the Sprite class
// probably best to use startingRect.w and startingRect.h as the boundaries.
// so, create a function in the sprite class to return startingRect, and go from there.
void rebound(Sprite &sprite1, Sprite &sprite2)
{
	float centerx1 = sprite1.x + sprite1.width / 2;
	float centery1 = sprite1.y + sprite1.height / 2;

	float centerx2 = sprite2.x + sprite2.width / 2;
	float centery2 = sprite2.y + sprite2.height / 2;

	if (centerx1 < centerx2)
	{
		sprite1.velx = std::abs(sprite1.velx) * -1;
	}
	else if (centerx1 > centerx2)
	{
		sprite1.velx = std::abs(sprite1.velx);
	}

	if (centery1 < centery2)
	{
		sprite1.vely = std::abs(sprite1.vely) * -1;
	}
	else
	{
		sprite1.vely = std::abs(sprite1.vely);
	}

	sprite1.x += sprite1.velx;
	sprite1.y += sprite1.vely;
}

// TODO: move this stuff out of this function to the other Run() function
// be sure to have it flow properly in terms of logic
// [NG] SDL_PollEvent should only ever really run in the main() function, or you risk
// the chance of popping events off the stack in places you shouldn't have.
// if you need to have input events processed elsewhere (such as in this instance)
// then you need to pass the unprocessed event data to a function from the main() function.
// I can probably set this up later if this is too confusing/difficult

// One last note here: all SDL_Mixer calls can be replaced with calls to the Audio class
// e.g. audio->PlaySound(). The extern pointer at the top should link to the one in main.cpp
// and thus the Audio system should be able to be accessed from here (same with the Image Manager)
void Play::Game_Run()
{
	/*if (!d3ddev)
		return;

	D3DXVECTOR2 trans((float)0, (float)0);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, 0, 0, 0, &trans);
	spriteobj->SetTransform(&mat);

	DirectInput_Update();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);*/

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
			Mix_PlayChannel(-1, sound_explode, 0);
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
			Mix_PlayChannel(-1, sound_explode, 0);
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
	
	/*if (Key_Down(DIK_UP))
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
			Mix_PlayChannel(-1, sound_fire, 0);
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
	}*/

	Sprite_Animate(ship.frame, ship.startframe, ship.endframe, ship.direction, ship.starttime, ship.delay);

	//start rendering
	if (d3ddev->BeginScene())
	{
		//start sprite handler
		spriteobj->Begin(D3DXSprite_ALPHABLEND);

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
			
			creds.Game_Run();
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
	SDL_FreeSurface(Game_Surf);
	SDL_FreeSurface(Asteroid);
	SDL_FreeSurface(Ship);
	SDL_FreeSurface(Bullet);
	xplode.end();
}