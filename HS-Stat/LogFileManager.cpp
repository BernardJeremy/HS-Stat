#include "LogFileManager.h"


LogFileManager::LogFileManager()
{
}


LogFileManager::~LogFileManager()
{
}

bool LogFileManager::init()
{
	if (!isFileExist())
		return true;

	_lastSize = getFileSize();
	return true;
}

bool LogFileManager::isFileExist() const
{
	struct stat buffer;
	return (stat(LOG_FILE_PATH, &buffer) == 0);
}

bool LogFileManager::isFileChange() const
{
	return (_lastSize != getFileSize());
}

std::vector<std::string> LogFileManager::getNewText(bool saveNewSize)
{
	std::ifstream infile(LOG_FILE_PATH);
	std::vector<std::string> list;
	std::string line;
	int index = _lastSize;

	infile.seekg(index);
	while (std::getline(infile, line))
	{
		list.push_back(line);
	}

	if (saveNewSize)
		_lastSize = getFileSize();

	return list;
}

unsigned int LogFileManager::getFileSize() const
{
	struct stat buffer;
	
	if (stat(LOG_FILE_PATH, &buffer) != 0)
		return 0;
	return buffer.st_size;
}

