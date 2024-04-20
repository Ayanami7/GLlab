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
    const char *ranks[5] = {"2", "3", "4", "5", "6"};       // 用于选择阶数
    int rankIndex = 0;                                      // +3 为控制点数
    const char *controlPointOptions[16] =
        {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"}; // 用于选择3D控制点
    int pointsIndex = 0;                                    // 3D控制点索引
    const char *bezierTypes[2] = {"2D", "3D"};              // 用于选择显示类型
    int bezierIndex = BEZIER_LINE;                          // 贝塞尔曲线类型

    int draggingIndex = -1;                                 // 用于判断屏幕上哪个点正在被拖动

    std::vector<float> c_points;                            // 控制点 默认存储为7个
    std::vector<float> vbuffer;                             // 用于存储线缓冲
    unsigned int VAO, VBO;                                  // VAO VBO

    std::vector<std::vector<float>> c_points3D;             // 存储3D控制点
    std::vector<float> vbuffer3D;                           // 用于存储3D面缓冲
    unsigned int VAO3D, VBO3D;                              // 3D VAO VBO

    std::vector<float> sbuffer;                             // 用于存储球体缓冲
    std::vector<unsigned int> ibuffer;                      // 存储索引缓冲
    unsigned int VAOs, VBOs, EBOs;                          // 球体 VAO VBO EBO

    bool modfiy3D = true;
    bool displayPoints = false;
    Shader *shader;
public:
    int height, width;

    float distance = 3.0f;      // 相机初始距离
    float fov = 45.0f;          // 视野范围，角度制

    float zoom_speed = 0.3f;    // 缩放速度

    // MVP矩阵
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

private:
    void debugWidget();              // 调试窗口
    void settingWidget();            // 设置窗口
    void render1();                  // 绘制贝塞尔曲线
    void render2();                  // 绘制贝塞尔曲面
    void switchType();               // 控件改变时切换类型

public:
    MainWindow(int w = 1280, int h = 720, const char *t = "ImGui OpenGL")
        : width(w), height(h), title(t)
    {
    }

    void init();
    void show();
    void destroy();
};
