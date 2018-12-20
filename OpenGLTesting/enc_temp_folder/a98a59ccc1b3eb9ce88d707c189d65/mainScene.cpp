#include <GL/glew.h>
#include <iostream>
#include <System/mainScene.h>
#include <Targets/Quad.h>

MainScene::MainScene(QOpenGLWidget *opengl_widget) : opengl_widget_(opengl_widget)
{
    std::cout << "initializing GLEW library..." <<std::endl;
    GLenum result = glewInit();
    if (result != GLEW_OK)
    {
        std::cout << "failed to initialize GLEW library, " << glewGetErrorString(result) << std::endl;
        assert(result == GLEW_OK);
    }
    std::cout << "initializing GLEW successfully, using GLEW " << glewGetString(GLEW_VERSION) <<std::endl;
}

MainScene::~MainScene()
{

}

void MainScene::initialize()
{

}

void MainScene::drawAxis()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.5, 0.0, -6.0);
    glLineWidth(2);
    int x = 0;
    int y = 0;
    int z = 0;
    glBegin(GL_LINES);
    {
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(x, y, z);
        glVertex3f(x + 100.f, y, z);
        glVertex3f(x + 100.f, y, z);
        glVertex3f(x + 100.f - 5.f, y + 5.f, z);
        glVertex3f(x + 100.f, y, z);
        glVertex3f(x + 100.f - 5.f, y - 5.f, z);

        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(x, y, z);
        glVertex3f(x, y + 40.f, z);
        glVertex3f(x, y + 40.f, z);
        glVertex3f(x - 5.f, y + 40.f - 5.f, z);
        glVertex3f(x, y + 40.f, z);
        glVertex3f(x + 5.f, y + 40.f - 5.f, z);
    }
    glEnd();
}

// we show target object in mainScene directly now, and it will be managed by a certain module afterwards
void MainScene::renderQuad()
{
    Quad quad = Quad();
    quad.build_render_config();
    quad.render();
}