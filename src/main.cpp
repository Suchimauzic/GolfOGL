#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.hpp"
#include "GameConfig.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

int main()
{
    short windowStatus = Window::init(1280, 720, "GolfGame");

    if (windowStatus != 0)
    {
        Window::deinit();
        return windowStatus;
    }
    
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
    
    float currentFrame;
    while (!Window::isShouldClose())
    {
        // deltaTime
        currentFrame = static_cast<float>(glfwGetTime());
        Window::deltaTime = currentFrame - Window::lastFrame;
        Window::lastFrame = currentFrame;

        Window::proccessInput();

        glClearColor(0.6f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(Window::camera->zoom), static_cast<float>(GameConfig::width) / static_cast<float>(GameConfig::height), 1.0f, 100.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = Window::camera->getViewMatrix();
        shader.setMat4("view", view);

        glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        Window::swapBuffers();
        Window::pollEvents();
    }

    Window::deinit();
    return 0;
}