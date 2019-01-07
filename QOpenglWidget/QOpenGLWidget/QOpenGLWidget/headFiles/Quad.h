#ifndef _QUAD_
#define _QUAD_

#include <glm/glm.hpp>
#include <headFiles/ShaderObject.h>
#include <headFiles/Camera.h>
#include <QOpenGLExtraFunctions>

class Quad : protected QOpenGLExtraFunctions
{
public:
    Quad();
    ~Quad();

    void build_render_config();
    void render();

private:
    // basic parameters
    int id = 1;
    glm::vec3 position;
    Camera camera;
    float* vertexInfo;
    ShaderObject quadObject = ShaderObject();
    GLuint shader_program_;
    GLuint vao_;
    GLuint vbo_;
};

#endif
