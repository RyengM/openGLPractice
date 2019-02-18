#define STB_IMAGE_IMPLEMENTATION
#include <headFiles/Smoke.h>
#include <headFiles/perlin.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <iostream>
#include <cmath>
#include <stb_image.h>

Smoke::Smoke()
{
    
}

Smoke::~Smoke()
{

}

void Smoke::init()
{
    //////////// GL preparation
    // set current context and start up glfunctions
    QOpenGLExtraFunctions *glf = QOpenGLContext::currentContext()->extraFunctions();

    // bind vao first
    glf->glGenVertexArrays(1, &vao_);
    glf->glBindVertexArray(vao_);

    // set vbo contains 4 vertices of the particles
    glf->glGenBuffers(1, &vertex_buffer_);
    glf->glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glf->glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glf->glEnableVertexAttribArray(0);
    glf->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glf->glEnableVertexAttribArray(1);

    // set vbo for particle positions
    glf->glGenBuffers(1, &particle_position_buffer_);
    glf->glBindBuffer(GL_ARRAY_BUFFER, particle_position_buffer_);
    glf->glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW);
    glf->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glf->glEnableVertexAttribArray(2);
    
    // tell OPENGL features and grid of instances
    glf->glVertexAttribDivisor(0, 0);   // always reuse the 4 same vertices -> 0
    glf->glVertexAttribDivisor(1, 0);
    glf->glVertexAttribDivisor(2, 1);   // positions: one per quad -> 1

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
    
    // build shader
    shaderObject_.build("../assets/shaders/smoke.vert", "../assets/shaders/smoke.frag");
    shader_program_ = shaderObject_.get_shader_program();

    shaderObject_.use();

    // unbind
    glf->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glf->glBindVertexArray(0);

    //////////// create perlin_noise-based pressure net
    Perlin myPerlin = Perlin();
    // calculate each grid's perlin value
    for (double i = 0; i < 101; i++)
        for (double j = 0; j < 101; j++)
            for (double k = 0; k < 101; k++)
                perlin_grid[(int)i][(int)j][(int)k] = myPerlin.perlin(i + 0.5, j + 0.5, k + 0.5);
    // calculate each grid's acceleration
    for (int i = 1; i < 100; i++)
        for (int j = 1; j < 100; j++)
            for (int k = 1; k < 100; k++)
            {
                if (perlin_grid[i][j][k] - perlin_grid[i + 1][j][k] > perlin_grid[i][j][k] - perlin_grid[i - 1][j][k])
                    acceleration_grid[i][j][k].x = (perlin_grid[i][j][k] - perlin_grid[i + 1][j][k]);
                else 
                    acceleration_grid[i][j][k].x = (perlin_grid[i - 1][j][k] - perlin_grid[i][j][k]);
                if (perlin_grid[i][j][k] - perlin_grid[i][j + 1][k] > perlin_grid[i][j][k] - perlin_grid[i][j - 1][k])
                    acceleration_grid[i][j][k].y = (perlin_grid[i][j][k] - perlin_grid[i][j + 1][k]);
                else 
                    acceleration_grid[i][j][k].y = (perlin_grid[i][j - 1][k] - perlin_grid[i][j][k]);
                if (perlin_grid[i][j][k] - perlin_grid[i][j][k + 1] > perlin_grid[i][j][k] - perlin_grid[i][j][k - 1])
                    acceleration_grid[i][j][k].z = (perlin_grid[i][j][k] - perlin_grid[i][j][k + 1]);
                else
                    acceleration_grid[i][j][k].z = (perlin_grid[i][j][k - 1] - perlin_grid[i][j][k]);
            }
    // set initial speed for each particle
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        double random = double(qrand() % 1000);
        particles[i].velocity = glm::vec3(random, 0, 0);
    }
}

void Smoke::render(Camera camera, int status)
{
    QOpenGLExtraFunctions *glf = QOpenGLContext::currentContext()->extraFunctions();

    // update particle condition
    if (status == SIMULATION_RUN) {
        // emit a particle per 20ms
        if (render_count_ < MAX_PARTICLES)
            particles[render_count_++].active = true;
        // update particle position
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (particles[i].active)
            {
                particles[i].velocity += acceleration_grid[(int)(abs(particles[i].offset.x) * 100)%99 + 1][(int)(abs(particles[i].offset.y) * 100)%99 +1][(int)(abs(particles[i].offset.z) * 100)%99 +1];
                particles[i].velocity = normalize(particles[i].velocity);
                particles[i].offset += particles[i].velocity / glm::vec3(30,30,30);
                if (sqrt(pow(particles[i].offset.x, 2) + pow(particles[i].offset.y, 2) + pow(particles[i].offset.z, 2)) > 20)
                {
                    particles[i].active = false;
                    particles[i].offset = glm::vec3(0, 0, 0);
                    double random = double(qrand() % 1000);
                    particles[i].velocity = glm::vec3(random, 0, 0);
                }
            }
            else
            {
                if (render_count_ > i)
                    particles[i].active = true;
            }
        }
        // record particle offset buffer
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            particles_position_[i * 3] = particles[i].offset.x;
            particles_position_[i * 3 + 1] = particles[i].offset.y;
            particles_position_[i * 3 + 2] = particles[i].offset.z;
        }

        // update position_buffer infomation
        glf->glBindBuffer(GL_ARRAY_BUFFER, particle_position_buffer_);
        glf->glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * sizeof(float) * 3, particles_position_, GL_DYNAMIC_DRAW);

        // active texture
        glf->glActiveTexture(GL_TEXTURE0);
        glf->glBindTexture(GL_TEXTURE_2D, texture_);
        glf->glUniform1i(glf->glGetUniformLocation(shader_program_, "our_texture"), 0);
    }

    // display particle system
    shaderObject_.use();

    // MVP transform
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    model = glm::rotate(model, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::lookAt(camera.get_view_offset() + position_, position_, glm::vec3(0.f, 0.f, -1.f));
    projection = glm::perspective(glm::radians(camera.get_fovy()), 1920.f / 1080.f, 0.1f, 1000.0f);

    glm::mat4 mvp = projection * view * model;

    // transfer camera data to shader
    glm::vec3 unit_offset = camera.get_view_offset() / camera.get_view_distance();
    glm::vec3 camera_up = glm::vec3(0, 1, 0);   // it is a temp camera_up
    glm::vec3 camera_right = normalize(glm::cross(-unit_offset, camera_up));
    camera_up = normalize(glm::cross(camera_right, -unit_offset));

    shaderObject_.set_mat4("mvp", mvp);
    shaderObject_.set_vec3("camera_up", camera_up);
    shaderObject_.set_vec3("camera_right", camera_right);

    glf->glBindVertexArray(vao_);
    glf->glDrawArraysInstanced(GL_TRIANGLES, 0, 6, render_count_);
    glf->glBindVertexArray(0);
}

glm::vec3 Smoke::get_position()
{
    return position_;
}