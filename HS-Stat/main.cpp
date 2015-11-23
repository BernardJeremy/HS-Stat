#include <windows.h>
#include <WinBase.h>
#include "LogFileManager.h"
#include "SdlDisplayer.h"
#include "CardDataManager.h"

int main(int, char**){
	LogFileManager *logFileManager = new LogFileManager;
	SdlDisplayer *displayer = new SdlDisplayer;
	CardDataManager * cardDataManager = new CardDataManager;
	bool loop = true;

	if (!cardDataManager->init() || !logFileManager->init() || !displayer->init()){
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
				if (line.empty())
					continue;
				std::string name;
				std::string cost;
				std::string rarity;
				bool localPlayer = true;

				cardDataManager->getDataFromId("EX1_116", name, rarity, cost);
				displayer->addCard(name, cost, rarity, true);
				displayer->addCard(name, cost, rarity, false);
			}
		}

		displayer->draw();
	}

	displayer->cleanup();
	delete displayer;

	delete logFileManager;

	return 0;
}