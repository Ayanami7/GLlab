#pragma once

#include "common.h"
#include "mesh.h"
#include "loadShader.h"

class Pipeline
{
private:
    Shader *shader;
    vector<unsigned int> VAO;
    vector<unsigned int> VBO;
    vector<unsigned int> EBO;
    vector<unsigned int> vertexCounts;
    bool binded = false;

public:
    Pipeline(){};
    ~Pipeline(){}
    void setShader(Shader *shader);
    Shader* getShader();
    void bind(Model *model);
    void draw();

};