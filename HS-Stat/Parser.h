#pragma once

#include <string>
#include <list>
#include <iostream>

class Parser
{
public:
	Parser();
	~Parser();

	bool getIdFromLine(const std::string &line, std::string &cardId, bool &localPlayer);
	bool isnewGame(const std::string &line);
	void clearSaveId();

private:
	bool isIdAlreadySaved(const std::string &uid) const;

private:
	std::list<std::string> _savedId;
};

