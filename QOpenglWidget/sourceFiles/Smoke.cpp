#include <headFiles/Smoke.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <iostream>

Smoke::Smoke()
{

}

Smoke::~Smoke()
{

}

void Smoke::init()
{
    // set current context and start up glfunctions
    QOpenGLExtraFunctions *glf = QOpenGLContext::currentContext()->extraFunctions();

    glf->glGenVertexArrays(1, &vao_);
    glf->glGenBuffers(1, &vbo_);
    
    glf->glBindVertexArray(vao_);
    glf->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glf->glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW);

    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glf->glEnableVertexAttribArray(0);
    
    // launch cuda
    //init_cuda();

    shaderObject_.build("../assets/shaders/smoke.vert", "../assets/shaders/smoke.frag");
    shader_program_ = shaderObject_.get_shader_program();

    shaderObject_.use();

    // unbind
    glf->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glf->glBindVertexArray(0);
}

void Smoke::render(Camera camera)
{
    // update particle condition
    // emit a particle per 20ms
    if (render_count_ < MAX_PARTICLES)
        particles[render_count_++].active = true;

    //update_cuda();

    // display particle system
    shaderObject_.use();

    // MVP transform
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::lookAt(camera.get_view_offset() + position_, position_, glm::vec3(0.f, 0.f, -1.f));
    projection = glm::perspective(glm::radians(camera.get_fovy()), 1920.f / 1080.f, 0.1f, 1000.0f);

    glm::mat4 mvp = projection * view * model;

    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    shaderObject_.set_vec3("offset", particles->offset);
    shaderObject_.set_mat4("mvp", mvp);

    f->glBindVertexArray(vao_);
    f->glDrawArrays(GL_POINTS, 0, render_count_);

}

glm::vec3 Smoke::get_position()
{
    return position_;
}