#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

#include "common.h"

class Shader
{
public:
    unsigned int ID;
    string shaderName;
    Shader(const string vertexPath, const string fragmentPath, const string name);
    void use();     //激活shader
    void remove();   //关闭shader
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMatrix4f(const std::string &name,glm::mat4 transform) const;
    void setVec3f(const std::string &name, glm::vec3 value) const;
    void setVec4f(const std::string &name, glm::vec4 value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

class ShaderView
{
public:
    Shader *shader;
    ShaderView(Shader *shader);
    void use();
    void remove();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setMatrix4f(const std::string &name,glm::mat4 transform);
    void setVec3f(const std::string &name, glm::vec3 value);
    void setVec4f(const std::string &name, glm::vec4 value);
};