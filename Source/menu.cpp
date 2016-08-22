//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//menu.cpp

#include "menu.h"
//#include "credits.h"
#include "play.h"
//#include "Enum.h"
#include "Audio.h"
#include "ImgManager.h"
#include "Sprite.h"
//#include "Mouse.h"

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

//Credits credit;
Play play;
//GameMode gamemode;
Sprite playT, exitT, creditsT, title;

//Handles mouse event
//int handleEvent(SDL_Event* e);


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

		imgMan->LoadFile("textures/empty.bmp", "NULLImage");
		imgMan->LoadFile("textures/Title.bmp", "Title");
		imgMan->LoadFile("textures/play.bmp", "Play");
		imgMan->LoadFile("textures/exit.bmp", "Exit");
		imgMan->LoadFile("textures/credits.bmp", "Credits");

		hasLoadedResources = true;
	}
	
	menuItem = MENU_PLAY;
	audio->PlayMusic("title_mus");

	backGround.AddFrame(imgMan->GetImage("main_background"), 500);
	backGround.SetStretch(true);

	//Sprite properties
	playT.AddFrame(imgMan->GetImage("Play"), 100);
	playT.AddFrame(imgMan->GetImage("NULLImage"), 100);
	//playT.StopAnimation();
	playT.SetPosition(15, 150);

	exitT.AddFrame(imgMan->GetImage("Exit"), 100);
	exitT.AddFrame(imgMan->GetImage("NULLImage"), 100);
	exitT.StopAnimation();
	exitT.SetPosition(15,320);

	title.AddFrame(imgMan->GetImage("Title"), 100);
	title.SetPosition(200,25);

	creditsT.AddFrame(imgMan->GetImage("Credits"), 100);
	creditsT.AddFrame(imgMan->GetImage("NULLImage"), 100);
	creditsT.StopAnimation();
	creditsT.SetPosition(15, 500);

	return true;
}

bool Menu::Run()
{
	if(leavingMenu)
	{
		leavingMenu = false;
		return false;
	}

	playT.Update();
	exitT.Update();
	creditsT.Update();

	backGround.Draw();
	title.Draw();
	playT.Draw();
	exitT.Draw();
	creditsT.Draw();

	return true;
}

void Menu::ProcessMenuItem(int item)
{
	switch(item)
	{
	case MENU_PLAY:
		SetNextState(STATE_PLAYING);
		break;
	case MENU_QUIT:
		SetNextState(STATE_WANTEXIT);
		break;
	case MENU_CREDITS:
		SetNextState(STATE_INCREDITS);
		break;
	default:
		return;
	}
	leavingMenu = true;
}

void Menu::ProcessSelection()
{
	switch(menuItem)
	{
	case MENU_PLAY:
		playT.RestartAnimation();
		exitT.StopAnimation();
		creditsT.StopAnimation();
		break;
	case MENU_QUIT:
		playT.StopAnimation();
		exitT.RestartAnimation();
		creditsT.StopAnimation();
		break;
	case MENU_CREDITS:
		playT.StopAnimation();
		exitT.StopAnimation();
		creditsT.RestartAnimation();
		break;
	default:
		break;
	}
}

void Menu::ProcessInput(SDL_Event &event)
{
	// [KB] Okay so I was going to switch the events for this over to the ProcessInput function
	//but I'm not sure what needs to be done with this event. I'm pretty sure the quit in main()
	//will work for the entire game, and I'm not sure what to do with the button events.

	// [NG] You are correct, pressing escape will be handled across the whole game since it is dealt with
	// in the main loop. 
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
		case SDLK_UP:
			menuItem--;
			if(menuItem < 0)
				menuItem = 0;
			else
				ProcessSelection();
			break;

		case SDLK_DOWN:
			menuItem++;
			if(menuItem >= MAX_MENU_ITEMS)
				menuItem = MAX_MENU_ITEMS - 1;
			else
				ProcessSelection();
			break;
			
		case SDLK_RETURN:
			ProcessMenuItem(menuItem);
			break;
		}
	}
}

/*
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

void Menu::Game_end()
{
	backG->Release();
	Title_text->Release();
	play.Game_End();
	credit.Game_End();
}
*/