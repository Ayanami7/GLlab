#include <cstdlib>

#include "common.h"

int combination(int n, int k)
{
    int result = 1;
    for (int i = 1; i <= k; ++i)
    {
        result *= n - i + 1;
        result /= i;
    }
    return result;
}

// 计算贝塞尔曲线上的点
void bezierCurve(std::vector<float> &points,int n, std::vector<float> &vertices, float step)
{
    if(points.size() < 9)
        return;
    n = n - 1;
    for (float t = 0; t <= 1; t += step)
    {
        float x = 0.0f, y = 0.0f, z = 0.0f;
        for (int j = 0; j <= n; ++j)
        {
            float basis = combination(n, j) * std::pow(1 - t, n - j) * std::pow(t, j); // 计算基函数值
            x += basis * points[3 * j];
            y += basis * points[3 * j + 1];
            z += basis * points[3 * j + 2];
        }
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }
}

void createSphere(glm::vec3 center, std::vector<float> &vertices,
                  std::vector<unsigned int> &indices, float radius, unsigned int rings, unsigned int sectors)
{
    vertices.clear();
    indices.clear();

    for (unsigned int y = 0; y <= rings; ++y)
    {
        for (unsigned int x = 0; x <= sectors; ++x)
        {
            float xSegment = (float)x / (float)sectors;
            float ySegment = (float)y / (float)rings;
            float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = std::cos(ySegment * M_PI);
            float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

            vertices.push_back(xPos * radius + center.x);
            vertices.push_back(yPos * radius + center.y);
            vertices.push_back(zPos * radius + center.z);
        }
    }

    for (unsigned int i = 0; i < rings; ++i)
    {
        for (unsigned int j = 0; j < sectors; ++j)
        {
            int start = (i * (sectors + 1) + j);
            indices.push_back(start);
            indices.push_back(start + sectors + 1);
            indices.push_back(start + sectors + 2);
            indices.push_back(start);
            indices.push_back(start + sectors + 2);
            indices.push_back(start + 1);
        }
    }
}