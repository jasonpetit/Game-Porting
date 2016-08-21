//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//menu.cpp

#include "menu.h"
#include "credits.h"
#include "play.h"
#include "Enum.h"
#include "Audio.h"
#include "ImgManager.h"
#include "Sprite.h"

using namespace std;

extern Audio *audio;
extern ImageResourceManager *imgMan;

SDL_Surface *backG = NULL;
SDL_Surface *Title_text = NULL;
SDL_Surface *Play_text = NULL;
SDL_Surface *Exit_text = NULL;
SDL_Surface *Credits_text = NULL;
SDL_Surface *Hplay = NULL;
SDL_Surface *Hexit = NULL;
SDL_Surface *Hcredits = NULL;

Mix_Music *sound_song = NULL;

Credits credit;
Play play;
GameMode gamemode;
Sprite playT, exitT, creditsT, title;

// TODO: Finish all of this...
// If nothing else, the Play class has a good, semi-completed example
// of what this class should look like in the end (loading and displaying resources,
// when to update and when to draw, etc.)
bool Menu::Init()
{
	if(!hasLoadedResources)
	{
		if(!imgMan->LoadFile("textures/background.bmp", "main_background"))
			return false;

		audio->LoadMusic("sound/starwars.wav", "title_mus");

		imgMan->LoadFile("textures/Title.bmp", "Title");
		imgMan->LoadFile("textures/play.bmp", "Play");
		imgMan->LoadFile("textures/exit.bmp", "Exit");
		imgMan->LoadFile("textures/credits.bmp", "Credits");

		hasLoadedResources = true;
	}
	
	credit.Game_Init();
	play.Game_Init();

	//Sprite properties
	playT.x = 15;
	playT.y = 150;
	playT.width = 425;
	playT.height = 190;
	playT.columns = 2;
	playT.startframe = 0;
	playT.endframe = 0;

	exitT.x = 15;
	exitT.y = 320;
	exitT.width = 420;
	exitT.height = 170;
	exitT.columns = 2;
	exitT.startframe = 0;
	exitT.endframe = 0;

	title.x = 200;
	title.y = 25;
	title.width = 700;
	title.height = 190;
	title.columns = 2;
	title.startframe = 0;
	title.endframe = 0;

	creditsT.x = 15;
	creditsT.y = 500;
	creditsT.width = 500;
	creditsT.height = 170;
	creditsT.columns = 2;
	creditsT.startframe = 0;
	creditsT.endframe = 0;


	return true;
}

void Menu::Game_Run()
{
	static bool keyRelease = true;
	static bool plays = false;
	static bool exits = false;
	static bool credits = false;


	DirectInput_Update();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);

	switch (gamemode)
	{
	case MENU:
		if (Key_Down(DIK_UP) && keyRelease)
		{
			keyRelease = false;
			Sprite_Animate(playT.frame, 1, 1, playT.direction, playT.starttime, playT.delay);
			Sprite_Animate(exitT.frame, 0, 0, exitT.direction, exitT.starttime, exitT.delay);
			Sprite_Animate(creditsT.frame, 0, 0, creditsT.direction, creditsT.starttime, creditsT.delay);
			plays = true;
		}
		if (!Key_Down(DIK_UP))
		{
			keyRelease = true;
		}
		if (Key_Down(DIK_RETURN) && plays)
		{
			plays = false;
			gamemode = PLAY;
		}
		if (Key_Down(DIK_LEFT))
		{
			Sprite_Animate(exitT.frame, 1, 1, exitT.direction, exitT.starttime, exitT.delay);
			Sprite_Animate(playT.frame, 0, 0, playT.direction, playT.starttime, playT.delay);
			Sprite_Animate(creditsT.frame, 0, 0, creditsT.direction, creditsT.starttime, creditsT.delay);
			exits = true;
		}
		if (Key_Down(DIK_RETURN) && exits)
		{
			exits = false;
			gamemode = EXIT;
		}
		if (Key_Down(DIK_RIGHT))
		{
			Sprite_Animate(playT.frame, 0, 0, playT.direction, playT.starttime, playT.delay);
			Sprite_Animate(exitT.frame, 0, 0, exitT.direction, exitT.starttime, exitT.delay);
			Sprite_Animate(creditsT.frame, 1, 1, creditsT.direction, creditsT.starttime, creditsT.delay);
			credits = true;
		}
		if (Key_Down(DIK_RETURN) && credits)
		{
			credits = false;
			gamemode = CREDITS;
		}
		break;
	}
	//start rendering
	if (d3ddev->BeginScene())
	{
		//start sprite handler
		spriteobj->Begin(D3DXSprite_ALPHABLEND);

		d3ddev->StretchRect(backG, NULL, backbuffer, NULL, D3DTEXF_NONE);

		switch (gamemode)
		{
		case MENU:
			Sprite_Transform_Draw(Exit_text, exitT.x, exitT.y, exitT.width, exitT.height, exitT.frame, exitT.columns);
			Sprite_Transform_Draw(Play_text, playT.x, playT.y, playT.width, playT.height, playT.frame, playT.columns);
			Sprite_Transform_Draw(Title_text, title.x, title.y, title.width, title.height, title.frame, title.columns);
			Sprite_Transform_Draw(Credits_text, creditsT.x, creditsT.y, creditsT.width, creditsT.height, creditsT.frame, creditsT.columns);
			Mix_PlayMusic(sound_song, -1);
			break;

		case PLAY:
			Mix_HaltMusic();
			play.Game_Run();
			break;
		case CREDITS:
			Mix_PauseMusic();
			credit.Game_Run();
			break;
		case EXIT:
			gameover = true;
			break;
		}

		//stop drawing
		spriteobj->End();

		//stop rendering
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}

/*
void Menu::Game_end()
{
	backG->Release();
	Title_text->Release();
	play.Game_End();
	credit.Game_End();
}
*/