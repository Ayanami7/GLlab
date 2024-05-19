#include "pipeline.h"

void Pipeline::setShader(Shader *shader)
{
    this->shader = shader;
    shader->use();
}

Shader* Pipeline::getShader()
{
    return this->shader;
}

void Pipeline::bind(Model *model)
{
    meshCount = model->meshCount;
    binded = true;

    // 创建新的 VAO, VBO, EBO
    VAO.resize(meshCount);
    VBO.resize(meshCount);
    EBO.resize(meshCount);
    vertexCounts.resize(meshCount);
    materials.resize(meshCount);

    glGenVertexArrays(meshCount, VAO.data());
    glGenBuffers(meshCount, VBO.data());
    glGenBuffers(meshCount, EBO.data());

    for(int i = 0; i < meshCount; i++)
    {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, model->meshes[i].vertices.size() * sizeof(Vertex), model->meshes[i].vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->meshes[i].indices.size() * sizeof(unsigned int), model->meshes[i].indices.data(), GL_STATIC_DRAW);

        // 顶点位置
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // 顶点法线
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        // 顶点纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

        vertexCounts[i] = static_cast<unsigned int>(model->meshes[i].indices.size());
        materials[i] = model->meshes[i].material;
    }

    this->loadedTextures = model->loadedTextures;
    for(int i = 0; i < loadedTextures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        loadedTextures[i].bind();
    }

    meshToTextureIndice.resize(meshCount);
    for(int i = 0; i < meshCount; i++)
    {
        for(int j = 0; j < model->meshes[i].material.textures.size(); j++)
        {
            auto iter = std::find(loadedTextures.begin(), loadedTextures.end(), model->meshes[i].material.textures[j]);
            if(iter != loadedTextures.end())
            {
                meshToTextureIndice[i].push_back(static_cast<int>(std::distance(loadedTextures.begin(), iter)));
            }
        }
    }
}

// 清除资源
void Pipeline::clear()
{
    // 删除原有的 VAO, VBO, EBO
    if(binded)
    {
        if (VAO.size() > 0)
        {
            glDeleteVertexArrays(int(VAO.size()), VAO.data());
            glDeleteBuffers(int(VBO.size()), VBO.data());
            glDeleteBuffers(int(EBO.size()), EBO.data());
            VAO.clear();
            VBO.clear();
            EBO.clear();
            loadedTextures.clear();
            meshToTextureIndice.clear();
            vertexCounts.clear();
            materials.clear();
        }
    }
    binded = false;
}

void Pipeline::draw()
{
    if (!binded)
    {
        throw std::runtime_error("Pipeline has not binded yet.");
    }

    // 绘制meshCount个mesh
    for (int i = 0; i < meshCount; i++)
    {
        glBindVertexArray(VAO[i]);
        if (shader->shaderName == "texture")
        {
            for(int j = 0; j < meshToTextureIndice[i].size(); j++)
            {
                shader->setInt("material.diffuse", j);
            }
            shader->setVec3f("material.specular", materials[i].specular);
            shader->setFloat("material.shininess", materials[i].shininess);
        }
        else if(shader->shaderName == "phong")
        {
            shader->setVec3f("material.ambient", materials[i].ambient);
            shader->setVec3f("material.diffuse", materials[i].diffuse);
            shader->setVec3f("material.specular", materials[i].specular);
            shader->setFloat("material.shininess", materials[i].shininess);
        }
        else if (shader->shaderName == "default")
        {
            // 空操作
        }
        else
        {
            throw std::runtime_error("Unknown shader.");
        }

        // 是否绘制线框
        if (polygonMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, vertexCounts[i], GL_UNSIGNED_INT, 0);

        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, vertexCounts[i], GL_UNSIGNED_INT, 0);
        }

    }
}