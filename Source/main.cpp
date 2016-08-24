#include "SDLHeaders.h"
#include "libheaders.h"
#include "Audio.h"
#include "ImgManager.h"
#include "State.h"
#include "menu.h"
#include "play.h"
#include "credits.h"

const std::string APPTITLE = "BATTLE GALAXY";
const int SCREENW = 1024;
const int SCREENH = 768;
const int SCREEN_BP = 32;

SDL_Surface *Screen;
SDL_Event event;

Audio *audio;
ImageResourceManager *imgMan;
State *activeState = NULL;

Menu *menuState;
Play *playState;
Credits *creditState;


int main(int argc, char *argv[])
{
	bool gameActive = true;

	srand(unsigned int (time(NULL)));

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
	creditState = new Credits();
	ChangeState(menuState);

	while(gameActive)
	{
		SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
					gameActive = false;

				else
					activeState->ProcessInput(event);
			}
			else if(event.type == SDL_QUIT)
			{
				gameActive = false;
			}
		}

		if(activeState == NULL)
			return 0;
		else
			if(!activeState->Run())
			{
				if(activeState->GetStateID() == STATE_WANTEXIT)
					gameActive = false;
				else
				{
					switch(activeState->GetStateTarget())
					{
					case STATE_MAINMENU:
						ChangeState(menuState);
						break;
					case STATE_PLAYING:
						ChangeState(playState);
						break;
					case STATE_INCREDITS:
						ChangeState(creditState);
						break;
					default:
						gameActive = false;
						break;
					}
				}
			}

		//update the screen
		if(SDL_Flip(Screen) == -1)
		{
			gameActive = false;
		}
	}

	//TTF_CloseFont(font);
	//Quit SDL_ttf
	TTF_Quit();

	return 0;
}