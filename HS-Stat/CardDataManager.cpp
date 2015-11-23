#include "CardDataManager.h"


CardDataManager::CardDataManager()
{
}


CardDataManager::~CardDataManager()
{
}

bool CardDataManager::init()
{
	if (!setAllCardJSON())
		return false;

	return true;
}

void CardDataManager::getDataFromId(std::string cardID, std::string &name, std::string &rarity, std::string &cost) const
{
	std::string content = getStringData(cardID);

	if (content.empty())
	{
		std::cout << "Card not found in data" << std::endl;
		return;
	}

	name = extractDataFromString(content, "\"name\":\"");
	rarity = extractDataFromString(content, "\"rarity\":\"");
	cost = extractDataFromString(content, "\"cost\":", true);
}

std::string CardDataManager::extractDataFromString(std::string content, std::string key, bool isInt) const
{
	size_t pos = content.find(key);
	size_t pos2 = content.find("\"", pos + key.length());
	std::string ret = content.substr(pos + key.length(), pos2 - pos - key.length() - (int)isInt);

	std::cout << key << " : " << ret << std::endl;
	return ret;
}

std::string CardDataManager::getStringData(std::string cardID) const
{
	std::string needle = "\"id\":\"";
	needle += cardID;
	needle += "\"";
	std::cout << "START ANALYSE JSON FOR " << needle << std::endl;

	size_t needlePos = _cardsData.find(cardID);
	if (needlePos == std::string::npos)
		return "";
	size_t closurePos = _cardsData.find("}", needlePos);
	if (closurePos == std::string::npos)
		return "";

	std::cout << "END ANALYSE JSON" << std::endl;
	return _cardsData.substr(needlePos, closurePos - needlePos + 6);
}

bool CardDataManager::setAllCardJSON()
{
	std::cout << "START LOADING JSON" << std::endl;
	std::string filePath = CardDataManager::getCurrentDir() + DATA_FILE_NAME;
	std::cout << filePath << std::endl;
	std::ifstream in(filePath, std::ios::in | std::ios::binary);

	if (in)
	{
		in.seekg(0, std::ios::end);
		_cardsData.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&_cardsData[0], _cardsData.size());
		in.close();

		std::cout << "END LOADING JSON" << std::endl;
		return true;
	}
	std::cout << "Fail Finding JSON" << std::endl;

	return false;
}

std::string CardDataManager::getCurrentDir()
{
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		return "";

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	return std::string(cCurrentPath);
}
