#include <iostream>
#include <System/mainScene.h>
#include <QPainter.h>


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

void MainScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->beginNativePainting();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            
        }
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
    glPopAttrib();
    painter->endNativePainting();
    painter->restore();
}