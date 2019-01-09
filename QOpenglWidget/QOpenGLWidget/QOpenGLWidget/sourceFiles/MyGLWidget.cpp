#include <QOpenGLFunctions.h>
#include <QOpenGLContext.h>
#include <QEvent.h>
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
    f->glEnable(GL_DEPTH_TEST);
    // ready for quad rendering
    quad = Quad();
    quad.build_render_config();

    camera = Camera(quad.get_position());
}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    quad.render(camera);
}

void MyGLWidget::resizeGL(int w, int h)
{
    showMaximized();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_pos_last.x = event->screenPos().x();
    mouse_pos_last.y = event->screenPos().y();

    mouse_press = true;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mouse_press) return;

    glm::vec2 current_pos(event->screenPos().x(), event->screenPos().y());
    glm::vec2 delta = (current_pos - mouse_pos_last) * 0.1f;

    float phi = camera.get_phi();
    float theta = camera.get_theta();

    phi += delta.x;
    theta += delta.y;

    camera.set_phi(phi);
    camera.set_theta(theta);
    camera.rotate();

    mouse_pos_last = current_pos;
    update();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    camera.zoom(event->delta()*(-0.1));
    update();
}