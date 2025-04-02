#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.hpp"
#include "Shader.hpp"

int main()
{
    short windowStatus = Window::init(800, 600, "GolfGame");

    if (windowStatus != 0)
        return windowStatus;
    
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");
    
    float vertices[] ={
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
    while (!Window::isShouldClose())
    {
        glClearColor(0.6f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        Window::swapBuffers();
        Window::pollEvents();
    }

    Window::deinit();
    return 0;
}