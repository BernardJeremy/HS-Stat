#pragma once

#include "SpriteManager.h"

#define W_CARD 307
#define H_CARD 465

class CardDisplay
{
public:
	CardDisplay(SDL_Renderer *renderer, SpriteManager *spriteManager);
	~CardDisplay();

	void checkMousePosition() const;
	void setHasFocus(bool hasFocus);

private:
	bool displayCard(int mouseX, int mouseY, const std::string &cardName) const;

private:
	SDL_Renderer *_renderer;
	SpriteManager *_spriteManager;
	bool _hasFocus;
};

