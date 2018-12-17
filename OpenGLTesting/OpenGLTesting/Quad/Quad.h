#ifndef _QUAD_
#define _QUAD_

#include <glm/glm.hpp>

class Quad
{
public:
    //basic parameters
    glm::vec3 position;

    Quad();

    void drawQuadHandler();
    void useGLDraw();

private:
    GLuint shaderProgram;
    GLuint VAO;
};

#endif

