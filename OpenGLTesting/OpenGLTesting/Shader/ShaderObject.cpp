#include "ShaderObject.h"
#include "Plugin/Logger.hpp"

#include <fstream>
#include <sstream>

ShaderObject::ShaderObject(const std::string& vertex_shader_file, const std::string& fragment_shader_file)
{
    build(vertex_shader_file, fragment_shader_file);
}

void ShaderObject::build(const std::string& vertex_shader_file, const std::string& fragment_shader_file)
{
    initializeOpenGLFunctions();

    GLint success;
    char info_log[512];

    if (program_ != 0)
        glDeleteProgram(program_);

    // vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertex_shader_code;
    std::ifstream vertex_shader_stream(vertex_shader_file, std::ios::in);
    if (vertex_shader_stream.is_open())
    {
        std::string line;
        while (getline(vertex_shader_stream, line))
            vertex_shader_code += "\n" + line;
        vertex_shader_stream.close();
    }
    else
    {
        Logger::error("cannot open vertex shader file {}", vertex_shader_file);
        exit(EXIT_FAILURE);
    }
    char const* vertex_source_ptr = vertex_shader_code.c_str();
    glShaderSource(vertex_shader, 1, &vertex_source_ptr, nullptr);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        Logger::error("vertex shader compilation failed, {}", info_log);
    }

    // fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragment_shader_code;
    std::ifstream fragment_shader_stream(fragment_shader_file, std::ios::in);
    if (fragment_shader_stream.is_open())
    {
        std::string line;
        while (getline(fragment_shader_stream, line))
            fragment_shader_code += "\n" + line;
        fragment_shader_stream.close();
    }
    else
    {
        Logger::error("cannot open fragment shader file {}", vertex_shader_file);
        exit(EXIT_FAILURE);
    }
    char const* fragment_source_ptr = fragment_shader_code.c_str();
    glShaderSource(fragment_shader, 1, &fragment_source_ptr, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        Logger::error("fragment shader compilation failed, {}", info_log);
    }

    // link program
    this->program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
    glLinkProgram(program_);

    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(program_, 512, nullptr, info_log);
        Logger::error("program linking failed, {}", info_log);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderObject::set_bool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(program_, name.c_str()), int(value));
}

void ShaderObject::set_int(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(program_, name.c_str()), value);
}

void ShaderObject::set_float(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
}

void ShaderObject::set_vec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}

void ShaderObject::set_vec2(const std::string& name, float x, float y)
{
    glUniform2f(glGetUniformLocation(program_, name.c_str()), x, y);
}

void ShaderObject::set_vec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}

void ShaderObject::set_vec3(const std::string& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(program_, name.c_str()), x, y, z);
}

void ShaderObject::set_vec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}

void ShaderObject::set_vec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(program_, name.c_str()), x, y, z, w);
}

void ShaderObject::set_mat2(const std::string& name, const glm::mat2& value)
{
    glUniformMatrix2fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderObject::set_mat3(const std::string& name, const glm::mat3& value)
{
    glUniformMatrix3fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderObject::set_mat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderObject::use()
{
    glUseProgram(this->program_);
}

void ShaderObject::unuse()
{
    glUseProgram(0);
}

void ShaderObject::release()
{
    glDeleteProgram(program_);
}

GLuint ShaderObject::get_shader_program() const
{
    return this->program_;
}
