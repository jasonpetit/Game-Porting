#include "SDLHeaders.h"
#include "libheaders.h"
#include "Audio.h"
#include "ImgManager.h"
#include "State.h"
#include "menu.h"
#include "Game.h"

const std::string APPTITLE = "BATTLE GALAXY";
const int SCREENW = 1024;
const int SCREENH = 768;
const int SCREEN_BP = 32;

SDL_Surface *Screen;
SDL_Event event;

Audio *audio;
ImageResourceManager *imgMan;
State *activeState;

Menu *menuState;
Game *playState;


int main(int argc, char *argv[])
{
	bool gameActive = true;

	srand(time(NULL));

	//initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	Screen = SDL_SetVideoMode(SCREENW, SCREENH, SCREEN_BP, SDL_SWSURFACE);

	//if there was an error
	if(Screen == NULL)
	{
		return false;
	}

	//set the caption
	SDL_WM_SetCaption(APPTITLE.c_str(), NULL);

	// [NG] Initialize resource systems
	audio = new Audio();
	if(!audio->IsOpen())
		return 0;

	imgMan = new ImageResourceManager();

	//activeState = new

	while(gameActive)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
					gameActive = false;
			}
			else if(event.type == SDL_QUIT)
			{
				gameActive = false;
			}
		}

		if(activeState == nullptr)
			return 0;
		else
			activeState->Run();

		//update the screen
		if(SDL_Flip(Screen) == -1)
		{
			gameActive = false;
		}
	}

	return 0;
}