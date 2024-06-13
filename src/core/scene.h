#pragma once

#include "common.h"
#include "model.h"
#include "camera.hpp"
#include "exception.h"

class Scene
{
private:
    // 核心组件
    Camera *camera;
    vector<Model *> models;
    vector<Light *> lights;

    // 环境设置
    glm::vec3 ambientColor;
    float ambientIntensity;
    
public:
    // 性能统计数据
    int vertexCount = 0;
    int faceCount = 0;
    int meshCount = 0;

public:
    // 数据获取接口
    const vector<Model *>& getModels() const { return models; }
    const vector<Light *>& getLights() const { return lights; }
    void setAmbientColor(const glm::vec3& color) { ambientColor = color; }
    void setAmbientIntensity(float intensity) { ambientIntensity = intensity; }
    glm::vec3 getAmbientColor() const { return ambientColor; }
    float getAmbientIntensity() const { return ambientIntensity; }
    Camera* getCamera() const { return camera; }

public:
    Scene();
    ~Scene();

    // 通用接口
    void setViewPort(int width, int height);
    void addModel(Model* model);
    void addLight(Light* light);
    void deleteModel(Model* model);
    void deleteLight(Light* light);
    void update();
    void clear();

};