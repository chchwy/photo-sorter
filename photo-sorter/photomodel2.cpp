#include "photomodel2.h"
#include <QDirIterator>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>

bool cmpFileSize(const FileEntry& a, const FileEntry& b)
{
	return a.size < b.size;
}

bool isPXLTypical(const QFileInfo& fileInfo)
{
	// PXL_20220103_202455910.jpg
	
	const QString fileName = fileInfo.fileName();
	QRegularExpression re("^PXL_[0-9]{8}_[0-9]{9}.jpg$");
	auto match = re.match(fileName);

	return match.hasMatch();
}

bool isIMGTypical(const QFileInfo& fileInfo)
{
	const QString fileName = fileInfo.fileName();
	QRegularExpression re("^IMG_[0-9]{8}_[0-9]{6}.jpg$");
	auto match = re.match(fileName);
	return match.hasMatch();
}

bool isIMG_HDR(const QFileInfo& fileInfo)
{
	const QString fileName = fileInfo.fileName();
	QRegularExpression re("^IMG_[0-9]{8}_[0-9]{6}_HDR.jpg$");
	auto match = re.match(fileName);
	return match.hasMatch();
}

bool isPXLVideo(const QFileInfo& fileInfo)
{
	const QString fileName = fileInfo.fileName();
	QRegularExpression re("^PXL_[0-9]{8}_[0-9]{9}.mp4$");
	auto match = re.match(fileName);
	return match.hasMatch();
}

bool isVIDVideo(const QFileInfo& fileInfo)
{
	//^VID_[0-9]{8}_[0-9]{6}.mp4$
	const QString fileName = fileInfo.fileName();
	QRegularExpression re("^VID_[0-9]{8}_[0-9]{6}.mp4$");
	auto match = re.match(fileName);
	return match.hasMatch();
}

bool isIMAG0000(const QFileInfo& fileInfo)
{
	const QString fileName = fileInfo.fileName();
	QRegularExpression re("^IMAG[0-9]{4}.jpg$");
	auto match = re.match(fileName);
	return match.hasMatch();
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
