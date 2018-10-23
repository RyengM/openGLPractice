#ifndef _WAKE_FLAME_H_
#define _WAKE_FLAME_H_

#include <glad/glad.h>
#include <string>
#include <myTools/camera.h>
#include <myTools/currentWakeFlameData.h>
#include <glm/glm.hpp>

#define PARTICLE_NUM 1024

class drawWakeFlameMethod {
public:
	drawWakeFlameMethod() {};
	void drawFlameHandler();
	void useGLDraw(Camera camera);

	void initialize();
	void update();

private:
	GLuint shaderProgram;
	GLuint VAO;
	CurrentWakeFlameData::CurrentData current_data;
};

#endif
