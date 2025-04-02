#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();

private:
    void checkCompileErrors(unsigned int shader, std::string type);
    void printLine();
};

#endif