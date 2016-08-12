//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// MyGame.cpp

//#include "MyDirectX.h"
//#include "DirectSound.h"
#include "SDLHeaders.h"
#include "menu.h"

using namespace std;

//const string APPTITLE = "BATTLE GALAXY";
const int SCREENW = 1024;
const int SCREENH = 768;
const int SCREEN_BP = 32;

SDL_Surface *Screen;

SDL_Event event;

Menu menu;

bool Game_Init()
{
	srand(time(NULL));

	//initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	Screen = SDL_SetVideoMode(SCREENW, SCREENH, SCREEN_BP, SDL_SWSURFACE);

	//if there was an error
	if (Screen == NULL)
	{
		return false;
	}

	//set the caption
	SDL_WM_SetCaption("BATTLE GALAXY", NULL);

	//Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	menu.Game_Init();

	return true;
}



void Game_Run()
{
	static bool keyRelease = false;

	/*if (!d3ddev)
		return;

	DirectInput_Update();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);*/

	//start rendering
	/*if (d3ddev->BeginScene())
	{

		//start sprite handler
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

		//stop drawing
		spriteobj->End();

		menu.Game_Run();

		//stop rendering
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	//exit with escape key
	if (KEY_DOWN(VK_ESCAPE))
		gameover = true;*/

	while (!gameover)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					gameover = true;
			}
			else if (event.type == SDL_QUIT)
			{
				gameover = true;
			}
		}
		//update the screen
		if (SDL_Flip(Screen) == -1)
		{
			return;
		}
	}
}

void Game_End()
{
	menu.Game_end();
	SDL_Quit();
}