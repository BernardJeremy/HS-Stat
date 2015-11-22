#include "Sprite.h"


Sprite::Sprite()
{
	_decalXPixel = 0;
	_nbrPlayed = 1;
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

int Sprite::getDecalXPixel() const
{
	return _decalXPixel;
}

int Sprite::getNbrPlayed() const
{
	return _nbrPlayed;
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

void Sprite::setDecalXPixel(int decalXPixel)
{
	_decalXPixel = decalXPixel;
}

void Sprite::setNbrPlayed(int nbrPlayed)
{
	_nbrPlayed = nbrPlayed;
}

void Sprite::incNbrPlayed()
{
	++_nbrPlayed;
}