#include <windows.h>
#include <WinBase.h>
#include "LogFileManager.h"
#include "SdlDisplayer.h"

int main(int, char**){
	LogFileManager *logFileManager = new LogFileManager;
	SdlDisplayer *displayer = new SdlDisplayer;
	bool loop = true;

	logFileManager->init();
	if (!displayer->init()){
		loop = false;
	}

	while (loop)
	{
		loop = displayer->manageInput();
		if (logFileManager->isFileChange())
		{
			std::vector<std::string> list;
			list = logFileManager->getNewText();
			for (auto line : list)
			{
				std::cout << line << std::endl;
				displayer->addCard(line, "2", "rare", true);
				displayer->addCard(line, "4", "legendary", false);
			}
		}

		displayer->draw();
	}

	displayer->cleanup();
	delete displayer;

	delete logFileManager;

	return 0;
}