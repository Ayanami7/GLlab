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

struct Light
{
    glm::vec3 position;
    glm::vec3 color;            // RGB颜色
    float diffuseIntensity;     // 漫反射强度
    float specularIntensity;    // 镜面反射强度
};