#ifndef _QUAD_
#define _QUAD_

#include <glm/glm.hpp>
#include <Shader/ShaderObject.h>
#include <Camera/Camera.h>
#include <QOpenGLExtraFunctions>

class Quad : protected QOpenGLExtraFunctions
{
public:
    //basic parameters
    int id = 1;
    glm::vec3 position;
    Camera camera;

    Quad();

    void build_render_config();
    void render();

private:
    char const* vertexInfo;
    QOpenGLExtraFunctions *glf;
    ShaderObject quadObject = ShaderObject();
    GLuint shader_program_;
    GLuint vao_;
    GLuint vbo_;
};

#endif

