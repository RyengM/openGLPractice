#include <iostream>
#include <System/mainScene.h>


MainScene::MainScene(TargetWidget *opengl_widget) : opengl_widget_(opengl_widget)
{
    
}

MainScene::~MainScene()
{

}

void MainScene::initialize()
{
    //opengl_widget_->show_quad();
}

void MainScene::key_press(QKeyEvent* event) const
{

}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->isAccepted()) return;

    opengl_widget_->mouse_press(event);
    event->accept();
}

void MainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (event->isAccepted()) return;

    opengl_widget_->mouse_release(event);
    event->accept();
}

void MainScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (event->isAccepted()) return;

    opengl_widget_->mouse_move(event);
    event->accept();
}

void MainScene::wheelEvent(QGraphicsSceneWheelEvent* event) const
{

}
