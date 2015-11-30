#include "SpriteManager.h"


SpriteManager::SpriteManager(SDL_Renderer *renderer) : _renderer(renderer), _frameTexture(NULL)
{
}


SpriteManager::~SpriteManager()
{
	this->eraseAllSprite(true);
}

bool SpriteManager::drawAllSprite() const
{
	std::list<Sprite*>::const_iterator it;
	int nbrSpriteLocal = 0;
	int nbrSpriteOpp = 0;
	for (it = _spriteList.begin(); it != _spriteList.end(); ++it) {
		int decalX = SpriteManager::POS_X_ZONE + (*it)->getDecalXPixel();
		int decalMultY = (*it)->getDecalXPixel() > 0 ? nbrSpriteOpp : nbrSpriteLocal;
		int decalY = SpriteManager::POS_Y_ZONE + (decalMultY * H_FRAME);
		Sprite *current = (*it);

		///////////////////////////////////
		// [CARD] IMAGE RENDERING
		///////////////////////////////////
		ImageManager::renderImage(_renderer, current->getImage(), decalX + W_FRAME - W_IMAGE - 5, decalY, H_IMAGE, W_IMAGE);
		///////////////////////////////////
		// [FRAME] RENDERING
		///////////////////////////////////
		ImageManager::renderImage(_renderer, current->getFrame(), decalX, decalY, H_FRAME, W_FRAME);
		///////////////////////////////////
		// [NUMBER + STAR] RENDERING
		///////////////////////////////////
		if (current->getNbrPlayed() > 1 || current->isLegendary()) {
			if (current->getNbrPlayed() > 9)
				current->setNbrPlayed(9);
			SDL_Texture *numberBoxTexture = ImageManager::getTextureFromImage(_renderer, "frame_countbox.png");
			ImageManager::renderImage(_renderer, numberBoxTexture, decalX + W_FRAME - W_NUMBER_BOX - 5, decalY + 6, H_NUMBER_BOX, W_NUMBER_BOX);
			
			std::string labelFileName = current->isLegendary() ? "legendary" : std::to_string(current->getNbrPlayed());
			std::string nbrFileName = "frame_" + labelFileName + ".png";
			
			SDL_Texture *numberTexture = ImageManager::getTextureFromImage(_renderer, nbrFileName);
			ImageManager::renderImage(_renderer, numberTexture, decalX + W_FRAME - W_NUMBER_BOX + 1, decalY + 8, H_NUMBER, W_NUMBER);

			SDL_DestroyTexture(numberBoxTexture);
			SDL_DestroyTexture(numberTexture);
		}
		///////////////////////////////////
		// [RARITY] RENDERING
		///////////////////////////////////
		ImageManager::renderImage(_renderer, current->getRarityGem(), decalX + 3, decalY + 3, H_GEM, W_GEM);
		///////////////////////////////////
		// [TEXT] RENDERING
		///////////////////////////////////
		int textWidth = current->getCardName().length() * 7;
		int maxTextWidth = W_FRAME - X_DECAL_TEXT;
		maxTextWidth -= (current->getNbrPlayed() > 1 || current->isLegendary() ? W_NUMBER_BOX : 0);
		textWidth = (textWidth > maxTextWidth ? maxTextWidth : textWidth);
		ImageManager::renderImage(_renderer, current->getText(), decalX + X_DECAL_TEXT, decalY + 4, H_FRAME - 10, textWidth);
		///////////////////////////////////
		// [COST] RENDERING
		///////////////////////////////////
		ImageManager::renderImage(_renderer, current->getCost(), decalX + X_DECAL_COST, decalY, H_COST, W_COST);

		if ((*it)->getDecalXPixel() > 0)
			++nbrSpriteOpp;
		else
			++nbrSpriteLocal;
	}

	return true;
}

void SpriteManager::eraseAllSprite(bool eraseAll)
{
	std::list<Sprite*>::iterator it;

	for (it = _spriteList.begin(); it != _spriteList.end(); ++it) {
		SDL_DestroyTexture((*it)->getCost());
		SDL_DestroyTexture((*it)->getImage());
		SDL_DestroyTexture((*it)->getText());
		if (eraseAll)
			SDL_DestroyTexture((*it)->getFrame());
		delete (*it);
	}

	_spriteList.clear();
	_cardList.clear();
}

const std::list<Sprite*> *SpriteManager::getSpriteList() const
{
	return &_spriteList;
}

bool SpriteManager::addCard(std::string cardName, std::string cost, std::string cardRarity, bool isLocalPlayer)
{
	if (cardName.empty())
		return false;
	std::string testName(cardName);
	testName += "_#";
	testName += (isLocalPlayer ? "1" : "2");
	if (_cardList.find(testName) != _cardList.end()) {
		_cardList.find(testName)->second->incNbrPlayed();
	}
	else {
		Sprite *sprite = new Sprite();
		std::string realCardName(cardName);

		sprite->setImage(AddImage(cardNameToFileName(cardName)));
		if (!sprite->getImage())
		{
			delete sprite;
			return false;
		}
		sprite->setFrame(AddFrame());
		sprite->setText(AddText(realCardName));
		sprite->setCardName(realCardName);
		sprite->setCost(AddText(cost));
		sprite->setRarityGem(AddRarityGem(cardRarity, sprite));
		sprite->setManaCost(std::stoi(cost));
		sprite->setIsLocalPlayer(isLocalPlayer);
		sprite->setDecalXPixel(isLocalPlayer ? 0 : SpriteManager::POS_X_ZONE + SpriteManager::W_LOCAL_ZONE + SpriteManager::DECAL_ZONE);

		addSpriteinList(sprite);
		_cardList.insert(std::pair<std::string, Sprite*>(testName, sprite));
	}	

	return true;
}

SDL_Texture *SpriteManager::AddFrame()
{
	if (!_frameTexture)
		_frameTexture = ImageManager::getTextureFromImage(_renderer, "frame.png");

	return _frameTexture;
}

SDL_Texture *SpriteManager::AddImage(std::string &fileName) const
{
	SDL_Texture *mobTexture = ImageManager::getTextureFromImage(_renderer, fileName);

	return mobTexture;
}

SDL_Texture *SpriteManager::AddText(std::string &cardName) const
{
	std::string fontPath = SDL_GetBasePath();
	fontPath += "1553.ttf";
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 48);
	if (!font)
	{
		std::cout << "TTF_Init Error : " << TTF_GetError() << std::endl;
		return NULL;
	}
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surfaceText = TTF_RenderText_Blended(font, cardName.c_str(), color);

	return SDL_CreateTextureFromSurface(_renderer, surfaceText);
}

SDL_Texture *SpriteManager::AddRarityGem(std::string &cardRarity, Sprite *sprite) const
{

	std::string fileName = "gem_rarity_";
	if (cardRarity.compare("Free") == 0 || cardRarity.compare("0") == 0)
		cardRarity = "Common";
	fileName += cardNameToFileName(cardRarity);

	if (cardRarity.compare("legendary.png") == 0)
		sprite->setIsLegendary(true);

	return AddImage(fileName);
}

std::string SpriteManager::cardNameToFileName(std::string &cardName) const
{
	std::transform(cardName.begin(), cardName.end(), cardName.begin(), ::tolower);
	replaceAll(cardName, " ", "-");
	replaceAll(cardName, ":", "");
	replaceAll(cardName, "'", "-");
	replaceAll(cardName, ".", "");
	replaceAll(cardName, "!", "");
	replaceAll(cardName, ",", "");
	cardName += ".png";

	return cardName;
}

void SpriteManager::replaceAll(std::string& str, const std::string& from, const std::string& to) const
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void SpriteManager::addSpriteinList(Sprite *newSprite)
{
	std::list<Sprite*>::iterator it;
	std::list<Sprite*>::iterator saveIt;
	int saveCost = 0;
	bool inserted = false;

	for (it = _spriteList.begin(); it != _spriteList.end(); ++it) {
		Sprite *current = (*it);
		saveIt = it;
		saveCost = current->getManaCost();

		if (newSprite->getManaCost() < current->getManaCost())
		{
			_spriteList.insert(saveIt, newSprite);
			inserted = true;
			break;
		}
	}

	if (!inserted)
		_spriteList.push_back(newSprite);
}