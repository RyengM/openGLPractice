#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

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
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    TargetWidget* opengl_widget_ = nullptr;
};

#endif
