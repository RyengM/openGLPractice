#ifndef _QUAD_
#define _QUAD_

#include <headFiles/Object.h>

class Quad : protected Object
{
public:
    Quad();
    ~Quad();

    void build_render_config();
    void render(Camera camera);

    glm::vec3 get_position();

private:
    // basic parameters
    //int id = 1;
    glm::vec3 position;
    float* vertexInfo;
};

#endif
