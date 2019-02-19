#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <headFiles/ShaderObject.h>

using namespace Widget;
using namespace Shader;

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
        std::cout << "cannot open vertex shader file " << vertex_shader_file << std::endl;
        exit(EXIT_FAILURE);
    }
    char const* vertex_source_ptr = vertex_shader_code.c_str();
    glShaderSource(vertex_shader, 1, &vertex_source_ptr, nullptr);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cout << "vertex shader compilation failed, " << info_log << std::endl;
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
        std::cout << "cannot open fragment shader file " << vertex_shader_file << std::endl;
        exit(EXIT_FAILURE);
    }
    char const* fragment_source_ptr = fragment_shader_code.c_str();
    glShaderSource(fragment_shader, 1, &fragment_source_ptr, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cout << "fragment shader compilation failed, " << info_log << std::endl;
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
        std::cout << "program linking failed, " << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

float* ShaderObject::getVertexInfo(const std::string& filename)
{
    // index of vertex_value
    int i = 0;
    // initialize number of vertices
    vertex_size = 0;
    // current character
    char temp_c;
    std::vector<float> vertex;
    char vertex_value[6];
    std::ifstream vertex_stream(filename, std::ios::in);
    if (vertex_stream.is_open())
    {
        while (!vertex_stream.eof())
        {
            if (vertex_stream.good())
            {
                vertex_stream >> temp_c;
                if (temp_c == 'f')
                {
                    vertex_value[i] = '\0';
                    i = 0;
                    vertex.push_back(atof(vertex_value));
                    vertex_size++;
                }
                else
                    vertex_value[i++] = temp_c;
            }
        }
    }
    else
    {
        std::cout << "cannot open vertex file {}" << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    // the value of result_buffer have to be checked
    float *result_buffer = new float[vertex.size() - 1];
    if (!vertex.empty())
        memcpy(result_buffer, &vertex[0], (vertex.size()-1) * sizeof(float));
    // there will be an extra 0.0f at the end of array, i don't know why yet, vertex.size()-1 is also influenced
    vertex_size--;
    return result_buffer;
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

int ShaderObject::get_vertex_size() const
{
    return this->vertex_size;
}