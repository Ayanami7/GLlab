#pragma once

#include "common.h"
#include "model.h"
#include "camera.hpp"

class Scene
{
private:
    // 核心组件
    Camera *camera;
    vector<Model *> models;
    vector<Light *> lights;

    // 环境设置
    glm::vec3 ambientColor;
    glm::vec3 ambientIntensity;

public:


    // 性能统计数据
    int vertexCount = 0;
    int faceCount = 0;
    int meshCount = 0;

public:
    Scene();
    ~Scene();

    // 通用接口
    void addModel(Model* model);
    void initialize();
    void update();
    void render();
};