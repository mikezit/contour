#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include <QDialog>
#include <QIcon>
#include <QProcess>
#include "mainwindow.h"

struct china {
     int name;
     int id;
     long group;
     china *next;
};

struct info{
     unsigned int res:2;
};

int main(int argc, char **argv)
{
     QApplication app(argc, argv);
     app.setWindowIcon(QIcon("../../contour.ico"));
     MainWindow window;
     window.show();
     return app.exec();
}
