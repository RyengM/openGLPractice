#include "TargetWidget.h"

TargetWidget::TargetWidget()
{
    show_quad();
}

void TargetWidget::show_item(int id)
{
    //to do after
}

void TargetWidget::show_quad()
{
    quad = new Quad();
    quad->render();
}

int TargetWidget::get_current_id()
{
    return current_show;
}

// rewrite functions
void TargetWidget::initilizeGL()
{
    initializeOpenGLFunctions();
}

void TargetWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void TargetWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}