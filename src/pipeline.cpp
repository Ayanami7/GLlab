#include "pipeline.h"

void Pipeline::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertex);
    glGenBuffers(1, &normal);
    glGenBuffers(1, &texCoord);
}

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
    vertexCount = static_cast<int>(model->vertices.size());
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vertex);
    glBufferData(GL_ARRAY_BUFFER, model->vertices.size() * sizeof(glm::vec3), model->vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normal);
    glBufferData(GL_ARRAY_BUFFER, model->normals.size() * sizeof(glm::vec3), model->normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glBufferData(GL_ARRAY_BUFFER, model->uvs.size() * sizeof(glm::vec2), model->uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(2);

    binded = true;
}

void Pipeline::draw()
{
    if (!binded)
    {
        throw std::runtime_error("Pipeline has not binded yet.");
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}