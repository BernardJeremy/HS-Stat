#include "ImageManager.h"

ImageManager::ImageManager()	
{
}


ImageManager::~ImageManager()
{
}

bool ImageManager::renderImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int h, int w)
{
	SDL_Rect s_rect;

	s_rect.x = x;   
	s_rect.y = y;
	s_rect.w = w; 
	s_rect.h = h; 

	SDL_RenderCopy(renderer, texture, NULL, &s_rect);
	
	return true;
}

SDL_Texture *ImageManager::getTextureFromImage(SDL_Renderer *renderer, const std::string &imgName)
{
	SDL_Texture *texture;

	std::string path = SDL_GetBasePath();
	path += IMG_REL_PATH;
	path += imgName;

	texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
		return NULL;
	}

	return texture;
}