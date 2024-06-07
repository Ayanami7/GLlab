#pragma once

#include <tiny_obj_loader.h>

#include "common.h"
#include "shader.h"
#include "model.h"

class ResourceManager
{
public:
    Shader* getShader(const string vertexPath, const string fragmentPath, const string name);
    Model* getModel(const string path, const string name);
    Texture getTexture(const string path, const string name);      
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