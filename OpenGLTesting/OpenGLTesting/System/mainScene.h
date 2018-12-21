#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <QOpenglWidget.h>
#include <QGraphicsScene.h>
#include <QOpenGLFunctions.h>
#include "TargetScene.h"

/*
    provide a surface for managing widgets and items
*/
class MainScene: public QGraphicsScene
{
public:
    MainScene(QOpenGLWidget *opengl_widget);
    ~MainScene();

    void initialize();

protected:
    /*void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void wheelEvent(QGraphicsSceneWheelEvent* event) override;*/

private:
    QOpenGLWidget* opengl_widget_ = nullptr;
    TargetScene *target_scene_ = nullptr;
};

#endif
