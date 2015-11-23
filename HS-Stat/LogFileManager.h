#pragma once

#include <sys/stat.h>
#include <string>
#include <fstream>
#include <vector>

#define LOG_FILE_LOCATION "C:\\Program Files (x86)\\Hearthstone\\Hearthstone_Data"
#define LOG_FILE_NAME "output_log_test.txt"
#define LOG_FILE_PATH "C:\\Program Files (x86)\\Hearthstone\\Hearthstone_Data\\output_log_test.txt"

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

