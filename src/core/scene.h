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
    Scene();
    ~Scene();

    void AddModel(Model* model);
    void Initialize();
    void Update();
    void Render();
};