//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// MyGame.cpp

#include "MyDirectX.h"
#include "DirectSound.h"
#include "menu.h"

using namespace std;

const string APPTITLE = "BATTLE GALAXY";
const int SCREENW = 1024;
const int SCREENH = 768;

Menu menu;

bool Game_Init(HWND window)
{
	srand(time(NULL));

	//initialize Direct3D
	if (!Direct3D_Init(window, SCREENW, SCREENH, false))
	{
		MessageBox(window, "Error initializing Direct3D", APPTITLE.c_str(), 0);
		return false;
	}

	//initialize DirectInput
	if (!DirectInput_Init(window))
	{
		MessageBox(window, "Error initializing DirectInput", APPTITLE.c_str(), 0);
		return false;
	}

	//initialize DirectSound
	if (!DirectSound_Init(window))
	{
		MessageBox(window, "Error initializing DirectSound", APPTITLE.c_str(), 0);
		return false;
	}

	menu.Game_Init(window);

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
	DirectInput_Shutdown();
	Direct3D_Shutdown();
}