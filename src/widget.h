#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "common.h"
#include "loadShader.h"

class MainWindow
{
private:
    GLFWwindow *window = nullptr;
    const char *title;
    const char *glsl_version = "#version 130";
    const char *ranks[4] = {"2", "3", "4", "5"};
    int rankIndex = 0;
    int maxRank = 2;
    Shader *shader;
    
public:
    int height, width;

private:
    void debugWidget();                                         //调试窗口
    void settingWidget();                                       //设置窗口
    void display(std::vector<float> vertices);                  //绘制

public:
    MainWindow(int w = 1280, int h = 720, const char *t = "ImGui OpenGL")
        : width(w), height(h), title(t)
    {
    }

    void init();
    void show();
    void destroy();
};
