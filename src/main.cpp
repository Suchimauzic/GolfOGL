#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "Window.hpp"
#include "GameConfig.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include "Cube.hpp"
#include "Sphere.hpp"

int main()
{
    short windowStatus = Window::init(1920, 1080, "GolfGame");

    if (windowStatus != 0)
    {
        Window::deinit();
        return windowStatus;
    }
    
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    Sphere* sphere = new Sphere();
    Cube* cube = new Cube();

    float currentFrame;

    while (!Window::isShouldClose())
    {
        // deltaTime
        currentFrame = static_cast<float>(glfwGetTime());
        Window::deltaTime = currentFrame - Window::lastFrame;
        Window::lastFrame = currentFrame;

        Window::proccessInput();
        Window::pollEvents();

        glClearColor(0.6f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        sphere->render(shader, GameConfig::width, GameConfig::height);
        cube->render(shader, GameConfig::width, GameConfig::height);
        Window::swapBuffers();
    }

    delete sphere;
    delete cube;
    Window::deinit();
    return 0;
}