#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

int combination(int n, int k);

void bezierCurve(std::vector<float> &points, std::vector<float> &vertices, float step);

void screenToViewport(float &x, float &y, float screenWidth, float screenHeight);
