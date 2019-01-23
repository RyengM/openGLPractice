#include <QOpenGLContext.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <headFiles/Quad.h>
#include <headFiles/Camera.h>

Quad::Quad()
{
    position = glm::vec3(0.f, 0.f, 0.f);
}

Quad::~Quad()
{

}

void Quad::build_render_config()
{
    // set current context and start up glfunctions
    QOpenGLExtraFunctions *glf = QOpenGLContext::currentContext()->extraFunctions();
    // bind vao, vbo and transport the necessary parameters to shader
    glf->glGenVertexArrays(1, &vao_);
    glf->glGenBuffers(1, &vbo_);

    glf->glBindVertexArray(vao_);
    glf->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    vertexInfo = shaderObject_.getVertexInfo("../assets/shaders/quad.txt");
    int vertexSize = shaderObject_.get_vertex_size();
    glf->glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertexInfo, GL_STATIC_DRAW);

    // vertices
    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glf->glEnableVertexAttribArray(0);

    shaderObject_.build("../assets/shaders/quad.vert", "../assets/shaders/quad.frag");
    shader_program_ = shaderObject_.get_shader_program();

    shaderObject_.use();

    // unbind
    glf->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glf->glBindVertexArray(0);
}

void Quad::render(Camera camera)
{
    shaderObject_.use();

    // MVP transform
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    model = glm::rotate(model, glm::radians(-5.f * render_count_++), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::lookAt(camera.get_view_offset() + position, position, glm::vec3(0.f, 0.f, -1.f));
    projection = glm::perspective(glm::radians(camera.get_fovy()), 1920.f / 1080.f, 0.1f, 1000.0f);

    glm::mat4 mvp = projection * view * model;

    shaderObject_.set_mat4("mvp", mvp);

    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    f->glBindVertexArray(vao_);
    f->glDrawArrays(GL_TRIANGLES, 0, shaderObject_.get_vertex_size()/3);
}

glm::vec3 Quad::get_position()
{
    return position;
}
