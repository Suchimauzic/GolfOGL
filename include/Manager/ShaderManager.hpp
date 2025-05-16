#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include "Core/Shader.hpp"
#include <string>

class ShaderManager
{
public:
    static void loadShader(const char* vertexPath, const char* fragmentPath, const std::string& shaderName);
    static Shader& getShader(const std::string& shaderName);

private:
    static std::vector<Shader> shaderList;
};

#endif