#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Window
{
public:
    static int init(int width, int height, const char* title);
    static void deinit();
    
    static int isShouldClose();
    static void swapBuffers();
    static void pollEvents();

private:
    static GLFWwindow* window;
};

#endif