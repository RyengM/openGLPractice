#include <QOpenGLFunctions.h>
#include <QOpenGLContext.h>
#include <iostream>
#include <headFiles/MyGLWidget.h>

MyGLWidget::MyGLWidget(QOpenGLWidget *parent)
    : QOpenGLWidget(parent)
{

}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL()
{
    std::cout << "initialize OPENGL" << std::endl;
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.1, 0, 0, 1);

    // ready for quad rendering
    quad = Quad();
    quad.build_render_config();
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    quad.render();
}

void MyGLWidget::resizeGL(int w, int h)
{

}