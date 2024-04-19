#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

int combination(int n, int k);

void bezierCurve(std::vector<float> &points, int n, std::vector<float> &vertices, float step);

inline void screenToViewport(float &x, float &y, float screenWidth, float screenHeight)
{
    x = (x / screenWidth - 0.5f) * screenWidth;
    y = (0.5f - y / screenHeight) * screenHeight;
}

inline bool insideCircle(float x, float y, float rx, float ry, float radius)
{
    float dx = x - rx;
    float dy = y - ry;
    float t = dx * dx + dy * dy;
    return t <= radius * radius;
}