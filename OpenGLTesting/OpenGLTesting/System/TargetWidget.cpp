#include "TargetWidget.h"
#include "QOpenGLContext.h"

#include <iostream>

TargetWidget::TargetWidget(QWidget *parent):QOpenGLWidget(parent)
{

}

TargetWidget::~TargetWidget()
{

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

void TargetWidget::initializeGL()
{
    std::cout << "initialize OPENGL" << std::endl;
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
    show_quad();
}

void TargetWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glLoadIdentity();
    quad->render();
}

void TargetWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TargetWidget::key_press(QKeyEvent* event) 
{

}

void TargetWidget::mouse_press(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton)
    {
        key_last_.x = event->screenPos().x();
        key_last_.y = event->screenPos().y();
        key_pressed_ = true;
    }
}

void TargetWidget::mouse_move(QGraphicsSceneMouseEvent* event)
{
    if (!key_pressed_) return;

    glm::vec2 current_pos(event->screenPos().x(), event->screenPos().y());
    glm::vec2 delta = (current_pos - key_last_) * 0.1f;

    // adjust the parameters of camera

    key_last_ = current_pos;
}

void TargetWidget::mouse_release(QGraphicsSceneMouseEvent* event)
{
    key_pressed_ = false;
}