#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.hpp"
#include "GameConfig.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include "Cube.hpp"

int main()
{
    short windowStatus = Window::init(1280, 720, "GolfGame");

    if (windowStatus != 0)
    {
        Window::deinit();
        return windowStatus;
    }
    
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");
    
    Cube* cube = new Cube();

    cube->setRotate(30.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
    cube->setSize(glm::vec3(8.0f, 0.0f, 8.0f));

    Cube* cube2 = new Cube();

    //cube2->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

    float currentFrame;
    while (!Window::isShouldClose())
    {
        // deltaTime
        currentFrame = static_cast<float>(glfwGetTime());
        Window::deltaTime = currentFrame - Window::lastFrame;
        Window::lastFrame = currentFrame;

        Window::proccessInput();

        glClearColor(0.6f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube->render(shader, GameConfig::width, GameConfig::height);

        cube2->setPosition(glm::vec3(0.0f, 0.0f, static_cast<float>(cos(glfwGetTime()) * Window::deltaTime * 4)));
        cube2->render(shader, GameConfig::width, GameConfig::height);

        Window::swapBuffers();
        Window::pollEvents();
    }

    Window::deinit();
    return 0;
}