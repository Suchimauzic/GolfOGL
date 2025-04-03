#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Window
{
public:
    static short init(int width, int height, const char* title);
    static void deinit();
    
    static int isShouldClose();
    static void swapBuffers();
    static void pollEvents();

    static void proccessInput();

private:
    static GLFWwindow* window;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif