#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "common.h"
#include "material.h"

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
    Material material;

public:
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices) : vertices(vertices), indices(indices)
    {
        setupMesh();
    }
    ~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void setupMesh();
};

class Model
{
public:
    // 核心数据
    vector<Mesh> meshes;
    vector<Texture> loadedTextures;
    string name;

    // 位置信息
    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    // 性能统计数据
    int meshCount = 0;
    int vertexCount = 0;
    int faceCount = 0;

private:
    void updateMatrix();    // 更新模型矩阵

public:
    // 数据获取接口
    void Model::setPosition(const glm::vec3 &position) { this->position = position; }
    void Model::setRotation(const glm::vec3 &rotation) { this->rotation = rotation; }
    void Model::setScale(const glm::vec3 &scale) { this->scale = scale; }
    glm::vec3 Model::getPosition() const { return this->position; }
    glm::vec3 Model::getRotation() const { return this->rotation; }
    glm::vec3 Model::getScale() const { return this->scale; }
    glm::mat4 Model::getModelMatrix() const { return this->modelMatrix; }

    // 通用接口
    void update();      // 更新状态
    void render();      // 执行渲染
    void loadTexture(int index, const Texture &texture)
    {
        if(index < 0 || index >= meshes.size())
        {
            throw std::runtime_error("Index out of range.");
        }
        if(std::find(loadedTextures.begin(), loadedTextures.end(), texture) == loadedTextures.end())
        {
            loadedTextures.push_back(texture);
        }
        meshes[index].material.textures.push_back(texture);
    }
    Model();
    ~Model();
};