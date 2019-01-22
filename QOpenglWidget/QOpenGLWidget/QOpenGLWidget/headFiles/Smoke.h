#ifndef SMOKE_H
#define SMOKE_H

#include <glm/glm.hpp>
#include <headFiles/ShaderObject.h>

#define MAX_PARTICLES 1000

// struct for particles with initial configs
typedef struct
{
    bool active = false;
    float life = 0;
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 velocity = glm::vec3(0,0,0);
}particles;

class Smoke
{
public:

    Smoke();
    ~Smoke();

    void init();

    particles particle[MAX_PARTICLES];

private:
    ShaderObject smokeObject = ShaderObject();
    GLuint shader_program_;
    GLuint vao_;
    GLuint vbo_;
};

#endif // !SMOKE_H
