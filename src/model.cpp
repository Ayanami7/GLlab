#include "model.h"

Model::Model(const string path)
{
    // load the model
    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;

    string err;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str()))
    {
        throw std::runtime_error(err);
    }

    for (const auto &shape : shapes)
    {
        for (const auto &index : shape.mesh.indices)
        {
            vertices.push_back(vec3(attrib.vertices[3 * index.vertex_index + 0],
                                    attrib.vertices[3 * index.vertex_index + 1],
                                    attrib.vertices[3 * index.vertex_index + 2]));

            uvs.push_back(vec2(attrib.texcoords[2 * index.texcoord_index + 0],
                               attrib.texcoords[2 * index.texcoord_index + 1]));

            normals.push_back(vec3(attrib.normals[3 * index.normal_index + 0],
                                   attrib.normals[3 * index.normal_index + 1],
                                   attrib.normals[3 * index.normal_index + 2]));
        }
    }
}

Model::~Model()
{
    // optional对象会自动销毁，但是这里是指针，需要手动销毁
    if (texture.has_value())
    {
        delete texture.value();
    }
}

void Model::loadTexture(string path)
{
    texture = new Texture(path);
}