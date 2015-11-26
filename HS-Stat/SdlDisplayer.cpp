#include "SdlDisplayer.h"


SdlDisplayer::SdlDisplayer()
{
	_spriteManager = NULL;
}


SdlDisplayer::~SdlDisplayer()
{
	if (_spriteManager)
		delete _spriteManager;
}

bool SdlDisplayer::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	_screen = SDL_CreateWindow(SCREEN_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	_renderer = SDL_CreateRenderer(_screen, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_screen == NULL || _renderer == NULL)
	{
		std::cout << "Impossible d'initialiser le mode écran à " << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << ": " << SDL_GetError() << std::endl;
		return false;
	}

	_spriteManager = new SpriteManager(this->_renderer);


	// load support for the PNG image formats
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		std::cout << "IMG_Init Error : " << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init Error : " << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

void SdlDisplayer::cleanup()
{
	SDL_DestroyRenderer(_renderer);
	_renderer = NULL;
	SDL_DestroyWindow(_screen);
	_screen = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool SdlDisplayer::manageInput(Parser *parser)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT){
			return false;
		}
		if (e.type == SDL_KEYUP){
			if (e.key.keysym.sym == SDLK_ESCAPE)
				return false;
			else if (e.key.keysym.sym == SDLK_e)
			{
				_spriteManager->eraseAllSprite();
				parser->clearSaveId();
			}
		}
	}
	return true;
}

bool SdlDisplayer::draw()
{
	static bool firstTime = true;

	if (firstTime) {
		firstTime = false;
	}

	SDL_SetRenderDrawColor(_renderer, 14, 25, 55, 255);
	SDL_RenderClear(_renderer);

	_spriteManager->drawAllSprite();

	SDL_RenderPresent(_renderer);

	SDL_Delay(1);
	return true;
}

bool SdlDisplayer::addCard(std::string cardName, std::string cost, std::string cardRarity, bool isLocalPlayer) const
{
	return _spriteManager->addCard(cardName, cost, cardRarity, isLocalPlayer);
}

void SdlDisplayer::eraseAllSprite() const
{
	_spriteManager->eraseAllSprite();
}
