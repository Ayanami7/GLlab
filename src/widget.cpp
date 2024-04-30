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
    mmodel = new Model("../../resource/model/room.obj");
    Texture *texture = new Texture("../../resource/texture/room.png");
    mmodel->setAllTexture(texture);

    // 初始的视角矩阵
    // 计算MVP矩阵
    float aspect = static_cast<float>(width) / height;
    projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
    view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::lookAt(this->cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4(1.0f);


    // 创建一些必要信息
    light.position = glm::vec3(1.2f, 1.0f, 2.0f);
    light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    // 创建着色器
    phongShader = new Shader("../../shader/phong.vert", "../../shader/phong.frag", "phong");
    textureShader = new Shader("../../shader/texture.vert", "../../shader/texture.frag", "texture");

    pipeline->setShader(phongShader);
    checkShader();      // 检查shader
    pipeline->bind(mmodel);

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
    // 设定初始位置和大小
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(270, 140));
    ImGui::Text("This is a test.");
    ImGui::Text("Framebuffer size: %d x %d", w, h);
    ImGui::Text("Vertex count: %d", mmodel->vertexCount);
    ImGui::Text("Triangle count: %d", mmodel->faceCount);
}

void MainWindow::settingWidget() 
{
    // 设定初始位置和大小
    ImGui::SetNextWindowPos(ImVec2(float(width - 320), 0));
    ImGui::SetNextWindowSize(ImVec2(320, 280));
    if (ImGui::Begin("setting"))
    {
        ImGui::Checkbox("Polygon Mode", &pipeline->polygonMode);
        ImGui::PushItemWidth(100); // 设置接下来的控件宽度为100
        // 设置阶数
        if (ImGui::Combo("Shader Type", &ui_shaderIndex, ui_shaderType, IM_ARRAYSIZE(ui_shaderType)))
        {
            if(ui_shaderIndex == 0)
            {
                pipeline->setShader(phongShader);

            }
            else if(ui_shaderIndex == 1)
            {
                pipeline->setShader(textureShader);
            }
            checkShader();
        }
        ImGui::PopItemWidth(); // 恢复之前的宽度

        ImGui::Text(" ");
        ImGui::Text("Light Position");
        if(ImGui::Checkbox("Enable Light", &lightEnable))
        {
            checkShader();
        }
        if (lightEnable)
        {
            ImGui::PushItemWidth(120); // 设置接下来的控件宽度为150
            bool t1 = ImGui::SliderFloat("X", &light.position.x, -3.0f, 3.0f);
            bool t2 = ImGui::SliderFloat("Y", &light.position.y, -3.0f, 3.0f);
            bool t3 = ImGui::SliderFloat("Z", &light.position.z, -3.0f, 3.0f);
            ImGui::PopItemWidth();

            ImGui::PushItemWidth(240);
            bool t4 = ImGui::SliderFloat3("Ambient", &light.ambient[0], 0.0f, 1.0f);
            bool t5 = ImGui::SliderFloat3("Diffuse", &light.diffuse[0], 0.0f, 1.0f);
            bool t6 = ImGui::SliderFloat3("Specular", &light.specular[0], 0.0f, 1.0f);
            ImGui::PopItemWidth();

            if (t1 || t2 || t3 || t4 || t5 || t6)
            {
                checkShader();
            }
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 200));
    ImGui::SetNextWindowSize(ImVec2(300, 140));
    for (int i = 0; i < mmodel->meshes.size(); ++i)
    {
        Mesh &mesh = mmodel->meshes[i];
        Material &material = mesh.material;

        std::string windowTitle = "Material Settings for Mesh " + std::to_string(i);
        if (ImGui::Begin(windowTitle.c_str()))
        {
            bool t1 = ImGui::SliderFloat3("Ambient", &material.ambient[0], 0.0f, 1.0f);
            bool t2 = ImGui::SliderFloat3("Diffuse", &material.diffuse[0], 0.0f, 1.0f);
            bool t3 = ImGui::SliderFloat3("Specular", &material.specular[0], 0.0f, 1.0f);
            bool t4 = ImGui::SliderFloat("Shininess", &material.shininess, 16.0f, 256.0f);

            if (t1 || t2 || t3 || t4)
            {
                checkShader();
                pipeline->bind(mmodel);
            }

            if (material.texture)
            {
                ImGui::Text("Texture is set.");
                // 如果需要，你可以添加更多的代码来显示或修改纹理
            }
            else
            {
                ImGui::Text("No texture set.");
            }
        }
        ImGui::End();
    }
}

void MainWindow::show()
{
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

// 提供一些必要的信息给shader
// 还有部分信息由Model提供
void MainWindow::checkShader()
{
    // 通用的MVP变换
    pipeline->getShader()->setMatrix4f("projection", projection);
    pipeline->getShader()->setMatrix4f("view", view);
    pipeline->getShader()->setMatrix4f("model", model);
    pipeline->getShader()->setVec3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    if (lightEnable)
    {
        pipeline->getShader()->setVec3f("light.position", light.position);
        pipeline->getShader()->setVec3f("light.ambient", light.ambient);
        pipeline->getShader()->setVec3f("light.diffuse", light.diffuse);
        pipeline->getShader()->setVec3f("light.specular", light.specular);
    }
    else
    {
        pipeline->getShader()->setVec3f("light.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        pipeline->getShader()->setVec3f("light.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
        pipeline->getShader()->setVec3f("light.specular", glm::vec3(0.0f, 0.0f, 0.0f));
    }
    pipeline->getShader()->setVec3f("viewPos", cameraPos);
}