#include <gtest/gtest.h>
#include <QDirIterator>
#include <QDebug>
#include "photomodel2.h"


class TriagePath : public ::testing::Test
{
protected:
	TriagePath()
	{
		infos.resize(10);
		infos[0] = QFileInfo("C:\\photos\\PXL_JPG\\PXL_20201002_133608818.jpg");
		infos[1] = QFileInfo("C:\\photos\\PXL_JPG\\PXL_20201002_133608818.JPG");
		infos[2] = QFileInfo("C:\\photos\\IMG_JPG\\IMG_20131114_133203.jpg");
		infos[3] = { "C:\\photos\\Backups\\100MEDIA\\FB_IMG_1488936000593.jpg" };

	}
	std::vector<QFileInfo> infos;
};

TEST_F(TriagePath, TypicalPXL)
{
	EXPECT_TRUE(isPXLTypical(infos[0]));
	EXPECT_FALSE(isPXLTypical(infos[1]));
	EXPECT_FALSE(isPXLTypical(infos[2]));
	EXPECT_FALSE(isPXLTypical(infos[3]));
}

TEST_F(TriagePath, TypicalIMG)
{
	EXPECT_EQ(isIMGTypical(infos[0]), false);
	EXPECT_EQ(isIMGTypical(infos[1]), false);
	EXPECT_EQ(isIMGTypical(infos[2]), true);
	EXPECT_EQ(isIMGTypical(infos[3]), false);
}

TEST(Triage, CheckPXLFolder)
{
	QDirIterator di("C:\\photos\\PXL_JPG", QDir::Files, QDirIterator::Subdirectories);
	int count = 0;
	int not_match = 0;
	while (di.hasNext())
	{
		QFileInfo info = di.fileInfo();
		di.next();
		
		bool ok = isPXLTypical(info);
		//EXPECT_TRUE(ok);
		if (!ok)
		{
			//qDebug() << info.fileName();
			//not_match++;
		}
		count++;
	}
	qDebug() << count << not_match;
}

TEST(Triage, CheckIMGFolder)
{
	QDirIterator di("C:\\photos\\IMG_JPG", QDir::Files);
	int count = 0;
	while (di.hasNext())
	{
		QString s = di.next();
		QFileInfo info = di.fileInfo();

		bool ok = isIMGTypical(info);
		EXPECT_TRUE(ok);
		if (!ok)
			qDebug() << "Fail:" << s << info.absoluteFilePath();
		count++;
	}
	qDebug() << count;
}

#define ROOT_DIR "C:\\photos\\Backups"
TEST(Triage, movefile)
{
	QDirIterator di(ROOT_DIR, QDir::Files, QDirIterator::Subdirectories);

	QDir dest("C:\\photos\\IMG_JPG");
	QDir check("C:\\photos\\Check");

	int pxlCount = 0;
	int totalCount = 0;
	while (di.hasNext())
	{
		const QString s = di.next();
		const QFileInfo info = di.fileInfo();

		QString f = info.fileName();
		if (isIMGTypical(f))
		{
			QString baseName = info.completeBaseName();
			//QStringList tokens = baseName.split(QChar('_'));
			pxlCount++;

			bool ok = true;
			ok = QFile::rename(s, dest.filePath(f));
			EXPECT_TRUE(ok);

			if (!ok)
			{
				qDebug() << s;
				qDebug() << dest.filePath(f);

				ok = QFile::rename(s, check.filePath(f));
				EXPECT_TRUE(ok);
			}

			if (pxlCount % 100 == 0)
				qDebug() << pxlCount;
		}
	}

	qDebug() << "PXL Count=" << pxlCount;
	//qDebug() << "Total Count=" << totalCount;
}
