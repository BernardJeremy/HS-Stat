#include <windows.h>
#include <WinBase.h>
#include "LogFileManager.h"
#include "SdlDisplayer.h"
#include "CardDataManager.h"
#include "Parser.h"

int main(int, char**){
	LogFileManager *logFileManager = new LogFileManager;
	SdlDisplayer *displayer = new SdlDisplayer;
	CardDataManager *cardDataManager = new CardDataManager;
	Parser *parser = new Parser;
	bool loop = true;

	if (!cardDataManager->init() || !logFileManager->init() || !displayer->init()){
		loop = false;
	}

	while (loop)
	{
		loop = displayer->manageInput(parser);
		if (logFileManager->isFileChange())
		{
			std::vector<std::string> list;
			list = logFileManager->getNewText();
			for (auto line : list)
			{
				std::string name;
				std::string cost;
				std::string rarity;
				std::string id;
				bool localPlayer = true;

				if (line.empty() || !parser->getIdFromLine(line, id, localPlayer))
					continue;

				cardDataManager->getDataFromId(id, name, rarity, cost);
				displayer->addCard(name, cost, rarity, localPlayer);
			}
		}

		displayer->draw();
	}

	displayer->cleanup();
	
	delete displayer;
	delete logFileManager;
	delete cardDataManager;
	delete parser;

	return 0;
}