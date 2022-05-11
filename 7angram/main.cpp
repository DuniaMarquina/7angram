//  Copyright (c) 2022 Cytrus. All rights reserved.
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1020,540);
    w.show();
    return a.exec();
}
