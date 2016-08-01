//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// MyGame.cpp

#include "MyDirectX.h"
#include "DirectSound.h"
#include "SDLHeaders.h"
#include "menu.h"

using namespace std;

//const string APPTITLE = "BATTLE GALAXY";
const int SCREENW = 1024;
const int SCREENH = 768;
const int SCREEN_BP = 32;

SDL_Surface *Screen;

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

	//initialize DirectSound
	if (!DirectSound_Init(window))
	{
		MessageBox(window, "Error initializing DirectSound", APPTITLE.c_str(), 0);
		return false;
	}

	menu.Game_Init();

	return true;
}

void Game_Run(HWND window)
{
	static bool keyRelease = false;

	if (!d3ddev)
		return;

	DirectInput_Update();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);

	//start rendering
	if (d3ddev->BeginScene())
	{

		//start sprite handler
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

		//stop drawing
		spriteobj->End();

		menu.Game_Run(window);

		//stop rendering
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	//exit with escape key
	if (KEY_DOWN(VK_ESCAPE))
		gameover = true;
}

void Game_End()
{
	menu.Game_end();
	DirectSound_Shutdown();
	SDL_Quit();
}