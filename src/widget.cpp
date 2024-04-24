#include "widget.h"

using std::vector;

void MainWindow::init()
{
    glfwInit();

    // 创建窗口
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize the OpenGL context" << std::endl;
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘控制

    // 创建管线和模型
    pipeline = new Pipeline();
    mmodel = new Model("../../resource/model/cow.obj");

    // 计算MVP矩阵
    float aspect = static_cast<float>(width) / height;
    float near = 0.1f;  // 近裁剪面
    float far = 100.0f; // 远裁剪面
    projection = glm::perspective(glm::radians(fov), aspect, near, far);
    view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::lookAt(this->cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4(1.0f);

    Shader *shader = new Shader("../../shader/default_vert.glsl", "../../shader/default_frag.glsl");

    pipeline->setShader(shader);
    shader->setMatrix4f("projection", projection);
    shader->setMatrix4f("view", view);
    shader->setMatrix4f("model", model);

    // 设置 ImGui 风格
    ImGui::StyleColorsDark();

    // 设置 ImGui 平台/渲染器绑定
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void MainWindow::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void MainWindow::debugWidget()
{
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    ImGui::Text("This is a test.");
    ImGui::Text("Framebuffer size: %d x %d", w, h);
    ImGui::Text("Vertex count: %d", mmodel->vertexCount);
    ImGui::Text("Triangle count: %d", mmodel->faceCount);
}

void MainWindow::settingWidget()
{
    if (ImGui::Begin("setting"))
    {
        
    }
    ImGui::End();
}

void MainWindow::show()
{
    pipeline->bind(mmodel);
    std::cout << sizeof(Vertex) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);    // 启用深度测试
        glfwPollEvents();

        // 清除深度缓冲区
        glClear(GL_DEPTH_BUFFER_BIT); // 清除深度缓冲区
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);

        // 开始新的 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        pipeline->draw();

        // 鼠标处理
        mouseHandle();
        // 调试窗口
        debugWidget();
        // 设置窗口
        settingWidget();

        // 渲染 ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void MainWindow::mouseHandle()
{
     if (ImGui::IsMouseDragging(0) &&        //鼠标左键拖动
        !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) &&     //鼠标不在ImGui窗口上
        !ImGui::IsAnyItemActive())          //没有其他活动项
    {
        ImVec2 drag_delta = ImGui::GetMouseDragDelta(0);
        ImGui::ResetMouseDragDelta(0);

        // 计算旋转角度，这里假设每拖动200像素，旋转90度
        float rotate_angle_x = drag_delta.y / 200.0f * glm::pi<float>() / 2;
        float rotate_angle_y = drag_delta.x / 200.0f * glm::pi<float>() / 2;

        // 创建旋转矩阵
        glm::mat4 rotate_x = glm::rotate(glm::mat4(1.0f), rotate_angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotate_y = glm::rotate(glm::mat4(1.0f), rotate_angle_y, glm::vec3(0.0f, 1.0f, 0.0f));

        // 将旋转矩阵应用到模型矩阵
        model = rotate_x * rotate_y * model;
        pipeline->getShader()->setMatrix4f("model", model);
    }
    // 获取ImGui的IO对象
    ImGuiIO &io = ImGui::GetIO();
    // 如果滚轮有滚动
    if (io.MouseWheel != 0 &&
        !ImGui::IsAnyItemActive())
    {
        cameraPos.z -= io.MouseWheel * zoom_speed;
        view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        pipeline->getShader()->setMatrix4f("view", view);
    }
}

