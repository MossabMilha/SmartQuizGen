#include "mainwindow.h"
#include "quizexamen.h"
#include "testconnection.h"


#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Run the Qt event loop
    return a.exec();
}
