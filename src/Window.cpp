#include "Window.hpp"

GLFWwindow* Window::window = nullptr;

short Window::init(int width, int height, const char* title)
{
    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    // Checking if the window was created correctly
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Checking if GLAD is working correctly
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
}

void Window::deinit()
{
    glfwTerminate();
}

int Window::isShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}