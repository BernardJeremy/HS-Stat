#include "CardDisplay.h"


CardDisplay::CardDisplay(SDL_Renderer *renderer, SpriteManager *spriteManager)
{
	_renderer = renderer;
	_spriteManager = spriteManager;
}


CardDisplay::~CardDisplay()
{
}

void CardDisplay::checkMousePosition() const
{
	const std::list<Sprite*> *spriteList;
	std::list<Sprite*>::const_iterator it;
	bool isLocalPlayer = true;
	Sprite *current = NULL;
	int seek = 0;
	int i = -1;
	int x = 0;
	int y = 0;

	spriteList = _spriteManager->getSpriteList();
	SDL_GetMouseState(&x, &y);

	if (x == 0 || y == 0)
		return;

	if (x >= SpriteManager::POS_X_ZONE + SpriteManager::W_LOCAL_ZONE + SpriteManager::DECAL_ZONE)
	{
		if (!_spriteManager->isReverseDisplay())
			isLocalPlayer = false;
	}
	else if (_spriteManager->isReverseDisplay())
		isLocalPlayer = false;

	seek = y / H_FRAME;

	for (it = spriteList->begin(); it != spriteList->end(); ++it) {
		current = (*it);
		if (current->isLocalPlayer() == isLocalPlayer)
			i++;
		if (i >= seek)
			break;
	}
	if (it == spriteList->end())
		return;
	this->displayCard(x, y, current);
}

bool CardDisplay::displayCard(int mouseX, int mouseY, Sprite *sprite) const
{
	SDL_Texture *cardTexture = NULL;

	if (!sprite->getFullCard())
		sprite->setFullCard(ImageManager::getTextureFromCard(_renderer, sprite->getCardName()));

	cardTexture = sprite->getFullCard();

	if (cardTexture)
	{
		int x = (mouseX + W_CARD > SCREEN_WIDTH ? SCREEN_WIDTH - W_CARD : mouseX);
		int y = (mouseX + H_CARD > SCREEN_HEIGHT ? SCREEN_HEIGHT - H_CARD : mouseY);
		ImageManager::renderImage(_renderer, cardTexture, x, y, H_CARD, W_CARD);
	}
	else {
		return false;
	}

	return true;
}