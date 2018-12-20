#ifndef _OPENGL_TESTING_
#define _OPENGL_TESTING_

#include <GL/glew.h>
#include <QOpenglWidget.h>
#include "mainScene.h"
#include "ui_OpenGLTesting.h"

/*
    Main window class, used for launching system
*/

class OpenGLTesting : public QOpenGLWidget
{
    Q_OBJECT

public:
    OpenGLTesting();
    OpenGLTesting(bool fullScreen);

    ~OpenGLTesting();

    void initializeOpenGL();
    void resizeGL(int width, int height);

    void initializeScene();

    void keyPressEvent(QKeyEvent *e);

private:
    bool fullScreen;
    MainScene *mainScene;
    Ui::OpenGLTestingClass ui;
};

#endif