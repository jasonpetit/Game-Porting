//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

// play.h

#ifndef PLAY_H
#define PLAY_H

#include "MyDirectX.h"
#include "SDLHeaders.h"
#include "DirectSound.h"
#include <time.h>
#include <cstdlib>

class Play
{
public:
	//Game functions
	bool Game_Init();
	void Game_Run();
	void Game_End();

	//SDL functions
	//Added the load_image function to the play.h file here.
		//One issue that does need to be fixed, is the alpha channel that the images apparantly use.
		//I believe switching the colorkey to simply use 0, 0, 0 will solve the problem.
	SDL_Surface *load_image(std::string filename)
	{
		//The image that's loaded
		SDL_Surface *loadedImage = NULL;

		//The optimized image
		SDL_Surface *optimizedImage = NULL;

		//Load the image
		loadedImage = IMG_Load(filename.c_str());

		//if the image loaded
		if (loadedImage != NULL)
		{
			//Create an optimized image
			optimizedImage = SDL_DisplayFormat(loadedImage);

			//Free the old image
			SDL_FreeSurface(loadedImage);

			//If the image was optimized just fine
			if (optimizedImage != NULL)
			{
				//Set the colorkey to 0, 0, 0 in order to attempt to remove the alpha channel
				Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0, 0);
				//set all pixels of color to 0 for RGB scale.
				SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
			}//end if (optimizedImage)
		}//end if (loadedImage)
	}// end load_image
};

class SPRITE
{
private:
	//offsets
	float x, y;
	//rate of movement
	int velocity;
	//current frame
	int frame;
	//animation status
	int status;

public:
	//initializes the variables
	SPRITE::SPRITE()
	{
		//Initialize movement variables
		x = y = 0;
		velocity = 0;

		//Initialize animation variables
		frame = 0;
	}

	//handles input
	void SPRITE::handle_events()
	{

	}

	//moves the sprite
	void SPRITE::move()
	{

	}

	//shows the sprite
	void SPRITE::show()
	{

	}
};
#endif