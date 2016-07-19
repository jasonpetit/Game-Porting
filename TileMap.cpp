#include "TileMap.h"

//settings for the scroller
const int TILEWIDTH = 200;
const int TILEHEIGHT = 200;
const int MAPWIDTH = 30;
const int MAPHEIGHT = 11;

//scrolling window size
const int WINDOWWIDTH = (SCREENW / TILEWIDTH) * TILEWIDTH;
const int WINDOWHEIGHT = (SCREENH / TILEHEIGHT) * TILEHEIGHT;

//entire game world dimensions
const int GAMEWORLDWIDTH = TILEWIDTH * MAPWIDTH;
const int GAMEWORLDHEIGHT = TILEHEIGHT * MAPHEIGHT;

LPDIRECT3DSURFACE9 gameworld = NULL;

int MAPDATA[MAPWIDTH*MAPHEIGHT] = { 
	1,9,45,45,27,36,45,45,35,36,35,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	35,36,9,36,35,44,45,44,45,26,44,36,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	9,26,26,35,36,45,45,36,44,45,35,27,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	44,35,45,36,45,35,36,45,45,36,45,35,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	45,44,44,36,8,45,26,44,44,17,26,8,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	8,44,26,27,17,45,17,35,45,45,27,18,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	44,17,44,36,35,8,45,1,2,3,4,5,44,35,36,9,36,35,44,45,44,45,26,44,36,35,36,9,36,35,44,
	36,18,45,45,26,18,27,10,11,12,13,14,44,35,36,9,36,35,44,45,44,45,26,44,44,36,35,36,9,36,35,44,
	2,3,4,5,6,7,8,28,29,30,31,32,44,35,36,9,36,35,44,45,44,45, 26,44,36,35,36,9,36,35,44,
	11,12,13,14,15,16,17,37,38,39,40,4144,35,36,9,36,35,44,45,44,45
	};

void TileMap::DrawTile(LPDIRECT3DSURFACE9 source,	// source surface image
				int tilenum,				// tile #
				int width,					// tile width
				int height,					// tile height
				int columns,				// columns of tiles
				LPDIRECT3DSURFACE9 dest,	// destination surface
				int destx,					// destination x
				int desty)					// destination y
{
    
    //create a RECT to describe the source image
    RECT r1;
    r1.left = (tilenum % columns) * width;
    r1.top = (tilenum / columns) * height;
    r1.right = r1.left + width;
    r1.bottom = r1.top + height;
    
    //set destination rect
	RECT r2 = {destx,desty,destx+width,desty+height};
    
    //draw the tile 
    d3ddev->StretchRect(source, &r1, dest, &r2, D3DTEXF_NONE);
}

void TileMap::BuildGameWorld()
{
	HRESULT result;
    int x, y;
    LPDIRECT3DSURFACE9 tiles;
    
    //load the bitmap image containing all the tiles
    tiles = LoadSurface("background.bmp");
    
    //create the scrolling game world bitmap
    result = d3ddev->CreateOffscreenPlainSurface(
		GAMEWORLDWIDTH,         //width of the surface
		GAMEWORLDHEIGHT,        //height of the surface
		D3DFMT_X8R8G8B8,		
		D3DPOOL_DEFAULT,		
		&gameworld,             //pointer to the surface
		NULL);
	
    if (result != D3D_OK)
	{
        MessageBox(NULL,"Error creating working surface!","Error",0);
		return;
	}
    
    //fill the gameworld bitmap with tiles
    for (y=0; y < MAPHEIGHT; y++)
        for (x=0; x < MAPWIDTH; x++)
            DrawTile(tiles, MAPDATA[y * MAPWIDTH + x], 200, 150, 8, 
            gameworld, x * 200, y * 200);
        
    //now the tiles bitmap is no longer needed
    tiles->Release();
}

void TileMap::ScrollScreen()
{
    //update horizontal scrolling position and speed
    ScrollX += SpeedX;
    if (ScrollX < 0) 
	{
        ScrollX = 0;
        SpeedX = 0;
	}
    else if (ScrollX > GAMEWORLDWIDTH - SCREENW)
	{
        ScrollX = GAMEWORLDWIDTH - SCREENW;
        SpeedX = 0;
	}
    
    //update vertical scrolling position and speed
    ScrollY += SpeedY;
    if (ScrollY < 0)
	{
        ScrollY = 0;
        SpeedY = 0;
	}
    else if (ScrollY > GAMEWORLDHEIGHT - SCREENH)
	{
        ScrollY = GAMEWORLDHEIGHT - SCREENH;
        SpeedY = 0;
	}
    
    //set dimensions of the source image
	RECT r1 = {ScrollX, ScrollY, ScrollX+SCREENW-1, ScrollY+SCREENH-1};
    
    //set the destination rect
	RECT r2 = {0, 0, SCREENW-1, SCREENH-1};
    
    //draw the current game world view
    d3ddev->StretchRect(gameworld, &r1, backbuffer, &r2, 
        D3DTEXF_NONE);

}

bool TileMap::Game_Init(HWND window)
{
	//create pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

    BuildGameWorld();

	start = GetTickCount();

    return true;
}

void TileMap::Game_Run(HWND window)
{
		//scroll based on key or controller input
		if (Key_Down(DIK_DOWN))
			ScrollY += 10;

		if (Key_Down(DIK_UP))
			ScrollY -= 10;

		if (Key_Down(DIK_LEFT))
			ScrollX -= 10;

		if (Key_Down(DIK_RIGHT))
			ScrollX += 10;
}

void TileMap::Game_End()
{
	if (gameworld) 
		gameworld->Release();
}