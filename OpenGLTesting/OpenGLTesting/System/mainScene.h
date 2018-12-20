#ifndef _MAINSCENE_
#define _MAINSCENE_

#include <QGL.h>
#include <QGraphicsScene.h>

/*
    provide a surface for managing widgets and items
*/
class MainScene: public QGraphicsScene
{
public:
    MainScene(QGLWidget *opengl_widget);
    ~MainScene();

    void initialize();


    void drawAxis();
    void renderQuad();

protected:
    /*void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void wheelEvent(QGraphicsSceneWheelEvent* event) override;*/

private:
    QGLWidget* opengl_widget_ = nullptr;
};

#endif
