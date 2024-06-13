#include "renderer.h"

void Renderer::init()
{
    scene = new Scene();
    shaderManager = new ShaderManager();
    modelManager = new ModelManager();
    textureManager = new TextureManager();
    pipeline = new Pipeline();

    // 执行资源加载和处理
    shaderManager->loadShader("../../shader/texture.vert", "../../shaders/texture.frag", "default");
    modelManager->loadModel("../../resource/model/room.obj", "room");
    textureManager->loadTexture("../../resource/texture/room.png", "room_texture");

    // 设置shader
    pipeline->setShader(shaderManager->getShader("default"));
    // 添加场景信息
    Model* m1 = modelManager->getModel("room");
    m1->loadTexture(0, textureManager->getTexture("room_texture"));
    scene->addModel(m1);

    Light *l1 = new Light();
    l1->position = glm::vec3(1.2f, 1.0f, 2.0f);
    l1->color = glm::vec3(1.0f, 1.0f, 1.0f);
    l1->diffuseIntensity = 0.5f; // 控制漫反射光强
    l1->specularIntensity = 1.0f; // 控制镜面反射光强
    scene->addLight(l1);
}

void Renderer::render()
{
    pipeline->render(scene);
}

