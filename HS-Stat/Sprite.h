#pragma once

#include <string>
#include <SDL.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	SDL_Texture *getFrame() const;
	SDL_Texture *getImage() const;
	SDL_Texture *getText() const;
	SDL_Texture *getCost() const;
	int getDecalXPixel() const;
	int getNbrPlayed() const;

	void setFrame(SDL_Texture *frame);
	void setImage(SDL_Texture *image);
	void setText(SDL_Texture *text);
	void setCost(SDL_Texture *cost);
	void setDecalXPixel(int decalXPixel);
	void setNbrPlayed(int nbrPlayed);
	void incNbrPlayed();

private:
	SDL_Texture *_frame = NULL;
	SDL_Texture *_image = NULL;
	SDL_Texture *_text = NULL;
	SDL_Texture *_cost = NULL;
	int _decalXPixel;
	int _nbrPlayed;
};

