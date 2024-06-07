#pragma once

#include "common.h"
#include "model.h"
#include "shader.h"

class Pipeline
{
private:
    Shader *shader;
    vector<unsigned int> VAO;
    vector<unsigned int> VBO;
    vector<unsigned int> EBO;
    vector<unsigned int> vertexCounts;
    vector<Material> materials;
    vector<Texture> loadedTextures;
    vector<vector<int>> meshToTextureIndice;
    int meshCount;
    bool binded = false;

public:
    bool polygonMode = false;
public:
    Pipeline(){}
    ~Pipeline(){}
    void setShader(Shader *shader);
    Shader* getShader();
    void initShader();
    void bind(Model *model);
    void draw();
    void clear();

};