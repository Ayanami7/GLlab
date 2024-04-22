#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "common.h"
#include "pipeline.h"

class MainWindow
{
private:
    GLFWwindow *window = nullptr;
    const char *title;
    const char *glsl_version = "#version 130";
    Pipeline *pipeline;

    // 暂时放在这 可能有后续抽象
    Model *model;
    
public:
    int height, width;
    float cameraDistance = 3.0f;
    float fov = 45.0f;

private:
    void debugWidget();                                         //调试窗口
    void settingWidget();                                       //设置窗口

public:
    MainWindow(int w = 1280, int h = 720, const char *t = "ImGui OpenGL")
        : width(w), height(h), title(t)
    {
    }
    ~MainWindow() {}
    void init();
    void show();
    void destroy();
};
