#pragma once

#include "common.h"
#include "widget.h"
#include "pipeline.h"
#include "scene.h"
#include "resourceManager.h"


class Renderer
{

private:
    // 没有做单例处理，但是作为单例使用
    Window *window;
    Scene *scene;
    Pipeline *pipeline;
    ShaderManager *shaderManager;
    ModelManager *modelManager;
    TextureManager *textureManager;
    
public:
    void render();
};