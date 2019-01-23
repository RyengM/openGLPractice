#include <headFiles/Smoke.h>
#include <random>

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

    // used for saving initial vertex data
    float vertexInfo[MAX_PARTICLES * 3];
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        vertexInfo[i] = particles[i / 3].position.x;
        vertexInfo[i + 1] = particles[i / 3].position.y;
        vertexInfo[i + 2] = particles[i / 3].position.z;
    }

    glf->glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * sizeof(float) * 3, vertexInfo, GL_STATIC_DRAW);

    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glf->glEnableVertexAttribArray(0);

    shaderObject_.build("../assets/shaders/smoke.vert", "../assets/shaders/smoke.frag");
    shader_program_ = shaderObject_.get_shader_program();

    shaderObject_.use();

    // unbind
    glf->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glf->glBindVertexArray(0);
}

void Smoke::render()
{
    // update particle condition
    // emit a particle per 20ms
    if (render_count_ < MAX_PARTICLES)
        particles[render_count_++].active = true;
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].active == true)
        {
            srand(time(0));
            particles[i].velocity.x = rand() % 100 / (double)100;
            particles[i].velocity.y = rand() % 100 / (double)100;
            particles[i].velocity.z = rand() % 100 / (double)100;

            particles[i].position += particles[i].velocity;
        }
    }

    // display particle system


}