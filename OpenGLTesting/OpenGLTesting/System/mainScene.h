#ifndef _MAINSCENE_
#define _MAINSCENE_

#include <QOpenglWidget.h>
#include <QGraphicsScene.h>

/*
    provide a surface for managing widgets and items
*/
class MainScene: public QGraphicsScene
{
public:
    MainScene(QOpenGLWidget *opengl_widget);
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
    QOpenGLWidget* opengl_widget_ = nullptr;
};

#endif
