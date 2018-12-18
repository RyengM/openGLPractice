#ifndef _QUAD_
#define _QUAD_

#include <glm/glm.hpp>

class Quad
{
public:
    //basic parameters
    int id = 1;
    glm::vec3 position;
    Camera camera;

    Quad();

    void build_render_config();

private:
    GLuint shader_program_;
    GLuint vao_;
    GLuint vbo_;
};

#endif

