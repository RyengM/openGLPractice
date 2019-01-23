#ifndef SMOKE_H
#define SMOKE_H

#include <headFiles/Object.h>

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

    void init();

    particles particle[MAX_PARTICLES];

private:
    
};

#endif // !SMOKE_H
