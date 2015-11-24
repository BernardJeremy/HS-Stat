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
	bool isFileChange() const;
	std::vector<std::string> getNewText(bool saveNewSize = true);

private:
	unsigned int getFileSize() const;
	

private:
	unsigned int _lastSize;
	

};

