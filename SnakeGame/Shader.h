#pragma once
#include <glad/glad.h>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setFloat(const std::string& name, float value) const;
    void setInt(const std::string& name, int value) const;
};
