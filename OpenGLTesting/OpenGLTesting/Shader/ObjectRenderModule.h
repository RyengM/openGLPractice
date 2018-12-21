#ifndef OBJECT_RENDER_MODULE_H
#define OBJECT_RENDER_MODULE_H

#include "ShaderObject.h"

    class RenderConfig
    {
    public:
        // 3D visible model
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint tex = 0;
        ShaderObject shader;
    };

    class ObjectRenderModule : protected QOpenGLExtraFunctions
    {
        static std::map<std::string, RenderConfig> configs_;

    public:
        static void initialize();

        static void render_visible(
            RenderConfig& render_config,
            const glm::vec3& camera_position,
            const glm::vec3& target_position,
            const glm::mat4& model,
            const glm::mat4& view,
            const glm::mat4& projection);

    private:
        static void initialize_config();

        static void build_render_config(RenderConfig& config);
    };


#endif 
