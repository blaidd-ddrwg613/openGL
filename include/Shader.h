#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // Program ID
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void use();

    // Utility functions
    void setBool(const std::string& name , bool value) const;
    void setInt(const std::string& name , int value) const;
    void setFloat(const std::string& name , float value) const;
    void setVec3(const std::string& name , float r, float g, float b) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};