#ifndef _QUAD_
#define _QUAD_

#include <headFiles/Camera.h>
#include <headFiles/ShaderObject.h>

namespace Widget
{
    namespace Object
    {
        class Quad
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

            GLuint vao_quad_;
            GLuint vertex_buffer_;
            GLuint texture_;
            GLuint program_quad_;

            Shader::ShaderObject shader_quad_;
        };
    }
}

#endif
