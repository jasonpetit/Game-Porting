// Game.cpp

#include "MyDirectX.h"
#include "TileMap.h"
#include "sprite.h"
#include <sstream>

using namespace std;

const string APPTITLE = "Battle Galaxy";
const int SCREENW = 1024;
const int SCREENH = 768;

TileMap map;
ship ships;

bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);
    DirectInput_Init(window);

	map.Game_Init(window);
	ships.Game_Init(window);

	return true;
}

void Game_Run(HWND window)
{
    if (!d3ddev) 
		return;

    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);


    //keep the game running at a steady frame rate
    if (GetTickCount() - map.start >= 30)
    {
        //reset timing
        map.start = GetTickCount();

		//start rendering
		if (d3ddev->BeginScene())
		{
			
            //update the scrolling view
            map.ScrollScreen();
		
            spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

			map.Game_Run(window);
			ships.Game_Run(window);
			
			spriteobj->End();

			//stop rendering
			d3ddev->EndScene();
            d3ddev->Present(NULL, NULL, NULL, NULL);
		}
	}

    //to exit 
    if (KEY_DOWN(VK_ESCAPE))
        gameover = true;

}

void Game_End()
{
	map.Game_End();
	ships.Game_End();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}