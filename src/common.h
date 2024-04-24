#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <optional>

#define PI 3.14f

using std::string;
using std::vector;

enum MaterialType
{
    DIFFUSE,
    SPECULAR,
    AMBIENT
};

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture
{
    unsigned int ID;
    string type;
    Texture(const string path);
    ~Texture();
    void bind();
    void unbind();
    inline unsigned int getID() { return ID; }
};

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct Light
{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};