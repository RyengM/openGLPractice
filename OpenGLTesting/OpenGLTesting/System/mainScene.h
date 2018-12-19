#ifndef _MAINSCENE_
#define _MAINSCENE_

#include <QGraphicsScene.h>

/*
    mainScene, used for basic view and operation
*/
class MainScene: public QGraphicsScene
{
public:
    MainScene();
    void drawAxis();
    void renderQuad();

protected:
    /*void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void wheelEvent(QGraphicsSceneWheelEvent* event) override;*/

private:

};

#endif
