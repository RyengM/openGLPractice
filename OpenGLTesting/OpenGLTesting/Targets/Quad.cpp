#include <camera/Camera.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Quad.h"


Quad::Quad()
{
    camera = Camera(id);
    //bind a camera and initialize it
    build_render_config();
}

void Quad::build_render_config()
{
    //glf = QOpenGLContext::currentContext()->versionFunctions<QOpenGLExtraFunctions>();

    //bind vao, vbo and transport the necessary parameters to shader
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    vertexInfo = quadObject.getVertexInfo("resources/shaders/quad.txt");
    glBufferData(GL_ARRAY_BUFFER, 5 * sizeof(float), vertexInfo, GL_STATIC_DRAW);

    // vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // texCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Quad::render()
{
    //MVP transform
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    // camera/view transformation
    float radius = 10.0f;

    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = camera.getViewMatrix();
    projection = glm::perspective(glm::radians(camera.zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model;

    quadObject.set_mat4("mvp", mvp);
}