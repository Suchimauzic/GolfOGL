#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "Camera.hpp"
#include "GameConfig.hpp"
#include "Core/Logger.hpp"

#include "FirstScene.hpp"


class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();
    
    // Loop methods
    int isShouldClose();
    void swapBuffers();
    void pollEvents();

    void proccessInput();

    void updateDeltaTime(float currentFrame);
    void render();
    void update();

    // Getters
    int getCodeStatus();
    float getDeltaTime();

private:
    // First level
    static FirstScene* firstScene;

    // Window attributes
    GLFWwindow* window;
    int codeStatus;

    // Timing
    float deltaTime;
    float lastFrame;
    
    // Camera
    static float lastX;
    static float lastY;

    void initWindow(int width, int height, const char* title);

    // Callbacks
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xPosMouse, double yPosMouse);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

#endif