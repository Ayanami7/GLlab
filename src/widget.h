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

    // 用于控件
    // 着色器选择框
    const char *ui_shaderType[2] = {"Phong", "Texture"};
    int ui_shaderIndex = 0;
    // 用于模型选择框
    const char *ui_modelName[6] = {"bunny", "teapot", "room", "amost", "xbox", "chest"};
    int ui_modelIndex = 0;

    bool lightEnable = true;

    // 着色器文件
    Shader *defaultShader;
    Shader *phongShader;
    Shader *textureShader;

    // 视角参数
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // 暂时放在这 可能有后续抽象
    Model *currentModel;
    vector<Model *> modelList;
    Light light;

public:
    int height, width;
    float fov = 45.0f;
    float zoom_speed = 0.3f;
    float zNear = 0.1f;
    float zFar = 20.0f;

private:
    void debugWidget();                                         //调试窗口
    void settingWidget();                                       //设置窗口
    void meshWidget();                                          //模型窗口
    void mouseHandle();                                         //鼠标处理

public:
    MainWindow(int w = 1280, int h = 720, const char *t = "ImGui OpenGL")
        : width(w), height(h), title(t)
    {
    }
    ~MainWindow() {}
    void init();
    void checkShader();
    void show();
    void destroy();
};
