#include <QtCore/QCoreApplication>
#include "controller.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Controller controller;
//    MainWindow mainWindow;
//    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
//    mainWindow.showExpanded();
//    app.setGlobalStrut(QSize(45,45));//increase size of scrollbars by setting global minimum size of all widgets
    return app.exec();
}

