#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "common.h"
#include "renderer.h"

class Window
{
private:
    GLFWwindow *window = nullptr;
    const char *title;
    const char *glsl_version = "#version 130";
    Renderer *renderer;

public:
    int height, width;
public:
    Window(int w = 1280, int h = 720, const char *t = "ImGui OpenGL")
        : width(w), height(h), title(t)
    {
    }
    ~Window() {}
    void init();
    void show();
    void destroy();
};
