#ifndef _SHADER_
#define _SHADER_

//#define STB_IMAGE_IMPLEMENTATION
//#include <myTools/stb_image.h>

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

class Shader
{
public:
	Shader(const std::string vertex_shader_file, const std::string fragment_shader_file) {
		vertexShaderFile = vertex_shader_file;
		fragmentShaderFile = fragment_shader_file;
	}

	void compile() {
		//compile vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		std::string vertex_shader_code;
		std::ifstream vertex_shader_stream(vertexShaderFile, std::ios::in);
		if (vertex_shader_stream.is_open())
		{
			std::string line;
			while (getline(vertex_shader_stream, line))
				vertex_shader_code += "\n" + line;
			vertex_shader_stream.close();
		}
		else
		{
			std::cerr << "Cannot open vertex shader file" << vertexShaderFile << std::endl;
			exit(EXIT_FAILURE);
		}
		char const* vertexShaderPtr = vertex_shader_code.c_str();
		glShaderSource(vertexShader, 1, &vertexShaderPtr, NULL);
		glCompileShader(vertexShader);

		//error dialog
		int success;
		char logInfo[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, logInfo);
			std::cout << "ERROR: vertextShader:: COMPILE_FAIL" << logInfo << std::endl;
		}
		//compile fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragment_shader_code;
		std::ifstream fragment_shader_stream(fragmentShaderFile, std::ios::in);
		if (fragment_shader_stream.is_open())
		{
			std::string line;
			while (getline(fragment_shader_stream, line))
				fragment_shader_code += "\n" + line;
			fragment_shader_stream.close();
		}
		else
		{
			std::cerr << "Cannot open vertex shader file" << fragmentShaderFile << std::endl;
			exit(EXIT_FAILURE);
		}
		char const* fragmentShaderPtr = fragment_shader_code.c_str();
		glShaderSource(fragmentShader, 1, &fragmentShaderPtr, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, logInfo);
			std::cout << "ERROR: fragmentShader:: COMPILE_FAIL" << logInfo << std::endl;
		}

		//shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, logInfo);
			std::cout << "ERROR: shaderProgram:: LINK_FAIL" << logInfo << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	//void textureCreate(const char* textureFile) {
	//	unsigned int texture;
	//	glGenTextures(1, &texture);
	//	glBindTexture(GL_TEXTURE_2D, texture);
	//	//set wrap/filter mode for binded texture object
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	//load and generate texture
	//	int width, height, nrChannels;
	//	stbi_set_flip_vertically_on_load(true);
	//	unsigned char *data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	//	if (data)
	//	{
	//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//		glGenerateMipmap(GL_TEXTURE_2D);
	//	}
	//	else
	//	{
	//		std::cout << "Failed to load texture" << std::endl;
	//	}
	//	stbi_image_free(data);
	//}

	GLuint getShaderProgram() {return shaderProgram;}

private:
	std::string vertexShaderFile;
	std::string fragmentShaderFile;
	GLuint shaderProgram;
};

#endif