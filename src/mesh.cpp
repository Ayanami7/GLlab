#include "mesh.h"

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
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        for (int i = 0; i < attrib.vertices.size() / 3; i++)
        {
            Vertex vertex;
            vertex.position = {attrib.vertices[3 * i + 0],
                               attrib.vertices[3 * i + 1],
                               attrib.vertices[3 * i + 2]};
            vertex.normal = {attrib.normals[3 * i + 0],
                             attrib.normals[3 * i + 1],
                             attrib.normals[3 * i + 2]};
            vertex.texCoords = {attrib.texcoords[2 * i + 0], attrib.texcoords[2 * i + 1]};
            vertices.push_back(vertex);
        }
        
        // 此处假设所有索引都是一样的
        for (const auto &index : shape.mesh.indices)
        {
            indices.push_back(index.vertex_index);
        }
        meshes.push_back(Mesh(vertices, indices));
    }
    meshCount = meshes.size();
}

void Model::setAllTexture(Texture tex)
{
    for(auto &mesh : meshes)
    {
        mesh.loadTexture(tex);
    }
}

Model::~Model()
{

}