//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// credits.cpp

#include "credits.h"
#include "SDLHeaders.h"
#include "play.h"
#include "SDLHeaders.h"
#include "libheaders.h"
#include "Audio.h"
#include "ImgManager.h"
#include "Sprite.h"

extern Audio *audio;
extern ImageResourceManager *imgMan;
extern SDL_Surface *Screen;

using namespace std;

bool Credits::Init()
{
	if(!hasLoadedResources)
	{
		imgMan->LoadFile("textures/background.bmp", "credits_background");
		backSurface.AddFrame(imgMan->GetImage("credits_background"), 300);
		backSurface.StopAnimation();

		audio->LoadMusic("sound/credits.wav", "CreditSong");

		m_creditFont = TTF_OpenFont("fonts/lucon.ttf", 32);
		m_roleFont = TTF_OpenFont("fonts/lucon.ttf", 24);
		m_nameFont = TTF_OpenFont("fonts/lucon.ttf", 18);
		
		//postion sprites x variable
		hasLoadedResources = true;
	}
	
	iTextY = 800;

	gTimer = moveTimer = SDL_GetTicks();
	audio->PlayMusic("CreditSong");

	return true;
}

bool Credits::Run()
{
	int currentTick = SDL_GetTicks();
	if(currentTick > gTimer + 10000) // show credits for 10 seconds
	{
		SetNextState(STATE_MAINMENU);
		return false;
	}

	backSurface.Draw();
	
	if(currentTick > moveTimer + 20)
	{
		moveTimer = currentTick;
		iTextY -= 2;
		if(iTextY < 30)
			iTextY = 30;
	}

	// [NG] hacky offset math. Don't use me as any examples for this :p
	DrawText(40, iTextY, m_creditFont, Screen, "CREDITS", MakeColor(255, 32, 32));
	DrawText(40, iTextY + 36, m_roleFont, Screen, "Original Project, Lead Programmer, Assets:", MakeColor(255, 32, 32));
	DrawText(44, iTextY + 36 + 24, m_nameFont, Screen, "Jason Petit", MakeColor(255, 255, 255));

	DrawText(40, iTextY + 36 + 24 + 32, m_roleFont, Screen, "Programmer", MakeColor(255, 32, 32));
	DrawText(44, iTextY + 36 + 24 + 32 + 24, m_nameFont, Screen, "Kevin Brunelle", MakeColor(255, 255, 255));

	DrawText(40, iTextY + 36 + 24 + 32 + 24 + 32, m_roleFont, Screen, "Programmer", MakeColor(255, 32, 32));
	DrawText(44, iTextY + 36 + 24 + 32 + 24 + 32 + 24, m_nameFont, Screen, "Nick George", MakeColor(255, 255, 255));

	return true;
}
