#ifndef TILEMAP_H
#define TILEMAP_H

#include "MyDirectX.h"
#include <sstream>

using namespace std;

class TileMap
{
public:
	void DrawTile(LPDIRECT3DSURFACE9 source,	// source surface image
				int tilenum,				// tile #
				int width,					// tile width
				int height,					// tile height
				int columns,				// columns of tiles
				LPDIRECT3DSURFACE9 dest,	// destination surface
				int destx,					// destination x
				int desty);					// destination y
	void BuildGameWorld();
	void ScrollScreen();
	bool Game_Init(HWND window);
	void Game_Run(HWND window);
	void Game_End();

	long start;

private:
	int ScrollX, ScrollY;	
	int SpeedX, SpeedY;	

};
#endif