#include "OpenGLTesting.h"
#include "QKeyEvent"

OpenGLTesting::OpenGLTesting()
{

}

OpenGLTesting::OpenGLTesting(bool fullScreen)
{
    setWindowTitle(QStringLiteral("��һģ�����ƽ̨"));
    if (fullScreen)
        showFullScreen();
}

OpenGLTesting::~OpenGLTesting()
{
    delete mainScene;
}

void OpenGLTesting::initializeOpenGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 0.5);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGLTesting::initializeScene()
{
    mainScene = new MainScene();
    mainScene->drawAxis();
    //mainScene->renderQuad();
}

void OpenGLTesting::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLTesting::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
}
