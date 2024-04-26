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
        for (const auto &index : shape.mesh.indices)
        {
            Vertex vertex;
            vertex.position = {attrib.vertices[3 * index.vertex_index + 0],
                               attrib.vertices[3 * index.vertex_index + 1],
                               attrib.vertices[3 * index.vertex_index + 2]};
            vertex.normal = {attrib.normals[3 * index.normal_index + 0],
                             attrib.normals[3 * index.normal_index + 1],
                             attrib.normals[3 * index.normal_index + 2]};
            vertex.texCoords = {attrib.texcoords[2 * index.texcoord_index + 0],
                                attrib.texcoords[2 * index.texcoord_index + 1]};

            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < shape.mesh.indices.size(); i++)
        {
            indices.push_back(i);
        }
        meshes.push_back(Mesh(vertices, indices));
    }
    for(auto mesh : meshes)
    {
        vertexCount += static_cast<int>(mesh.vertices.size());
        faceCount += static_cast<int>(mesh.indices.size() / 3);
    }
    meshCount = static_cast<int>(meshes.size());
}

void Model::setAllTexture(Texture *tex)
{
    for(auto &mesh : meshes)
    {
        mesh.loadTexture(tex);
    }
}

Model::~Model()
{

}