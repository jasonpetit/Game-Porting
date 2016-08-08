//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// credits.cpp

#include "credits.h"
#include "SDLHeaders.h"

using namespace std;

SDL_Surface *back_surf = NULL;
SDL_Surface *credit_text = NULL;
SDL_Surface *design_text = NULL;
SDL_Surface *prog_text = NULL;
SDL_Surface *art_text = NULL;
SDL_Surface *credB_text = NULL;
SDL_Surface *explode_text = NULL;
SDL_Surface *gShip_text = NULL;
SDL_Surface *menu_text = NULL;
SDL_Surface *creditSp_text = NULL;

Mix_Music *sound_music = NULL;

Play play;

struct sprite
{
	float x, y;
};

sprite credit;
sprite design;
sprite prog;
sprite art;
sprite back;
sprite explode;
sprite gShip;
sprite menu;
sprite credSp;

bool Credits::Game_Init()
{
	back_surf = play.load_image("background.bmp");

	sound_music = Mix_LoadMUS("credits.wav");
	if (!back_surf)
	{
		//MessageBox(window, "Error loading Background", "Error", 0);
		return false;
	}

	credit_text = play.load_image("creditsT.bmp");
	design_text = play.load_image("design.bmp");
	prog_text = play.load_image("program.bmp");


	//postion sprites x variable
	credit.x = 350;
	design.x = 300;
	prog.x = 300;


	//position sprites y variable
	credit.y = 800;
	design.y = 875;
	prog.y = 950;

	return true;
}

void Credits::Game_Run()
{
	//make sure the Direct 3D device is valid
	if (!d3ddev)
		return;

	// move the sprites up the screen
	credit.y -= 0.15f;
	design.y -= 0.15f;
	prog.y -= 0.15f;

	if (d3ddev->BeginScene())
	{
		//start drawing
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

		Mix_PlayMusic(sound_music, -1);

		d3ddev->StretchRect(back_surf, NULL, backbuffer, NULL, D3DTEXF_NONE);

		D3DXVECTOR3 pos1(credit.x, credit.y, 0);
		D3DXVECTOR3 pos2(design.x, design.y, 0);
		D3DXVECTOR3 pos3(prog.x, prog.y, 0);
		D3DXVECTOR3 pos4(art.x, art.y, 0);
		D3DXVECTOR3 pos5(back.x, back.y, 0);
		D3DXVECTOR3 pos6(explode.x, explode.y, 0);
		D3DXVECTOR3 pos7(gShip.x, gShip.y, 0);
		D3DXVECTOR3 pos8(menu.x, menu.y, 0);
		D3DXVECTOR3 pos10(credSp.x, credSp.y, 0);


		spriteobj->Draw(credit_text, NULL, NULL, &pos1, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(design_text, NULL, NULL, &pos2, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(prog_text, NULL, NULL, &pos3, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(art_text, NULL, NULL, &pos4, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(credB_text, NULL, NULL, &pos5, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(explode_text, NULL, NULL, &pos6, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(gShip_text, NULL, NULL, &pos7, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(menu_text, NULL, NULL, &pos8, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->Draw(creditSp_text, NULL, NULL, &pos10, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void Credits::Game_End()
{
	SDL_FreeSurface(back_surf);
	SDL_FreeSurface(credit_text);
	SDL_FreeSurface(design_text);
	SDL_FreeSurface(prog_text);
}