#pragma once

#include <tiny_obj_loader.h>

#include "common.h"
#include "exception.h"
#include "shader.h"
#include "model.h"

class ShaderManager
{
public:
    vector<Shader*> loadedShaders;
public:
    void loadShader(const string vertexPath, const string fragmentPath, const string name);
};

class ModelManager
{
public:
    vector<Model*> loadedModels;
public:
    void loadModel(const string path, const string name);
};

class TextureManager
{
public:
    vector<Texture> loadedTextures;
    int currentUnit = 0;
public:
    void loadTexture(const string path, const string name); 
    void clear();
};

// Mesh(vector<Vertex> vertices, vector<unsigned int> indices, MaterialType type = MaterialType::DIFFUSE)
// {
//     if (type == MaterialType::DIFFUSE)
//     {
//         material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.shininess = 32.0f;
//     }
//     else if (type == MaterialType::SPECULAR)
//     {
//         material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
//         material.shininess = 128.0f;
//     }
//     else if (type == MaterialType::AMBIENT)
//     {
//         material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
//         material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
//         material.shininess = 32.0f;
//     }
//     this->vertices = vertices;
//     this->indices = indices;
// }