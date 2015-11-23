#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>

#define DATA_FILE_NAME "\\AllSets.json"

#define GetCurrentDir _getcwd

class CardDataManager
{
public:
	CardDataManager();
	~CardDataManager();

	bool init();

	void getDataFromId(std::string cardID, std::string &name, std::string &rarity, std::string &cost) const;

	static std::string getCurrentDir();

private:
	bool setAllCardJSON();
	std::string getStringData(std::string cardID) const;
	std::string extractDataFromString(std::string content, std::string key, bool isInt = false) const;

private:
	std::string _cardsData;
};

