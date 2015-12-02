#pragma once

#include <sys/stat.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>

#define LOG_FILE_PATH "C:\\Program Files (x86)\\Hearthstone\\Hearthstone_Data\\output_log.txt"

class LogFileManager
{
public:
	LogFileManager();
	~LogFileManager();

	bool init();
	bool isFileExist() const;
	bool isFileChange();
	std::vector<std::string> getNewText(bool saveNewSize = true);
	void updateSizeFromLastGame();

private:
	long long getFileSize() const;
	
private:
	long long _lastSize;
	long long _sizeFromLastGame;
	

};

