#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <QOpenGLExtraFunctions>
#include <headFiles/ShaderObject.h>
#include <headFiles/Camera.h>

// abstract class, used for all objects, provide some basic parameteres

class Object : protected QOpenGLExtraFunctions
{
public:

    Object();
    ~Object();

    void reset();                                   // reset object condition

protected:

    int id_;                                        // object's identity
    int render_count_ = 0;                          // record the number of times render function is invoked

    ShaderObject shaderObject_ = ShaderObject();
    GLuint shader_program_;
    GLuint vao_;
    GLuint vbo_;

};

#endif