#include "Core/Window.hpp"

#include <sstream>

// Variables

FirstScene* Window::firstScene = nullptr;

float Window::lastX = 0.0f;
float Window::lastY = 0.0f;


Window::Window(int width, int height, const char* title)
{
    // deltaTime variables
    deltaTime = 0.0f;
    lastFrame = 0.0f;

    codeStatus = 0;

    initWindow(width, height, title);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::loadScene(FirstScene* firstScene)
{
    this->firstScene = firstScene;
}

void Window::removeScene()
{
    delete firstScene;
}


// Window initialization function
void Window::initWindow(int width, int height, const char* title)
{
    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    // Checking if the window was created correctly
    if (window == nullptr)
    {
        Logger::printError("Failed to create GLFW window");
        codeStatus = -1;
        return;
    }

    glfwMakeContextCurrent(window);

    // Checking if GLAD is working correctly
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::printError("Failed to initialize GLAD");
        codeStatus = -2;
        return;
    }

    // GLFW info
    Logger::printInfo("----GLFW info----");
    Logger::printValue("GLFW version", glfwGetVersionString());


    // OpenGL info
    Logger::printInfo("\n----OpenGL info----");
    Logger::printValue("OpenGL Vendor", glGetString(GL_VENDOR));
    Logger::printValue("OpenGL Renderer", glGetString(GL_RENDERER));
    Logger::printValue("OpenGL Version", glGetString(GL_VERSION));

    Logger::printInfo("");


    // Callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Cursor mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enables
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glEnable(GL_MULTISAMPLE);

    // Culling face
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Initing static variables
    lastX = width / 2;
    lastY = height / 2;

    GameConfig::width = width;
    GameConfig::height = height;
}


// Loop methods

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

void Window::proccessInput()
{
    firstScene->processInput(window, deltaTime);
}

void Window::updateDeltaTime(float currentFrame)
{
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Window::render()
{
    Renderer::draw(&firstScene->getCamera());
}

void Window::update()
{
    Logger::printValue("FPS", 1.0f / deltaTime);
}

// Geters

int Window::getCodeStatus()
{
    return codeStatus;
}

float Window::getDeltaTime()
{
    return deltaTime;
}


// Callbacks

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::mouseCallback(GLFWwindow* window, double xPosMouse, double yPosMouse)
{
    float xPos = static_cast<float>(xPosMouse);
    float yPos = static_cast<float>(yPosMouse);

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    // camera->proccessMouseMovement(xOffset, yOffset);
    // firstScene->getCamera().proccessMouseMovement(xOffset, yOffset);
}

void Window::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    // camera->proccessMouseScroll(static_cast<float>(yOffset));
    firstScene->getCamera().proccessMouseScroll(static_cast<float>(yOffset));
}