#include "SdlDisplayer.h"


SdlDisplayer::SdlDisplayer()
{
	_spriteManager = NULL;
	_cardDisplay = NULL;
	_currentMode = SdlDisplayer::DECK;
}


SdlDisplayer::~SdlDisplayer()
{
	if (_spriteManager)
		delete _spriteManager;
	if (_cardDisplay)
		delete _cardDisplay;
}

bool SdlDisplayer::init()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_DisplayMode dm;
	int windowXPos = SDL_WINDOWPOS_CENTERED;
	int widowHeight = SCREEN_HEIGHT;
	if (SDL_GetDesktopDisplayMode(0, &dm) == 0) {
		windowXPos = dm.w - SCREEN_WIDTH;
		widowHeight = dm.h;
	}
	else {
		std::cout << "SDL_GetDesktopDisplayMode failed: " << SDL_GetError() << std::endl;
	}

	_screen = SDL_CreateWindow(SCREEN_TITLE,
		windowXPos,	15,
		SCREEN_WIDTH, widowHeight,
		SDL_WINDOW_SHOWN);

	_renderer = SDL_CreateRenderer(_screen, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_screen == NULL || _renderer == NULL)
	{
		std::cout << "Impossible d'initialiser le mode écran à " << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << ": " << SDL_GetError() << std::endl;
		return false;
	}

	_spriteManager = new SpriteManager(this->_renderer);
	_cardDisplay = new CardDisplay(this->_renderer, _spriteManager);


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

bool SdlDisplayer::manageInput(Parser *parser, LogFileManager *logFileManager)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT){
			return false;
		}
		if (e.type == SDL_KEYUP){
			if (e.key.keysym.sym == SDLK_ESCAPE)
				return false;
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				this->switchMode();
			}
			else if (e.key.keysym.sym == SDLK_e)
			{
				_spriteManager->eraseAllSprite();
				parser->clearSaveId();
				logFileManager->resetSzeFromLastGame();
			}
		}
		if (e.type == SDL_WINDOWEVENT) {
			switch (e.window.event) {
				case SDL_WINDOWEVENT_ENTER:
					_cardDisplay->setHasFocus(true);
					break;
				case SDL_WINDOWEVENT_LEAVE:
					_cardDisplay->setHasFocus(false);
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					_cardDisplay->setHasFocus(true);
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					_cardDisplay->setHasFocus(false);
					break;
				default:
					break;
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

	if (_currentMode == SdlDisplayer::DECK)
	{
		_spriteManager->drawAllSprite();
		_cardDisplay->checkMousePosition();
	}

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

void SdlDisplayer::switchMode()
{
	if (_currentMode == SdlDisplayer::DECK)
		_currentMode = SdlDisplayer::BUTTON;
	else
		_currentMode = SdlDisplayer::DECK;
}