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
#include "Mouse.h"

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

//Handles mouse event
int handleEvent(SDL_Event* e)


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
	
	credit.Init();
	play.Init();

	//Sprite properties
	playT.SetPosition(15, 150);
	exitT.SetPosition(15,320);
	title.SetPosition(200,25);
	creditsT.SetPosition(15, 500);

	return true;
}

bool Menu::Game_Run()
{
	/*static bool keyRelease = true;
	static bool plays = false;
	static bool exits = false;
	static bool credits = false;*/

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle button events
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				gButtons[i].handleEvent(&e);
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render buttons
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i].render();
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
}










	switch (gamemode)
	{
	case MENU:
		//If mouse event happened
		if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);






		if (Key_Down(DIK_UP) && keyRelease)
		{
			keyRelease = false;
			playT.
			Sprite_Animate(playT.AddFrame.                       , 1, 1, playT.direction, playT.starttime, playT.delay);
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