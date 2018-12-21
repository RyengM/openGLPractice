#include <iostream>
#include <System/mainScene.h>
#include <Targets/Quad.h>


MainScene::MainScene(QOpenGLWidget *opengl_widget) : opengl_widget_(opengl_widget)
{
    initialize();
}

MainScene::~MainScene()
{

}

void MainScene::initialize()
{
    target_scene_ = new TargetScene();
}