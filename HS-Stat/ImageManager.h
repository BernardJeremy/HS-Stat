#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <SDL_image.h>

#define IMG_REL_PATH "Images\\"

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	static bool renderImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int h, int w);
	static SDL_Texture *getTextureFromImage(SDL_Renderer *renderer, const std::string &imgName);

private:
	std::vector<SDL_Texture *> _images;
};

