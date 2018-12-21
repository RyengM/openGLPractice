#include "TargetScene.h"

TargetScene::TargetScene()
{

}

void TargetScene::show_item(int id)
{
    //to do after
}

void TargetScene::show_quad()
{
    quad = new Quad();
    quad->render();
}

int TargetScene::get_current_id()
{
    return current_show;
}