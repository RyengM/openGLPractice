#ifndef SMOKE_H
#define SMOKE_H

#include <headFiles/ShaderObject.h>
#include <headFiles/Camera.h>

#define MAX_PARTICLES 10000
#define SIMULATION_INIT 0
#define SIMULATION_RUN 1
#define SIMULATION_STOP 2

namespace Widget
{
    namespace Object
    {
        // struct for particles with initial configs
        typedef struct
        {
            bool active = false;
            float life = 0;
            glm::vec3 offset = glm::vec3(0, 0, 0);
            glm::vec3 velocity = glm::vec3(0, 0, 0);
        }Particles;

        // basic billboard unit: position.x, position.y, position.z, texture.x, texture.y
        static const GLfloat vertex_buffer_data[] = {
            -0.1f, 0.1f, 0.0f, 0.0f, 1.0f,
            0.1f, -0.1f, 0.0f, 1.0f, 0.0f,
            -0.1f, -0.1f, 0.0f, 0.0f, 0.0f,
            -0.1f, 0.1f, 0.0f, 0.0f, 1.0f,
            0.1f, -0.1f, 0.0f, 1.0f, 0.0f,
            0.1f, 0.1f, 0.0f, 1.0f, 1.0f
        };

        static double perlin_grid[101][101][101];
        static glm::vec3 acceleration_grid[100][100][100];

        class Smoke
        {
        public:

            Smoke();
            ~Smoke();

            // initialize particle system and vertex preparation
            void init();
            // update and display particle system
            void render(Camera camera, int status);
            glm::vec3 get_position();

            Particles particles[MAX_PARTICLES];

        private:

            // record the number of times render function is invoked
            int render_count_ = 0;                          

            // position_ is the pos of particles, not each particle
            glm::vec3 position_ = glm::vec3(0, 0, 0);

            // used to record each particle's position
            float particles_position_[MAX_PARTICLES * 3];

            GLuint vao_smoke_;
            GLuint vertex_buffer_;
            GLuint particle_position_buffer_;
            GLuint texture_;
            GLuint program_smoke_;

            Shader::ShaderObject shader_smoke_;
        };
    }
}

#endif // !SMOKE_H
