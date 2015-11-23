#pragma once
#include <iostream>

#include <SDL.h>

#include "ImageManager.h"
#include "SpriteManager.h"

#define SCREEN_TITLE "HS-Stat by Corelan"

#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 1050

class SdlDisplayer
{
public:
	SdlDisplayer();
	~SdlDisplayer();

	bool init();
	void cleanup();
	bool manageInput();
	bool draw();
	bool addCard(std::string cardName, std::string cost, std::string cardRarity, bool isLocalPlayer);

private:
	SDL_Window *_screen;
	SDL_Renderer *_renderer;
	
	SpriteManager *_spriteManager;
};

