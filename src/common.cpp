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
void bezierCurve(std::vector<float> &points, std::vector<float> &vertices, float step)
{
    if(points.size() < 6)
        return;
    int n = static_cast<int>(points.size() / 3 - 1); // 控制点数量减1，即贝塞尔曲线的阶数
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

void screenToViewport(float &x, float &y, float screenWidth, float screenHeight)
{
    x = (x / screenWidth - 0.5f) * screenWidth;
    y = (0.5f - y / screenHeight) * screenHeight;
}