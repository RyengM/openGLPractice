#ifndef My_GLWidget
#define My_GLWidget

//#include <QtWidgets/QMainWindow>
#include <QOpenglwidget.h>
#include <ui_MyGLWidget.h>

#include <headFiles/Quad.h>
#include <headFiles/Camera.h>

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QOpenGLWidget *parent = Q_NULLPTR);
    ~MyGLWidget();

protected:
    // rewrite three necessary virtual functions
    /*
    initializeGL for rendering context, loading shaders and other resources, etc.. only be invoked once
    paintGL for redrawing everything in the widget
    resizeGL for setting up the OPENGL viewport, projection, etc
    */
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


private:
    Quad quad;
    Camera camera;

    Ui::MyGLWidgetClass ui;
};

#endif // !My_GLWidget