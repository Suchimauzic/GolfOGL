#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.hpp"

int main()
{
    if (Window::init(1280, 720, "GolfGame") != 0)
        return -1;

    while (!Window::isShouldClose())
    {
        Window::swapBuffers();
        Window::pollEvents();
    }

    Window::deinit();
    return 0;
}