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

