#pragma once

#include "common.h"

class Camera
{
public:
    float fov = 45.0f;
    float zoom_speed = 0.1f;
    float zNear = 0.1f;
    float zFar = 20.0f;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    int height;
    int width;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

public:
    Camera::Camera()
    {
        position = glm::vec3(0.0f, 0.0f, 3.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::vec3(1.0f, 0.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        viewMatrix = glm::mat4(1.0f);
        projectionMatrix = glm::mat4(1.0f);
    }
    Camera::~Camera() {}

    void update()
    {
        right = glm::normalize(glm::cross(this->front, worldUp));
        up = glm::normalize(glm::cross(right, this->front));

        viewMatrix = glm::lookAt(position, position + front, up);
        projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(width / height), zNear, zFar);
    }
};

