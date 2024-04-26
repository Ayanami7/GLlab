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

class Texture
{
private:
    unsigned int ID;
    string type;
    unsigned char *image;
    int width;
    int height;
    int nrChannels;
public:
    Texture(const string path);
    ~Texture();
    void load();
    void unload();
    inline unsigned int getID() { return ID; }
};

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    std::optional<Texture*> texture;
};

struct Light
{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};