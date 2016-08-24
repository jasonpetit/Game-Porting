//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.cpp

//#include "explode.h"
//#include "credits.h"
#include "SDLHeaders.h"
#include "libheaders.h"
#include "Audio.h"
#include "ImgManager.h"
#include "Sprite.h"
#include "play.h"

// Goddamn Microsoft...
#undef DrawText

using namespace std;

const int SCREENW = 1024;
const int SCREENH = 768;
const int SCREEN_BP = 32;

extern Audio *audio;
extern ImageResourceManager *imgMan;
extern SDL_Surface *Screen;


int score = 0;
int lives = 3;
int destroyedAsteroids = 0;
bool win = false;
float winTimer = 0.f;

SDL_Surface *message = NULL;


//Explode xplode;
//Credits creds;

Play::Play() : State(STATE_PLAYING), hasLoadedResources(false), respawned(true), moveUp(false), moveDown(false), moveLeft(false), moveRight(false)
{

}

void Play::ProcessInput(SDL_Event &event)
{
	bool pressed = (event.type == SDL_KEYDOWN ? true : false);
	if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
		case SDLK_UP:
			moveUp = pressed;
			break;
		case SDLK_LEFT:
			moveLeft = pressed;
			break;
		case SDLK_DOWN:
			moveDown = pressed;
			break;
		case SDLK_RIGHT:
			moveRight = pressed;
			break;
		case SDLK_SPACE:
			if(event.type == SDL_KEYDOWN)
			{
				if(!bullet.IsActive())
				{
					//showBullet = true;
					bullet.SetPosition(ship.GetPosition().x, ship.GetPosition().y);
					bullet.Reactivate();
					audio->PlaySound("sound_fire");
				}
			}
			break;
		}
	}
}

bool Play::Init()
{
	//if(!hasLoadedResources)
	//{
		lives = 3;
		score = 0;
		destroyedAsteroids = 0;
		winTimer = 0.f;
		win = false;

		audio->StopMusic();
		audio->LoadSound("sound/blaster.wav", "sound_fire");
		audio->LoadSound("sound/blast.wav", "sound_explode");

		//create Font for the score
		font = TTF_OpenFont("fonts/lucon.ttf", 24);

		if(!imgMan->LoadFile("textures/Starfield.bmp", "Starfield"))
			return false;

		backGroundImage.AddFrame(imgMan->GetImage("Starfield"), 400);
		backGroundImage.SetStretch(true);

		imgMan->LoadFile("textures/asteroid.tga", "Asteroid");

		//asteroids properties
		for(int n = 0; n < numasteroid; n++)
		{
			asteroid[n].SetupSpriteSheet(imgMan->GetImage("Asteroid"), 8, 8, 64, 60, 60, 0, 0, 60, 0);
			asteroid[n].SetPosition((float)(rand() % (SCREENW - 65)), (float)(rand() % (SCREENH - 65)));
			float vx = (float)(rand() % 8) + 1 / (float)(rand() % 8) + 1;
			float vy = (float)(rand() % 8) + 1 / (float)(rand() % 8) + 1;
			vx *= 0.1f;
			vy *= 0.1f;
			asteroid[n].SetInitialVelocity(vx, vy);

			// [NG] this is so stupid. Don't do this in real production code. But I don't have time to make better stuff.
			for(int i = 0; i < 64; ++i)
			{
				asteroid[n].AddSheetFrame(28.f);
			}
			asteroid[n].Reactivate();
		}

		imgMan->LoadFile("textures/ships.png", "Ships");

		//ship properties
		ship.SetupSpriteSheet(imgMan->GetImage("Ships"), 0, 0, 1, 36, 36, 0, 0, 0, 0);
		ship.AddSheetFrame(120);
		ship.SetPosition(475, 350);


		imgMan->LoadFile("textures/SpaceBu.bmp", "Bullet");

		//bullet Properties
		bullet.AddFrame(imgMan->GetImage("Bullet"), 800);
		bullet.SetPosition(-500, 0);
		bullet.SetLooping(false);
		bullet.SetInitialVelocity(0, -3.f);
		bullet.Destroy();	// seems contradictory, but we will reactivate the bullet every time we want to fire it so this works. It's just kinda hacky...

		imgMan->LoadFile("textures/Explosions.png", "Explosions");
		explosion.SetupSpriteSheet(imgMan->GetImage("Explosions"), 8, 5, 40, 64, 64, 0, 256, 64, 0);
		for(int i = 0; i < 40; ++i)
		{
			explosion.AddSheetFrame(14.f);
		}
		explosion.SetLooping(false);
		explosion.Destroy();

		//hasLoadedResources = true;
	//}

	return true;
}

bool Play::Run()
{
	if(moveUp)
	{
		ship.Move(0, -0.55f);
		if(ship.GetPosition().y < 0)
			ship.SetPosition(ship.GetPosition().x, 0);
	}
	if(moveLeft)
	{
		ship.Move(-0.55f, 0);
		if(ship.GetPosition().x < 0)
			ship.SetPosition(0, ship.GetPosition().y);
	}
	if(moveDown)
	{
		ship.Move(0, 0.55f);
		if(ship.GetPosition().y > SCREENH - ship.GetRect().h)
			ship.SetPosition(ship.GetPosition().x, float(SCREENH - ship.GetRect().h));
	}
	if(moveRight)
	{
		ship.Move(0.55f, 0);
		if(ship.GetPosition().x > SCREENW - ship.GetRect().w)
			ship.SetPosition(float(SCREENW - ship.GetRect().w), ship.GetPosition().y);
	}

	for(int i = 0; i < numasteroid; ++i)
	{
		asteroid[i].Update();
		if(asteroid[i].GetPosition().x < 0 && asteroid[i].GetVelocityX() < 0)
		{
			asteroid[i].SetVelocityX(asteroid[i].GetVelocityX() * -1);
		}
		else if(asteroid[i].GetPosition().x > SCREENW - asteroid[i].GetRect().w && asteroid[i].GetVelocityX() > 0)
		{
			asteroid[i].SetVelocityX(asteroid[i].GetVelocityX() * -1);
		}

		if(asteroid[i].GetPosition().y < 0 && asteroid[i].GetVelocityY() < 0)
		{
			asteroid[i].SetVelocityY(asteroid[i].GetVelocityY() * -1);
		}
		else if(asteroid[i].GetPosition().y > SCREENH - asteroid[i].GetRect().h && asteroid[i].GetVelocityY() > 0)
		{
			asteroid[i].SetVelocityY(asteroid[i].GetVelocityY() * -1);
		}
	}
	ship.Update();

	// [KB] I put in the showBullet bool again, and set it to update and draw the bullet when it is active. This should still work with the controls that I set up before.
	// [NG] this is actually unnecessary, as there is already code within Update() and Draw() that checks to make sure the Sprite is active, so might as well just call this every time anyway
	bullet.Update();
	explosion.Update();

	//display font
	stringstream out;
	out << score;
	string s = "Score: ";
	s += out.str();

	stringstream outs;
	outs << lives;
	string l = "Lives: ";
	l += outs.str();

	backGroundImage.Draw();

	DrawText(0, 0, font, Screen, s, MakeColor(255, 255, 255));
	DrawText(0, 20, font, Screen, l, MakeColor(255, 255, 255));


	if(!win)
	{
		//check for sprite collisions

		/*
		for(int one = 0; one < numasteroid; one++)
		{
			for(int two = 0; two < numasteroid; two++)
			{
				if(one != two)
				{
					if(Collision(asteroid[one], asteroid[two]))
					{
						if(Collision(asteroid[one], asteroid[two]))
						{
							//rebound asteroid one
							rebound(asteroid[one], asteroid[two]);

							//rebound asteroid two
							rebound(asteroid[two], asteroid[one]);
						}
					}
				}
			}
		}
		*/

		for(int one = 0; one < numasteroid; one++)
		{
			if(Collision(bullet, asteroid[one]))
			{
				asteroid[one].Move(-999, 0);
				asteroid[one].Destroy();
				bullet.Move(0, -35);
				explosion.SetPosition(bullet.GetPosition().x, bullet.GetPosition().y);
				explosion.Reactivate();
				//explosion.RestartAnimation();
				score += 100;
				audio->PlaySound("sound_explode");
				bullet.Destroy();

				destroyedAsteroids++;
				if(destroyedAsteroids >= numasteroid)
				{
					win = true;
					winTimer = SDL_GetTicks();
				}
			}
		}

		for(int one = 0; one < numasteroid; one++)
		{
			if(Collision(ship, asteroid[one]))
			{
				ship.SetPosition(-1999, ship.GetPosition().y);
				explosion.SetPosition(ship.GetPosition().x, ship.GetPosition().y);
				explosion.Reactivate();
				//explosion.RestartAnimation();
				audio->PlaySound("sound_explode");
				asteroid[one].SetVelocityX(asteroid[one].GetVelocityX() * -1);
				lives--;
				if(lives > 0)
				{
					ship.SetPosition(500, ship.GetPosition().y);
				}
				else
				{
					SetNextState(STATE_INCREDITS);
					return false;
				}
			}
		}
	}
	else
	{
		DrawText((SCREENW / 2) - 50, (SCREENH / 2) - 30, font, Screen, "You Win!", MakeColor(255, 255, 255));
		if(SDL_GetTicks() > winTimer + 5000)
		{
			SetNextState(STATE_MAINMENU);
			return false;
		}
	}

	for(int i = 0; i < numasteroid; ++i)
	{
		asteroid[i].Draw();
	}
	ship.Draw();
	bullet.Draw();
	explosion.Draw();

	return true;
}

void Play::End()
{
	ship = bullet = explosion = backGroundImage = Sprite();
	for(int i = 0; i < numasteroid; ++i)
	{
		asteroid[i] = Sprite();
	}
}

bool Play::Collision(Sprite &sprite1, Sprite &sprite2)
{
	if(!sprite1.IsActive() || !sprite2.IsActive())
		return false;
	SDL_Rect rect1 = sprite1.GetRect();
	SDL_Rect rect2 = sprite2.GetRect();

	return Intersection(rect1, rect2);
}

bool Play::Intersection(SDL_Rect A, SDL_Rect B)
{
	// Taken from Lazy Foo's tutorials
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	// Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	// If any of the sides from A are outside of B
	if(bottomA <= topB)
	{
		return false;
	}

	if(topA >= bottomB)
	{
		return false;
	}

	if(rightA <= leftB)
	{
		return false;
	}

	if(leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

/*
void rebound(Sprite &sprite1, Sprite &sprite2)
{
	SDL_Rect spr1Bounds = sprite1.GetRect();
	SDL_Rect spr2Bounds = sprite2.GetRect();
	int centerx1 = spr1Bounds.x + spr1Bounds.w / 2;
	int centery1 = spr1Bounds.y + spr1Bounds.h / 2;

	int centerx2 = spr2Bounds.x + spr2Bounds.w / 2;
	int centery2 = spr2Bounds.y + spr2Bounds.h / 2;

	if (centerx1 < centerx2)
	{
		sprite1.SetVelocityX(std::fabs(sprite1.GetVelocityX()) * -1);
	}
	else if (centerx1 > centerx2)
	{
		sprite1.SetVelocityX(std::fabs(sprite1.GetVelocityX()));
	}

	if (centery1 < centery2)
	{
		sprite1.SetVelocityY(std::fabs(sprite1.GetVelocityY()) * -1);
	}
	else
	{
		sprite1.SetVelocityY(std::fabs(sprite1.GetVelocityY()));
	}

	sprite1.Move(sprite1.GetVelocityX(), sprite1.GetVelocityY());
}
*/

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
/*
void Play::Game_Run()
{
	if (!d3ddev)
		return;

	D3DXVECTOR2 trans((float)0, (float)0);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, 0, 0, 0, &trans);
	spriteobj->SetTransform(&mat);

	DirectInput_Update();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);


		
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
*/