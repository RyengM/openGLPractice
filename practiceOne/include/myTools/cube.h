#ifndef _CUBE_H_
#define _CUBE_H_

#include <glad/glad.h>
#include <string>
#include <myTools/camera.h>

class drawCubeMethod {
public:
	drawCubeMethod() {};
	void drawCubeHandler();
	void useGLDraw(Camera camera);

private:
	GLuint shaderProgram;
	GLuint VAO;
};

#endif
