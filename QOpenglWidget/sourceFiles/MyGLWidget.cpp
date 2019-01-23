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
    delete timer;
}

void MyGLWidget::initializeGL()
{
    // set timer to refresh screen per 20ms, setting at keyPressEvent
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &MyGLWidget::updateScene);

    std::cout << "initialize OPENGL" << std::endl;
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.1, 0, 0, 1);
    f->glEnable(GL_DEPTH_TEST);
    // ready for quad rendering
    //quad = Quad();
    //quad.build_render_config();
    smoke = Smoke();
    smoke.init();
    camera = Camera(smoke.get_position());
    //camera = Camera(quad.get_position());
}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //quad.render(camera);
    smoke.render(camera);
}

void MyGLWidget::resizeGL(int w, int h)
{
    showMaximized();
}

void MyGLWidget::updateScene()
{
    update();
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        if (simulation_condition == 0 || simulation_condition == 2)
        {
            simulation_condition = 1;
            timer->start(20);
        }
        else
        {
            simulation_condition = 2;
            timer->stop();
        }
            
    }
    if (event->key() == Qt::Key_S)
    {
        simulation_condition = 0;
        timer->stop();
        // current_target.reset();
    }
    if (event->key() == Qt::Key_Escape)
        exit(0);
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