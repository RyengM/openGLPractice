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
    timer->start(20);
    connect(timer, &QTimer::timeout, this, &MyGLWidget::updateScene);

    std::cout << "initialize OPENGL" << std::endl;
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0, 0, 0, 1);
    f->glEnable(GL_DEPTH_TEST);
    // ready for quad rendering
    //quad = Quad();
    //quad.build_render_config();
    smoke = Smoke();
    smoke.init();
    camera = Camera(smoke.get_position());
    smoke.render(camera, simulation_status);
    std::cout << "OpenGL initialize ready..." << std::endl;
    //camera = Camera(quad.get_position());

    // prepare basic opengl config
    f->glEnable(GL_BLEND);
    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    f->glEnable(GL_DEPTH_TEST);
}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    
    //quad.render(camera);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    smoke.render(camera, simulation_status);
}

void MyGLWidget::resizeGL(int w, int h)
{
    showMaximized();
}

void MyGLWidget::updateScene()
{
    // invoke virtual function
    update();
    
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        if (simulation_status == SIMULATION_INIT || simulation_status == SIMULATION_STOP)
            simulation_status = SIMULATION_RUN;
        else
            simulation_status = SIMULATION_STOP;
            
    }
    if (event->key() == Qt::Key_S)
    {
        simulation_status = SIMULATION_INIT;
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