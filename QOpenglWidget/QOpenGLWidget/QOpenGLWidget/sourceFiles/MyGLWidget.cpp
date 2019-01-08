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
    //quad = Quad();
    //quad.build_render_config();

    /*float vertex[] = { 0.f, 0.f, 0.f };
    GLuint VBO;
    f->glGenBuffers(1, &VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);*/
}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //quad.render();
    //f->glDrawArrays(GL_POINTS, 0, 1);
}

void MyGLWidget::resizeGL(int w, int h)
{

}