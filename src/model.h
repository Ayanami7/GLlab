#pragma once
#include <tiny_obj_loader.h>

#include "common.h"
#include "texture.h"

struct Model
{
    vector<vec3> vertices;
    vector<vec2> uvs;
    vector<vec3> normals;
    std::optional<Texture*> texture;

    Model(const string path);
    ~Model();
    void loadTexture(string path);
};