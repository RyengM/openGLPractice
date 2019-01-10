#ifndef _QUAD_
#define _QUAD_

#include <glm/glm.hpp>
#include <Shader/ShaderObject.h>
#include <Camera/Camera.h>
#include <QOpenGLExtraFunctions>

class Quad : protected QOpenGLExtraFunctions
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
    ShaderObject quadObject = ShaderObject();
    GLuint shader_program_;
    GLuint vao_;
    GLuint vbo_;
};

#endif
