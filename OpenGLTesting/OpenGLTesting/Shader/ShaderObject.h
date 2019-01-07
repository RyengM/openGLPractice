#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include <string>
#include <glm/glm.hpp>

#include <QOpenGLExtraFunctions>

class ShaderObject : protected QOpenGLExtraFunctions
{
public:
    ShaderObject() = default;
    ShaderObject(const std::string& vertex_shader_file,
        const std::string& fragment_shader_file);

    float* getVertexInfo(const std::string& filename);

    void build(const std::string& vertex_shader_file,
        const std::string& fragment_shader_file);

    void set_bool(const std::string& name, bool value);
    void set_int(const std::string& name, int value);
    void set_float(const std::string& name, float value);

    void set_vec2(const std::string& name, const glm::vec2& value);
    void set_vec2(const std::string& name, float x, float y);

    void set_vec3(const std::string& name, const glm::vec3& value);
    void set_vec3(const std::string& name, float x, float y, float z);

    void set_vec4(const std::string& name, const glm::vec4& value);
    void set_vec4(const std::string& name, float x, float y, float z, float w);

    void set_mat2(const std::string& name, const glm::mat2& value);
    void set_mat3(const std::string& name, const glm::mat3& value);
    void set_mat4(const std::string& name, const glm::mat4& value);

    void use();
    void unuse();
    void release();

    GLuint get_shader_program() const;

private:
    GLuint program_ = 0u;
};


#endif
