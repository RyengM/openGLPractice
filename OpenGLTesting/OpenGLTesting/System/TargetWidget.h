#ifndef TARGET_SCENE_H
#define TARGET_SCENE_H

#include <QOpenglFunctions.h>
#include <QOpenGLWidget.h>
#include <QGraphicsSceneEvent.h>
#include <Targets/Quad.h>

/*
    main widget for showing target items, the specific frame for OPENGL in QT
*/
class TargetWidget : public QOpenGLWidget , protected QOpenGLFunctions
{
public:
    // initialize necessary configuration
    TargetWidget();

    // used for switching target item, is not necessary now
    void show_item(int current_show);
    void show_quad();

    int get_current_id();

    // outer interaction
    void key_press(QKeyEvent* event);
    void mouse_press(QGraphicsSceneMouseEvent* event);
    void mouse_move(QGraphicsSceneMouseEvent* event);
    void mouse_release(QGraphicsSceneMouseEvent* event);

protected:
    // rewrite three necessary virtual functions
    /*
        initializeGL for rendering context, loading shaders and other resources, etc.. only be invoked once
        paintGL for redrawing everything in the widget 
        resizeGL for setting up the OPENGL viewport, projection, etc
    */
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    // equals to the id of target shows on the screen
    int current_show = 0;

    Quad *quad = nullptr;

    glm::vec2 key_last_;
    bool key_pressed_ = false;
};

#endif
