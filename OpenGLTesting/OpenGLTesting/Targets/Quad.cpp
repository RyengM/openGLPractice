#include <camera/Camera.h>

#include <QOpenGLContext.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Quad.h"


Quad::Quad()
{
    camera = Camera(id);
    // set current context and start up glfunctions
    glf = QOpenGLContext::currentContext()->extraFunctions();
    // bind a camera and initialize it
    build_render_config();
}

Quad::~Quad()
{
    delete vertexInfo;
}

void Quad::build_render_config()
{
    // bind vao, vbo and transport the necessary parameters to shader
    glf->glGenVertexArrays(1, &vao_);
    glf->glGenBuffers(1, &vbo_);

    glf->glBindVertexArray(vao_);
    glf->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    vertexInfo = quadObject.getVertexInfo("../assets/shaders/quad.txt");
    glf->glBufferData(GL_ARRAY_BUFFER, 5 * sizeof(float), vertexInfo, GL_STATIC_DRAW);

    // vertices
    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glf->glEnableVertexAttribArray(0);

    // texCoord
    glf->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glf->glEnableVertexAttribArray(1);

    quadObject.build("../assets/shaders/quad.vert", "../assets/shaders/quad.frag");

    // unbind
    glf->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glf->glBindVertexArray(0);
}

void Quad::render()
{
    // MVP transform
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    // camera/view transformation
    float radius = 10.0f;

    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = camera.getViewMatrix(position);
    projection = glm::perspective(glm::radians(camera.zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model;

    quadObject.set_mat4("mvp", mvp);
}