#define STB_IMAGE_IMPLEMENTATION

#include <myTools/draw.h>
#include <myTools/stb_image.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>

using namespace std;

drawMethod::drawMethod(const std::string vertex_shader_file, const std::string fragment_shader_file) {
	vertexShaderFile = vertex_shader_file;
	fragmentShaderFile = fragment_shader_file;
}

void drawMethod::render() {
	//编译顶点着色器
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
	
	//错误日志
	int success;
	char logInfo[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, logInfo);
		cout << "ERROR: vertextShader:: COMPILE_FAIL" << logInfo << endl;
	}
	//编译片元着色器
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
		cout << "ERROR: fragmentShader:: COMPILE_FAIL" << logInfo << endl;
	}

	//着色器程序
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, logInfo);
		cout << "ERROR: shaderProgram:: LINK_FAIL" << logInfo << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void drawMethod::textureCreate(const char* textureFile) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载并生成纹理
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void drawMethod::drawTriangleHandler() {
	glEnable(GL_DEPTH_TEST);
	//定义顶点参数
	float triangleVertices[] = {
		//x, y, z, s, t
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//需要先绑定VAO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	textureCreate("../assets/textures/chartletOne.jpg");
	textureCreate("../assets/textures/figure.jpg");
	drawMethod::render();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void drawMethod::useGLDraw(Camera camera) {

	//MVP变换
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

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
}