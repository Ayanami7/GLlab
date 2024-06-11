#include <stb_image.h>

#include "resourceManager.h"

void ShaderManager::loadShader(const string vertexPath, const string fragmentPath, const string name)
{
    Shader *shader = new Shader(vertexPath, fragmentPath, name);
    loadedShaders.push_back(shader);
}

void ModelManager::loadModel(const string path, const string name)
{
    Model *model = new Model();
       // load the model
    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;

    try
    {
        string err;
        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str()))
        {
            throw FileNotFoundException(err);
        }
    }
    catch(const BaseException& e)
    {
        Logger::Log(e.what());
        Logger::Print(e.what());
        Logger::Log("Failed to load model: " + path);
        Logger::Print("Failed to load model: " + path);
        throw e;
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
        model->meshes.push_back(Mesh(vertices, indices));
    }
    for (auto mesh : model->meshes)
    {
        model->vertexCount += static_cast<int>(mesh.vertices.size());
        model->faceCount += static_cast<int>(mesh.indices.size() / 3);
    }
    model->meshCount = static_cast<int>(model->meshes.size());
}

void TextureManager::loadTexture(const string path, const string name)
{
    Texture texture(path, name);

    // 检查是否已经加载过，避免重复加载
    if (std::find(loadedTextures.begin(), loadedTextures.end(), texture) != loadedTextures.end())
    {
        return;
    }

    unsigned char *image;
    int width;
    int height;
    int nrChannels;

    try
    {
        // 使用 stb_image.h 加载图片
        stbi_set_flip_vertically_on_load(true); // 如果需要，翻转图片
        image = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    }
    catch(const BaseException& e)
    {
        Logger::Log(e.what());
        Logger::Print(e.what());
        Logger::Log("Failed to load texture: " + path);
        Logger::Print("Failed to load texture: " + path);
        throw e;
    }
    
    if (image)
    {
        // 生成纹理
        glGenTextures(1, &texture.ID);
        glBindTexture(GL_TEXTURE_2D, texture.ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 上传纹理到 GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(image);

        if(currentUnit >= 32)
        {
            throw InvalidValueException("GPU Texture unit is full!");
        }
        texture.bind(currentUnit);
        currentUnit++;
        loadedTextures.push_back(texture);
    }
    else
    {
        throw InvalidValueException("Invalid image : " + path);
    }
}

void TextureManager::clear()
{
    for (auto texture : loadedTextures)
    {
        texture.destroy();
    }
    loadedTextures.clear();
    currentUnit = 0;
}