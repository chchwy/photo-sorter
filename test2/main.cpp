#include <QtCore/QCoreApplication>
#include <gtest/gtest.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	a.exit();
	return 0;
}
