#include "SDLHeaders.h"
#include "libheaders.h"
#include "Audio.h"
#include "ImgManager.h"
#include "State.h"
#include "menu.h"
#include "play.h"

const std::string APPTITLE = "BATTLE GALAXY";
const int SCREENW = 1024;
const int SCREENH = 768;
const int SCREEN_BP = 32;

SDL_Surface *Screen;
SDL_Event event;

Audio *audio;
ImageResourceManager *imgMan;
State *activeState = nullptr;

Menu *menuState;
Play *playState;


int main(int argc, char *argv[])
{
	bool gameActive = true;

	srand(time(NULL));

	//initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 0;
	}

	if(TTF_Init() == -1) { return 0; }

	Screen = SDL_SetVideoMode(SCREENW, SCREENH, SCREEN_BP, SDL_SWSURFACE);

	//if there was an error
	if(Screen == NULL)
	{
		return 0;
	}

	//set the caption
	SDL_WM_SetCaption(APPTITLE.c_str(), NULL);

	// [NG] Initialize resource systems
	audio = new Audio();
	if(!audio->IsOpen())
		return 0;

	imgMan = new ImageResourceManager();

	menuState = new Menu();
	playState = new Play();
	ChangeState(menuState);

	while(gameActive)
	{
		// TODO: Pass unprocessed events to the active state
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