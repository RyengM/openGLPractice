#ifndef TARGET_SCENE_H
#define TARGET_SCENE_H

#include <QOpenglFunctions.h>
#include <QOpenGLWidget.h>
#include <Targets/Quad.h>

/*
    main widget for showing target items, the specific frame for OPENGL in QT
*/
class TargetWidget : public QOpenGLWidget , protected QOpenGLFunctions
{
public:
    //initialize necessary configuration
    TargetWidget();

    //used for switching target item, is not necessary now
    void show_item(int current_show);
    void show_quad();

    int get_current_id();
protected:
    //rewrite three necessary functions
    void initilizeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    //equals to the id of target shows on the screen
    int current_show = 0;

    Quad *quad = nullptr;

};

#endif
