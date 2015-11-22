#include "SdlDisplayer.h"

int main(int, char**){
	SdlDisplayer *displayer = new SdlDisplayer;
	bool loop = true;

	if (!displayer->init()){
		loop = false;
	}

	while (loop)
	{
		loop = displayer->manageInput();

		displayer->draw();
	}

	displayer->cleanup();

	return 0;
}