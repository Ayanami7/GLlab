#include "pipeline.h"

void Pipeline::setShader(Shader *shader)
{
    this->shader = shader;
    shader->use();
}

void Pipeline::render(Scene *scene)
{
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glfwPollEvents();

    // 清除深度缓冲区
    glClear(GL_DEPTH_BUFFER_BIT); // 清除深度缓冲区
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    // 配置环境光照
    shader->setVec3f("ambientColor", scene->getAmbientColor());
    shader->setFloat("ambientIntensity", scene->getAmbientIntensity());

    // 配置V和P矩阵
    shader->setVec3f("viewPos", scene->getCamera()->position);
    shader->setMat4f("view", scene->getCamera()->viewMatrix);
    shader->setMat4f("projection", scene->getCamera()->projectionMatrix);

    if (polygonMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 填充模式
    }

    // 遍历设置光源
    const std::vector<Light *> &lights = scene->getLights();
    for (int i = 0; i < lights.size(); i++)
    {
        shader->setInt("numLights", static_cast<int>(lights.size()));
        shader->setVec3f("lights[" + std::to_string(i) + "].position", lights[i]->position);
        shader->setVec3f("lights[" + std::to_string(i) + "].color", lights[i]->color);
        shader->setFloat("lights[" + std::to_string(i) + "].diffuseIntensity", lights[i]->diffuseIntensity);
        shader->setFloat("lights[" + std::to_string(i) + "].specularIntensity", lights[i]->specularIntensity);
    }

    // 遍历绘制模型
    const std::vector<Model *> &models = scene->getModels();
    for (auto model : models)
    {
        shader->setMat4f("model", model->getModelMatrix());

        for(auto mesh : model->meshes)
        {
            glBindVertexArray(mesh.VAO);
            // 此处规定了为第一张贴图
            if (mesh.material.textures.size() > 0)
            {
                shader->setInt("material.diffuse", mesh.material.textures[0].unit);
            }
            shader->setVec3f("material.specular", mesh.material.specular);
            shader->setFloat("material.shininess", mesh.material.shininess);

            glDrawElements(GL_TRIANGLES, static_cast<int>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
        }
    }


}