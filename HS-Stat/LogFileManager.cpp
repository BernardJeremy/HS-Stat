#include "LogFileManager.h"


LogFileManager::LogFileManager()
{
	_lastSize = 0;
	_sizeFromLastGame = 0;
}

LogFileManager::~LogFileManager()
{
}

bool LogFileManager::init()
{
	if (!isFileExist())
		return true;

	_lastSize = getFileSize();
	_sizeFromLastGame = getFileSize();
	return true;
}

bool LogFileManager::isFileExist() const
{
	struct stat buffer;

	return (stat(LOG_FILE_PATH, &buffer) == 0);
}

bool LogFileManager::isFileChange()
{
	if (_lastSize > getFileSize())  {
		_lastSize = getFileSize();
		_sizeFromLastGame = getFileSize();
	}

	return (_lastSize != getFileSize());
}

std::vector<std::string> LogFileManager::getNewText(bool saveNewSize)
{
	std::ifstream infile(LOG_FILE_PATH);
	std::vector<std::string> list;
	std::string line;
	long long index = _sizeFromLastGame;

	if (_sizeFromLastGame <= 0) {
		_sizeFromLastGame = getFileSize();
		index = _sizeFromLastGame;
	}

	infile.seekg(index);
	while (std::getline(infile, line))
	{
		list.push_back(line);
	}

	if (saveNewSize)
		_lastSize = getFileSize();

	return list;
}

void LogFileManager::updateSizeFromLastGame()
{
	_sizeFromLastGame = getFileSize();
	_lastSize = getFileSize();
}

void LogFileManager::resetFileIndex()
{
	_sizeFromLastGame = 1;
	_lastSize = 1;
}

long long LogFileManager::getFileSize() const
{
	std::ifstream is;
	long long length = 0;

	is.open(LOG_FILE_PATH, std::ios::binary);
	is.seekg(0, std::ios::end);
	length = is.tellg();
	is.close();

	return(length);
}

