#include "OpenGLTesting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //initialize main window, including OPENGL and main scene
    OpenGLTesting launch(false);
    launch.initializeOpenGL();
    launch.initializeScene();
    return a.exec();
}
