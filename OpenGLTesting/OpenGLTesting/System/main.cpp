#include <QtWidgets/QApplication>
#include "mainView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //initialize main window, including OPENGL and main scene
    MainView *mainView = new MainView();
    //show main window based on your platform
    mainView->show_up();
    return a.exec();
}
