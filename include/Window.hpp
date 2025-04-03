#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "Camera.hpp"

class Window
{
public:
    // Timing
    static float deltaTime;
    static float lastFrame;

    static Camera* camera;

    static short init(int width, int height, const char* title);
    static void deinit();
    
    static int isShouldClose();
    static void swapBuffers();
    static void pollEvents();

    static void proccessInput();

private:
    static GLFWwindow* window;
    
    // Camera
    static float lastX;
    static float lastY;

    // Callbacks
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xPosMouse, double yPosMouse);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

#endif