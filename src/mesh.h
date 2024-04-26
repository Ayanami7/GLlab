#pragma once
#include <tiny_obj_loader.h>

#include "common.h"

struct Mesh
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Material material;
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, MaterialType type = MaterialType::DIFFUSE)
    {
        if (type == MaterialType::DIFFUSE)
        {
            material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
            material.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
            material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
            material.shininess = 32.0f;
        }
        else if (type == MaterialType::SPECULAR)
        {
            material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
            material.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
            material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
            material.shininess = 64.0f;
        }
        else if (type == MaterialType::AMBIENT)
        {
            material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
            material.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
            material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
            material.shininess = 32.0f;
        }
        this->vertices = vertices;
        this->indices = indices;
    }
    ~Mesh(){};
    inline void loadTexture(Texture *tex)        //加载纹理但并不启用
    {
        this->material.texture = tex;
    }
};

struct Model
{
    vector<Mesh> meshes;
    int meshCount = 0;
    int vertexCount = 0;
    int faceCount = 0;
    void setAllTexture(Texture *tex);
    Model(const string path);
    ~Model();
};