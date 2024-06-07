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
    float speed;
    float sensitivity;
    float zoom;

public:
    Camera::Camera()
    {
        position = glm::vec3(0.0f, 0.0f, 3.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::vec3(1.0f, 0.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        speed = 2.5f;
        sensitivity = 0.1f;
        zoom = 45.0f;
    }
    Camera::~Camera() {}
};

