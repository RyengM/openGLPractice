#ifndef TARGET_WIDGET_H
#define TARGET_WIDGET_H

#include <QOpenglwidget.h>

#include <Targets/Quad.h>
#include <Camera/Camera.h>

class TargetWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit TargetWidget();
    ~TargetWidget();

protected:
    // rewrite three necessary virtual functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // initializeGL for rendering context, loading shaders and other resources, etc.. only be invoked once
    // paintGL for redrawing everything in the widget
    // resizeGL for setting up the OPENGL viewport, projection, etc
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    // rewrite event handle functions
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Quad quad;
    Camera camera;

    glm::vec2 mouse_pos_last;           // the position of mouse on screen, including x and y
    boolean mouse_press;                // signal whether mouse is pressed
};

#endif // TARGET_WIDGET_H