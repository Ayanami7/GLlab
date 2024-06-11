#include "scene.h"

Scene::Scene()
{
    camera = new Camera();
}

Scene::~Scene()
{
    delete camera;
    for (int i = 0; i < models.size(); i++)
    {
        delete models[i];
    }
    for (int i = 0; i < lights.size(); i++)
    {
        delete lights[i];
    }
}

void Scene::addModel(Model *model)
{
    models.push_back(model);
}

void Scene::addLight(Light *light)
{
    lights.push_back(light);
}
