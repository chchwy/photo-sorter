#include "stdafx.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "photomodel2.h"

int main(int argc, char *argv[])
{
    PhotoModel model;
    model.scan();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
