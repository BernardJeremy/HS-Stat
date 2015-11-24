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
	SDL_Texture *getRarityGem() const;
	const std::string &getCardName() const;
	int getDecalXPixel() const;
	int getNbrPlayed() const;
	int getManaCost() const;
	bool isLegendary() const;

	void setFrame(SDL_Texture *frame);
	void setImage(SDL_Texture *image);
	void setText(SDL_Texture *text);
	void setCost(SDL_Texture *cost);
	void setRarityGem(SDL_Texture *rarityGem);
	void setCardName(const std::string &cardName);
	void setDecalXPixel(int decalXPixel);
	void setNbrPlayed(int nbrPlayed);
	void incNbrPlayed();
	void setManaCost(int manaCost);
	void setIsLegendary(bool isLegendary);

private:
	SDL_Texture *_frame = NULL;
	SDL_Texture *_image = NULL;
	SDL_Texture *_text = NULL;
	SDL_Texture *_cost = NULL;
	SDL_Texture *_rarityGem = NULL;
	std::string _cardName;
	int _decalXPixel;
	int _nbrPlayed;
	int _manaCost;
	bool _isLegendary;
};

