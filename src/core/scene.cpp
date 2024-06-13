#include "scene.h"

Scene::Scene()
{
    camera = new Camera();
}

Scene::~Scene()
{
    delete camera;

    // 无需删除Model资源，有ModelManager统一管理
    models.clear();

    for (int i = 0; i < lights.size(); i++)
    {
        delete lights[i];
    }
    lights.clear();
}

void Scene::setViewPort(int width, int height)
{
    this->camera->width = width;
    this->camera->height = height;
    this->camera->update();
}

void Scene::addModel(Model *model)
{
    models.push_back(model);
    this->meshCount += model->meshCount;
    this->vertexCount += model->vertexCount;
    this->faceCount += model->faceCount;
}

void Scene::addLight(Light *light)
{
    lights.push_back(light);
}

void Scene::deleteModel(Model *model)
{
    auto it = std::find(models.begin(), models.end(), model);
    if (it != models.end())
    {
        models.erase(it);
    }
    else
    {
        throw InvalidValueException("Model not found.");
    }
}

void Scene::deleteLight(Light *light)
{
    auto it = std::find(lights.begin(), lights.end(), light);
    if (it != lights.end())
    {
        delete *it;
        lights.erase(it);
    }
    else
    {
        throw InvalidValueException("Light not found.");
    }
}

void Scene::update()
{
    for(auto &m : models)
    {
        m->update();
    }
}

void Scene::clear()
{
    models.clear();
    for(int i = 0; i < lights.size(); i++)
    {
        delete lights[i];
    }
    lights.clear();
}