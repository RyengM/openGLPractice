#include <GL/glew.h>
#include <camera/Camera.h>
#include <Shader/ShaderObject.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Quad.h"


Quad::Quad()
{
    camera = Camera(id);
    //bind a camera and initialize it
}

void Quad::build_render_config()
{
    //auto gl_func = QOpenGLContext::currentContext()->extraFunctions();

    //gl_func->glGenVertexArrays(1, &vao_);
    //gl_func->glGenBuffers(1, &vbo_);

    //gl_func->glBindVertexArray(vao_);
    //gl_func->glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    //gl_func->glBufferData(
    //    GL_ARRAY_BUFFER, config.mesh_object.buffer.size() * sizeof(float),
    //    static_cast<void*>(config.mesh_object.buffer.data()), GL_STATIC_DRAW);

    //// vertices
    //gl_func->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)nullptr);
    //gl_func->glEnableVertexAttribArray(0);

    //// normals
    //gl_func->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    //gl_func->glEnableVertexAttribArray(1);

    //// colors
    //gl_func->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
    //gl_func->glEnableVertexAttribArray(2);

    //build(
    //    "resources/shaders/object_shader.vert",
    //    "resources/shaders/object_shader.frag");

    //gl_func->glBindBuffer(GL_ARRAY_BUFFER, 0);
    //gl_func->glBindVertexArray(0);
}