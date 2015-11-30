#pragma once
#include <iostream>

#include <SDL.h>

#include "ImageManager.h"
#include "SpriteManager.h"
#include "Parser.h"
#include "LogFileManager.h"
#include "CardDisplay.h"

#define SCREEN_TITLE "HS-Stat by Corelan"

class SdlDisplayer
{
public:
	SdlDisplayer();
	~SdlDisplayer();

	enum Mode { DECK, BUTTON };

	bool init();
	void cleanup();
	bool manageInput(Parser *parser, LogFileManager *logFileManager);
	bool draw();
	bool addCard(std::string cardName, std::string cost, std::string cardRarity, bool isLocalPlayer) const;
	void eraseAllSprite() const;

private:
	void switchMode();

private:
	SDL_Window *_screen;
	SDL_Renderer *_renderer;
	SpriteManager *_spriteManager;
	SdlDisplayer::Mode _currentMode;
	CardDisplay *_cardDisplay;
	
};

