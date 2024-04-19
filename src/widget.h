#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "common.h"
#include "loadShader.h"

#define BEZIER_LINE 0
#define BEZIER_SURFACE 1

class MainWindow
{   
private:
    GLFWwindow *window = nullptr;
    const char *title;
    const char *glsl_version = "#version 130";
    // 用于控件
    const char *ranks[5] = {"2", "3", "4", "5", "6"};  //用于选择阶数
    int rankIndex = 0;              // +3 为控制点数
    const char *bezierTypes[2] = {"Line", "Surface"};        //用于选择显示类型
    int bezierIndex = BEZIER_LINE;        //贝塞尔曲线类型
    std::vector<float> c_points;    // 控制点 默认存储为7个
    int draggingIndex = -1;              //用于判断屏幕上哪个点正在被拖动
    
    Shader *shader;
public:
    int height, width;

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;

    float distance = 3.0f;  // 相机距离
    float fov = 45.0f;      // 视野范围，角度制

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

private:
    void debugWidget();              // 调试窗口
    void settingWidget();            // 设置窗口
    void render1();                  // 绘制贝塞尔曲线
    void render2();                  // 绘制贝塞尔曲面
    void drawCircle(float x, float y, float radius, int nums);      //绘制圆

public:
    MainWindow(int w = 1280, int h = 720, const char *t = "ImGui OpenGL")
        : width(w), height(h), title(t)
    {
    }

    void init();
    void show();
    void destroy();
};
