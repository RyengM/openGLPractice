#include <myTools/wakeFlame.h>
#include <myTools/shader.h>
#include <myTools/cudaUtility.h>
#include <../assets/cuda/wakeFlame.cuh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cuda_gl_interop.h>
#include <iostream>

using namespace std;

void drawWakeFlameMethod::drawFlameHandler() {
	glEnable(GL_DEPTH_TEST);
	//set vertex parameter
	//float triangleVertices[] = {
	//	//x, y, z, s, t
	//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	//	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	//};

	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind VAO first
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * PARTICLE_NUM * sizeof(float), nullptr, GL_STATIC_DRAW);

	cudaGraphicsGLRegisterBuffer(&current_data.renderData.cuda_vbo_resource, VBO,
		cudaGraphicsMapFlagsWriteDiscard);
	//checkCudaErrors(cudaGraphicsMapResources(1, &current_data.renderData.cuda_vbo_resource, 0));

	//uchar4* devPtr;
	//size_t size;
	//cudaGraphicsResourceGetMappedPointer((void**)&devPtr, &size, current_data.renderData.cuda_vbo_resource);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	Shader cubeShader("../assets/shaders/wakeFlame.vert", "../assets/shaders/wakeFlame.frag");
	//cubeShader.textureCreate("../assets/textures/chartletOne.jpg");
	//cubeShader.textureCreate("../assets/textures/figure.jpg");
	cubeShader.compile();

	shaderProgram = cubeShader.getShaderProgram();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void drawWakeFlameMethod::useGLDraw(Camera camera) {

	//MVP transform
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection;

	// camera/view transformation
	float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

	glm::mat4 mvp = projection * view * model;

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, PARTICLE_NUM);
}

void drawWakeFlameMethod::initialize() {
	current_data.position = glm::vec3(0, 0, 0);
	current_data.angle = glm::vec3(0, 0, 0);

	drawWakeFlameMethod::drawFlameHandler();

	checkCudaErrors(cudaMalloc(reinterpret_cast<void**>(&current_data.renderData._flame),
		PARTICLE_NUM * sizeof(CurrentWakeFlameData)));

	initialize_flame(current_data.renderData._flame, current_data);
}

void drawWakeFlameMethod::update() {

	checkCudaErrors(cudaGraphicsMapResources(1, &current_data.renderData.cuda_vbo_resource, nullptr));
	size_t num_bytes;
	checkCudaErrors(cudaGraphicsResourceGetMappedPointer(
		reinterpret_cast<void**>(&current_data.renderData.verticesArray),
		&num_bytes, current_data.renderData.cuda_vbo_resource));
	assert(num_bytes == 9 * PARTICLE_NUM * sizeof(float));

	update_flame(current_data.renderData._flame, current_data, current_data.renderData.verticesArray);

	checkCudaErrors(cudaGraphicsUnmapResources(1, &current_data.renderData.cuda_vbo_resource, nullptr));
}