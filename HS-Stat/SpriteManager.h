#pragma once

#include <algorithm>
#include <list>
#include <map>

#include "SDL_ttf.h"

#include "ImageManager.h"
#include "Sprite.h"

#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 1050

#define W_IMAGE 110
#define H_IMAGE 35

#define W_FRAME 218
#define H_FRAME 35

#define W_NUMBER_BOX 25
#define H_NUMBER_BOX 24

#define W_NUMBER 18
#define H_NUMBER 21

#define X_DECAL_TEXT 40

#define X_DECAL_COST 10
#define W_COST 15
#define H_COST 30

#define W_GEM 28
#define H_GEM 28

class SpriteManager
{
public:
	SpriteManager(SDL_Renderer *renderer);
	~SpriteManager();

	static const int POS_X_ZONE = 0;
	static const int POS_Y_ZONE = 0;
	static const int H_LOCAL_ZONE = 765;
	static const int W_LOCAL_ZONE = 218;
	static const int DECAL_ZONE = 2;

	bool addCard(std::string cardName, std::string cost, std::string cardRarity, bool isLocalPlayer);
	bool drawAllSprite() const;
	void eraseAllSprite(bool eraseAll = false);
	const std::list<Sprite*> *getSpriteList() const;

private:
	SDL_Texture *AddFrame();
	SDL_Texture *AddImage(std::string &fileName) const;
	SDL_Texture *AddText(std::string &cardName) const;
	SDL_Texture *AddRarityGem(std::string &cardRarity, Sprite *sprite) const;

	std::string cardNameToFileName(std::string &cardName) const;

	void replaceAll(std::string& str, const std::string& from, const std::string& to) const;
	void addSpriteinList(Sprite *newSprite);

	SDL_Renderer *_renderer;
	SDL_Texture *_frameTexture;
	std::list<Sprite*> _spriteList;
	std::map<std::string, Sprite*> _cardList;
};

