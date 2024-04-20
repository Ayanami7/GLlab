#pragma once
#include<glad/glad.h>
#include <fstream>
#include <sstream>

#include "common.h"

class Shader
{
public:
    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    void use();     //激活shader
    void close();   //关闭shader
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMatrix4f(const std::string &name,glm::mat4 transform) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setVec4(const std::string &name, glm::vec4 value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};