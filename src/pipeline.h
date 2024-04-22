#pragma once

#include "common.h"
#include "model.h"
#include "loadShader.h"

class Pipeline
{
private:
    Shader *shader;
    unsigned int vertex;
    unsigned int normal;
    unsigned int texCoord;
    unsigned int VAO;
    int vertexCount;
    bool binded = false;

public:
    Pipeline(){};
    ~Pipeline(){}
    void setShader(Shader *shader);
    Shader* getShader();
    void bind(Model *model);
    void init();
    void draw();

};