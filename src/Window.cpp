#include "Window.hpp"

// Variables

Camera* Window::camera = nullptr;

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
    delete camera;
    glfwTerminate();
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enables
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Initing static variables
    lastX = width / 2;
    lastY = height / 2;

    GameConfig::width = width;
    GameConfig::height = height;

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->proccessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->proccessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->proccessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->proccessKeyboard(CameraMovement::RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void Window::updateDeltaTime(float currentFrame)
{
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
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

Camera* Window::getCamera()
{
    return camera;
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

    camera->proccessMouseMovement(xOffset, yOffset);
}

void Window::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera->proccessMouseScroll(static_cast<float>(yOffset));
}