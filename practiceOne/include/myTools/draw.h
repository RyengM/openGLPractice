#ifndef _DRAW_H_
#define _DRAW_H_

#include <glad/glad.h>
#include <string>
#include <myTools/camera.h>

class drawMethod {
public:
	drawMethod(const std::string vertex_shader_file, const std::string fragment_shader_file);
	void textureCreate(const char* textureFile);
	void render();
	void drawTriangleHandler();
	void useGLDraw(Camera camera);

private:
	std::string vertexShaderFile;
	std::string fragmentShaderFile;
	GLuint shaderProgram;
	GLuint VAO;
};

#endif
