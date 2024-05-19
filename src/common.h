#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

#ifdef _MSC_VER
    #define M_PI 3.14f
#endif

using std::string;
using std::vector;
using std::unordered_map;

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
    string path;
    string name;

    // 默认构造
    Texture(const string path, const string type);
    // 拷贝构造
    Texture(const Texture &other) : ID(other.ID), path(other.path), name(other.name) {}
    // 析构
    ~Texture(){};

    bool operator==(const Texture &other) const
    {
        return this->ID == other.ID;
    }
    bool operator!=(const Texture &other) const
    {
        return this->ID != other.ID;
    }
    void bind();
    void unbind();
    void destroy();
    inline unsigned int getID() { return ID; }
};

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    vector<Texture> textures;
};

struct Light
{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};