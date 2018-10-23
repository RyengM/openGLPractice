#ifndef _SHADER_GLEW_HPP_
#define _SHADER_GLEW_HPP_

#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

namespace UniSim
{
	namespace GPU
	{
		class ShaderGLEW
		{
		public:
			ShaderGLEW(const std::string& vertex_shader_file, const std::string& fragment_shader_file)
			{
				GLint success;
				char info_log[512];

				/// vertex shader
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
					std::cerr << "Cannot open vertex shader file" << vertex_shader_file << std::endl;
					exit(EXIT_FAILURE);
				}

				char const* vertex_source_ptr = vertex_shader_code.c_str();
				glShaderSource(vertex_shader, 1, &vertex_source_ptr, nullptr);
				glCompileShader(vertex_shader);
				glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
				if (success == 0)
				{
					glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
					std::cerr << "Vertex shader compile failed, " << info_log << std::endl;
				}

				/// fragment shader
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
					std::cerr << "Cannot open fragment shader file" << fragment_shader_file << std::endl;
					exit(EXIT_FAILURE);
				}

				char const* fragment_source_ptr = fragment_shader_code.c_str();
				glShaderSource(fragment_shader, 1, &fragment_source_ptr, nullptr);
				glCompileShader(fragment_shader);
				glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
				if (success == 0)
				{
					glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
					std::cerr << "Fragment shader compile failed, " << info_log << std::endl;
				}

				/// link program
				this->shader_program_ = glCreateProgram();
				glAttachShader(shader_program_, vertex_shader);
				glAttachShader(shader_program_, fragment_shader);
				glLinkProgram(shader_program_);
				glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
				if (success == 0)
				{
					glGetProgramInfoLog(shader_program_, 512, nullptr, info_log);
					std::cerr << "Shader program linking failed, " << info_log << std::endl;
				}
				glDeleteShader(vertex_shader);
				glDeleteShader(fragment_shader);
			}

			void use() const
			{
				glUseProgram(this->shader_program_);
			}

			GLuint get_shader_program() const
			{
				return this->shader_program_;
			}

		private:
			GLuint shader_program_;
		};
	}
}

#endif // _SHADER_GLEW_HPP_