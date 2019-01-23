#ifndef SMOKE_H
#define SMOKE_H

#include <headFiles/Object.h>
#include <QRandom.h>

#define MAX_PARTICLES 1000

// struct for particles with initial configs
typedef struct
{
    bool active = false;
    float life = 0;
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 velocity = glm::vec3(0,0,0);
}particles;

class Smoke : protected Object
{
public:

    Smoke();
    ~Smoke();

    // initialize particle system and vertex preparation
    void init();
    // update and display particle system
    void render(Camera camera);
    glm::vec3 get_position();

    particles particles[MAX_PARTICLES];

private:
    glm::vec3 position_ = glm::vec3(0,0,0);
};

#endif // !SMOKE_H
