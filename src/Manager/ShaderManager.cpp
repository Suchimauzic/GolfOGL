#include "Manager/ShaderManager.hpp"

std::vector<Shader> ShaderManager::shaderList = {};

void ShaderManager::loadShader
(
    const char* vertexPath,
    const char* fragmentPath,
    const std::string& shaderName
)
{
    Shader shader(vertexPath, fragmentPath, shaderName);
    shaderList.push_back(shader);
}

Shader& ShaderManager::getShader(const std::string& shaderName)
{
    for (Shader& shader : shaderList)
    {
        if (shader.getName() == shaderName)
        {
            return shader;
        }
    }
}