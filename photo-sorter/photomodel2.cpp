#include "stdafx.h"
#include "photomodel2.h"
#include <QDirIterator>
#include <QFileInfo>

bool cmpFileSize(const FileEntry& a, const FileEntry& b)
{
	return a.size < b.size;
}

PhotoModel::PhotoModel()
{
}

void PhotoModel::scan()
{
	QDirIterator di("E:\\Backups", QDir::Files, QDirIterator::Subdirectories);

	int count = 0;
	qint64 maxSize = 0;
	qint64 minSize = 999999999;

	while (di.hasNext())
	{
		QString filename = di.next();
		//qDebug() << filename;

		FileEntry entry;

		QFileInfo info(filename);
		entry.size = info.size();
		entry.path = filename;
		entry.timestamp = info.birthTime().toSecsSinceEpoch();

		//if (entry.size == 0)
		{
			//qWarning() << filename << entry.timestamp;
		}

		maxSize = std::max(maxSize, entry.size);
		minSize = std::min(minSize, entry.size);

		m_fileEntries.emplace_back(entry);
		count++;
	}
	qDebug() << "File Count=" << count;
	qDebug() << "Max Size=" << maxSize << ", Min Size=" << minSize;

	std::sort(m_fileEntries.begin(), m_fileEntries.end(), cmpFileSize);

	for (const auto& entry : m_fileEntries)
	{
		qDebug() << entry.size << entry.path; // << entry.timestamp;
	}
}

bool FileSizeBucket::inRange(int fileSize)
{
	return (fileSize >= min && fileSize < max);
}