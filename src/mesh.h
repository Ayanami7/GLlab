#pragma once
#include <tiny_obj_loader.h>

#include "common.h"

struct Mesh
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    std::optional<Texture> texture;
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }
    ~Mesh(){};
    inline void loadTexture(Texture tex)        //加载纹理但并不启用
    {
        this->texture = tex;
    }
};

struct Model
{
    vector<Mesh> meshes;
    int meshCount;
    void setAllTexture(Texture tex);
    Model(const string path);
    ~Model();
};