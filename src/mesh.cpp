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
            // 处理位置
            vertex.position = {attrib.vertices[3 * index.vertex_index + 0],
                               attrib.vertices[3 * index.vertex_index + 1],
                               attrib.vertices[3 * index.vertex_index + 2]};
            // 检查是否存在法线
            if (index.normal_index >= 0)
            {
                vertex.normal = {attrib.normals[3 * index.normal_index + 0],
                                 attrib.normals[3 * index.normal_index + 1],
                                 attrib.normals[3 * index.normal_index + 2]};
            }
            else
            {
                vertex.normal = {0.0f, 0.0f, 0.0f};
            }
            // 检查是否存在纹理坐标
            if (index.texcoord_index >= 0)
            {
                vertex.texCoords = {attrib.texcoords[2 * index.texcoord_index + 0],
                                    attrib.texcoords[2 * index.texcoord_index + 1]};
            }
            else
            {
                vertex.texCoords = {0.0f, 0.0f};
            }
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

Model::~Model()
{
    for (auto t: loadedTextures)
    {
        t.destroy();
    }
}