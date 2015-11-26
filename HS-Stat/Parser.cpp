#include "Parser.h"


Parser::Parser()
{
	clearSaveId();
}


Parser::~Parser()
{
	clearSaveId();
}

bool Parser::isnewGame(const std::string &line)
{
	size_t pos2 = line.find("to OPPOSING PLAY (Hero)");
	if (pos2 == std::string::npos)
	{
		pos2 = line.find("to FRIENDLY PLAY (Hero)");
		if (pos2 == std::string::npos)
		{
			return false;
		}
	}

	return true;
}

bool Parser::getIdFromLine(const std::string & line, std::string &cardId, bool &localPlayer)
{
	size_t pos2 = line.find("zone from FRIENDLY HAND");
	if (pos2 == std::string::npos)
	{
		size_t pos3 = line.find("zone from OPPOSING HAND");
		if (pos3 == std::string::npos)
		{
			pos3 = line.find("zone from OPPOSING SECRET");
			if (pos3 == std::string::npos)
			{
				return false;
			}
			else {
				pos3 = line.find("zone=SECRET");
				if (pos3 == std::string::npos)
					return false;
			}
		}
		else {
			pos3 = line.find("zone=PLAY");
			if (pos3 == std::string::npos)
				return false;
		}
	}
	else {
		pos2 = line.find("zone=HAND");
		if (pos2 == std::string::npos)
			return false;
	}

	size_t pos4 = line.find(" id=");
	if (pos4 == std::string::npos)
		return false;
	size_t pos5 = line.find(" ", pos4 + 1);
	if (pos5 == std::string::npos)
		return false;
	std::string uid = line.substr(pos4 + 4, pos5 - pos4 - 4);
	if (isIdAlreadySaved(uid))
		return false;
	_savedId.push_back(uid);

	size_t pos6 = line.find(" cardId=");
	if (pos6 == std::string::npos)
		return false;
	size_t pos7 = line.find(" ", pos6 + 1);
	if (pos7 == std::string::npos)
		return false;
	cardId = line.substr(pos6 + 8, pos7 - pos6 - 8);

	size_t pos8 = line.find(" player=");
	if (pos8 == std::string::npos)
		return false;
	size_t pos9 = line.find(" ", pos8);
	if (pos9 == std::string::npos)
		return false;
	localPlayer = (line.substr(pos8 + 8, 1).compare("1") == 0 ? true : false);
	
	std::cout << "UID : " << uid << std::endl;
	std::cout << "CARD ID : " << cardId << std::endl;
	std::cout << "LOCAL PLAYER ? : " << localPlayer << std::endl;

	return true;
}

bool Parser::isIdAlreadySaved(const std::string &uid) const
{
	for (auto currId : _savedId) 
	{
		if (currId.compare(uid) == 0)
			return true;
	}

	return false;
}

void Parser::clearSaveId()
{
	_savedId.clear();
}
