#pragma once

#include "SDLHeaders.h"
#include "libheaders.h"

struct ImageResource
{
	SDL_Surface *m_imageData;

	ImageResource() : m_imageData(NULL) {}
	~ImageResource()
	{
		if(m_imageData != NULL) SDL_FreeSurface(m_imageData);
	}
};

class ImageResourceManager
{
public:
	ImageResourceManager();
	~ImageResourceManager();

	bool LoadFile(const std::string &file, const std::string &key);
	void DestroyResource(const std::string &key);
	SDL_Surface *GetImage(const std::string &key);
	SDL_Surface *operator[] (const std::string &key);
	
private:

	SDL_Surface *load_image(const std::string &filename);

	std::map<std::string, ImageResource *> m_resources;
};