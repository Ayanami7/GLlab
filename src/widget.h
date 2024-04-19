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
    const char *ranks[6] = {"2", "3", "4", "5", "6", "7"};
    int rankIndex = 0;              // +2 为贝塞尔曲线的阶数
    std::vector<float> c_points;    // 控制点 默认存储为7个
    int draggingIndex = -1;              //用于判断屏幕上哪个点正在被拖动
    int bezierType = BEZIER_LINE;        //贝塞尔曲线类型

    Shader *shader;
public:
    int height, width;

private:
    void debugWidget();                                         //调试窗口
    void settingWidget();                                       //设置窗口
    void display(std::vector<float> &vertices);                  //绘制贝塞尔曲线
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
