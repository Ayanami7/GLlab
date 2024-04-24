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
    // 删除原有的 VAO, VBO, EBO
    meshCount = model->meshCount;
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
            vertexCounts.clear();
            materials.clear();
            textures.clear();
        }
    }
    binded = true;

    // 创建新的 VAO, VBO, EBO
    VAO.resize(meshCount);
    VBO.resize(meshCount);
    EBO.resize(meshCount);
    vertexCounts.resize(meshCount);
    materials.resize(meshCount);
    textures.resize(meshCount);

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
        if (model->meshes[i].texture.has_value())
        {
            textures.push_back(model->meshes[i].texture);
        }
        else
        {
            textures.push_back(std::nullopt);
        }
    }
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
        shader->setVec3f("material.ambient", materials[i].ambient);
        shader->setVec3f("material.diffuse", materials[i].diffuse);
        shader->setVec3f("material.specular", materials[i].specular);
        shader->setFloat("material.shininess", materials[i].shininess);
        glBindVertexArray(VAO[i]);
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