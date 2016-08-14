#pragma once

// Add SDL headers here
// Use preprocessor directive to set between Windows/Linux headers

#ifdef WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#else
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

#endif