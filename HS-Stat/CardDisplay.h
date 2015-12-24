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

private:
	bool displayCard(int mouseX, int mouseY, Sprite *sprite) const;

private:
	SDL_Renderer *_renderer;
	SpriteManager *_spriteManager;
};

