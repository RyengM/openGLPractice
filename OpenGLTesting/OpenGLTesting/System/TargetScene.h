#ifndef TARGET_SCENE_H
#define TARGET_SCENE_H

#include <QOpenglFunctions.h>
#include <Targets/Quad.h>

/*
    main scene for showing target items
*/
class TargetScene : QOpenGLFunctions
{
public:
    //initialize necessary configuration
    TargetScene();

    //used for switching target item, is not necessary now
    void show_item(int current_show);
    void show_quad();

    int get_current_id();

private:
    //equals to the id of target shows on the screen
    int current_show = 0;

    Quad *quad = nullptr;

};

#endif
