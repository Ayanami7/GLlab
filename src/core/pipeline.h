#pragma once
#include <functional>

#include "common.h"
#include "shader.h"
#include "scene.h"

class Pipeline
{
public:
    bool polygonMode = false;
    Shader *shader;
public:
    Pipeline(){}
    ~Pipeline(){}
    void setShader(Shader *shader);
    void render(Scene *scene);
};