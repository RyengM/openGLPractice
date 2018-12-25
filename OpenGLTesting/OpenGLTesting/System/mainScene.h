#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <QOpenglWidget.h>
#include <QGraphicsScene.h>
#include <QOpenGLFunctions.h>

#include "TargetWidget.h"

/*
    provide a surface for managing widgets and items
*/
class MainScene: public QGraphicsScene
{
public:
    MainScene(TargetWidget *opengl_widget);
    ~MainScene();

    void initialize();

protected:
    void key_press(QKeyEvent* event) const;
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void wheelEvent(QGraphicsSceneWheelEvent* event) const;

private:
    TargetWidget* opengl_widget_ = nullptr;
};

#endif
