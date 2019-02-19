#include <QOpenGLContext.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb_image.h>

#include <headFiles/Quad.h>
#include <headFiles/Camera.h>

using namespace Widget;
using namespace Object;

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
    glf->glGenVertexArrays(1, &vao_quad_);
    glf->glGenBuffers(1, &vertex_buffer_);

    glf->glBindVertexArray(vao_quad_);
    glf->glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);

    vertexInfo = shader_quad_.getVertexInfo("../assets/shaders/quad.txt");
    int vertexSize = shader_quad_.get_vertex_size();
    glf->glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertexInfo, GL_STATIC_DRAW);

    // vertices
    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glf->glEnableVertexAttribArray(0);
    // texture vertices
    glf->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glf->glEnableVertexAttribArray(1);

    // load and create texture
    glf->glGenTextures(1, &texture_);
    glf->glBindTexture(GL_TEXTURE_2D, texture_);
    // Set our texture parameters
    glf->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glf->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glf->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glf->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load texture
    int x, y, n;
    unsigned char* image_data = stbi_load("../assets/textures/smoke.png", &x, &y, &n, STBI_rgb_alpha);
    if (!image_data)
    {
        std::cout << "failed to load texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    glf->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glf->glGenerateMipmap(GL_TEXTURE_2D);
    glf->glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image_data);

    shader_quad_.build("../assets/shaders/quad.vert", "../assets/shaders/quad.frag");
    program_quad_ = shader_quad_.get_shader_program();

    shader_quad_.use();

    // unbind
    glf->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glf->glBindVertexArray(0);
}

void Quad::render(Camera camera)
{
    QOpenGLExtraFunctions *glf = QOpenGLContext::currentContext()->extraFunctions();

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    shader_quad_.use();

    // active texture
    glf->glActiveTexture(GL_TEXTURE0);
    glf->glBindTexture(GL_TEXTURE_2D, texture_);
    glf->glUniform1i(glf->glGetUniformLocation(program_quad_, "texture_"), 0);

    // MVP transform
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    model = glm::rotate(model, glm::radians(-5.f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::lookAt(camera.get_view_offset() + position, position, glm::vec3(0.f, 0.f, -1.f));
    projection = glm::perspective(glm::radians(camera.get_fovy()), 1920.f / 1080.f, 0.1f, 1000.0f);

    glm::mat4 mvp = projection * view * model;

    shader_quad_.set_mat4("mvp", mvp);

    glf->glBindVertexArray(vao_quad_);
    glf->glDrawArrays(GL_TRIANGLES, 0, shader_quad_.get_vertex_size()/3);

    glPopAttrib();
}

glm::vec3 Quad::get_position()
{
    return position;
}
