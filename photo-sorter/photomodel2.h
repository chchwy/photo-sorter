#pragma once
#include<vector>
#include<cstdint>
#include<QString>

class QFileInfo;

struct FileEntry
{
	int64_t size = 0;
	int64_t timestamp = 0;
	QString path;
};

struct FileSizeBucket
{
	int64_t min;
	int64_t max;

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

bool isPXLTypical(const QFileInfo& fileInfo);
bool isIMGTypical(const QFileInfo& fileInfo);
bool isIMG_HDR(const QFileInfo&);
bool isPXLVideo(const QFileInfo& fileInfo);
bool isVIDVideo(const QFileInfo& fileInfo);
bool isIMAG0000(const QFileInfo&);