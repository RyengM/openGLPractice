#include "OpenGLTesting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGLTesting w;
    w.show();
    return a.exec();
}
