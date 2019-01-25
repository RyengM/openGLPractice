#ifndef SMOKE_H
#define SMOKE_H

#include <headFiles/Object.h>
#include <QRandom.h>
#include <curand_kernel.h>

#define MAX_PARTICLES 1000

// struct for particles with initial configs
typedef struct
{
    bool active = false;
    float life = 0;
    glm::vec3 offset = glm::vec3(0,0,0);
    glm::vec3 velocity = glm::vec3(0,0,0);
}Particles;

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

    Particles particles[MAX_PARTICLES];

private:

    void init_cuda();
    void update_cuda();
    void free_cuda();

    // position_ is the pos of particles, not each particle
    glm::vec3 position_ = glm::vec3(0,0,0);

    GLuint position_buffer_;
    cudaGraphicsResource_t position_buffer_resource_;
    curandState* curand_state;

};

#endif // !SMOKE_H
