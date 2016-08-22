#include "ImgManager.h"

ImageResourceManager::ImageResourceManager()
{
	m_resources.clear();
}

ImageResourceManager::~ImageResourceManager()
{

}

bool ImageResourceManager::LoadFile(const std::string &file, const std::string &key)
{
	ImageResource *newImage = new ImageResource;

	newImage->m_imageData = load_image(file);
	if(newImage->m_imageData == NULL)
	{
		delete newImage;
		return false;
	}

	m_resources[key] = newImage;
	return true;
}

void ImageResourceManager::DestroyResource(const std::string &key)
{
	if(m_resources.find(key) != m_resources.end())
	{
		delete m_resources[key];
		m_resources.erase(key);
	}
}

SDL_Surface *ImageResourceManager::GetImage(const std::string &key)
{
	if(m_resources.find(key) != m_resources.end())
	{
		return m_resources[key]->m_imageData;
	}
	else
		return nullptr;
}

SDL_Surface *ImageResourceManager::operator[](const std::string &key)
{
	return GetImage(key);
}

SDL_Surface *ImageResourceManager::load_image(const std::string &filename)
{
	//The image that's loaded
	SDL_Surface *loadedImage = NULL;

	//The optimized image
	SDL_Surface *optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	//if the image loaded
	if(loadedImage != NULL)
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);

		//If the image was optimized just fine
		if(optimizedImage != NULL)
		{
			//Set the colorkey to 0, 0, 0 in order to attempt to remove the alpha channel
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0, 0);
			//set all pixels of color to 0 for RGB scale.
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}
