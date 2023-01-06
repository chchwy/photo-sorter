#pragma once
#include <vector>

struct FileEntry
{
	qint64 size = 0;
	qint64 timestamp = 0;
	QString path;
};

struct FileSizeBucket
{
	qint64 min;
	qint64 max;

	bool inRange(int fileSize);

	//std::vector<FileEntry> 
};


class PhotoModel
{
public:
	PhotoModel();

	void scan();

	std::vector<FileEntry> m_fileEntries;
};

