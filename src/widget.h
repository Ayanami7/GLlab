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
    Pipeline *pipeline;     //渲染管线

    // 视角参数
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    // 暂时放在这 可能有后续抽象
    Model *mmodel;
    Light light;

public:
    int height, width;
    float fov = 45.0f;
    float zoom_speed = 0.1f;
    float zNear = 0.1f;
    float zFar = 20.0f;

private:
    void debugWidget();                                         //调试窗口
    void settingWidget();                                       //设置窗口
    void mouseHandle();                                         //鼠标处理

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
