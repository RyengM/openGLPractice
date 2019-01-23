#include <headFiles/MyGLWidget.h>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGLWidget w;
    w.show();
    return a.exec();
}
