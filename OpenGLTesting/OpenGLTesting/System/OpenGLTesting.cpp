#include "OpenGLTesting.h"
#include "mainScene.h"
#include "QKeyEvent"

OpenGLTesting::OpenGLTesting(bool fullScreen)
{
    setWindowTitle(QStringLiteral("单一模组测试平台"));
    if (fullScreen)
        showFullScreen();
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
    MainScene *mainScene = new MainScene();
    mainScene->drawAxis();
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
    switch (e->key())
    {
    case Qt::Key_F2:
        fullScreen = !fullScreen;
        if (fullScreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
            setGeometry(0, 0, 640, 480);
        }
        update();
        break;
    case Qt::Key_Escape:
        close();
    }
}
