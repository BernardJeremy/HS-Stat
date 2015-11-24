#include "Sprite.h"


Sprite::Sprite()
{
	_decalXPixel = 0;
	_nbrPlayed = 1;
	_manaCost = 0;
	_isLegendary = false;
}


Sprite::~Sprite()
{
}

SDL_Texture *Sprite::getFrame() const
{
	return _frame;
}

SDL_Texture *Sprite::getImage() const
{
	return _image;
}

SDL_Texture *Sprite::getText() const
{
	return _text;
}

SDL_Texture *Sprite::getCost() const
{
	return _cost;
}

SDL_Texture *Sprite::getRarityGem() const
{
	return _rarityGem;
}

const std::string &Sprite::getCardName() const
{
	return _cardName;
}

int Sprite::getDecalXPixel() const
{
	return _decalXPixel;
}

int Sprite::getNbrPlayed() const
{
	return _nbrPlayed;
}

int Sprite::getManaCost() const
{
	return _manaCost;
}

bool Sprite::isLegendary() const
{
	return _isLegendary;
}

void Sprite::setFrame(SDL_Texture *frame)
{
	_frame = frame;
}

void Sprite::setImage(SDL_Texture *image)
{
	_image = image;
}

void Sprite::setText(SDL_Texture *text)
{
	_text = text;
}

void Sprite::setCost(SDL_Texture *cost)
{
	_cost = cost;
}

void Sprite::setRarityGem(SDL_Texture *rarityGem)
{
	_rarityGem = rarityGem;
}

void Sprite::setCardName(const std::string &cardName)
{
	_cardName = cardName;
}

void Sprite::setDecalXPixel(int decalXPixel)
{
	_decalXPixel = decalXPixel;
}

void Sprite::setNbrPlayed(int nbrPlayed)
{
	_nbrPlayed = nbrPlayed;
}

void Sprite::setManaCost(int manaCost)
{
	_manaCost = manaCost;
}

void Sprite::incNbrPlayed()
{
	++_nbrPlayed;
}

void Sprite::setIsLegendary(bool isLegendary)
{
	_isLegendary = isLegendary;
}