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

    // 设置 ImGui 风格
    ImGui::StyleColorsDark();

    // 设置 ImGui 平台/渲染器绑定
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //初始化VAO VBO
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO3D);
    glGenVertexArrays(1, &VAO3D);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // 加载着色器
    shader = new Shader("../../shader/default_vert.glsl", "../../shader/default_frag.glsl");

    // 初始化贝塞尔曲线控制点
    c_points = {-500.0f, -200.0f, 0.0f,
                -300.0f, 200.0f, 0.0f,
                -100.0f, -200.0f, 0.0f,
                0.0f, 200.0f, 0.0f,
                100.0f, -200.0f, 0.0f,
                300.0f, 200.0f, 0.0f,
                500.0f, -200.0f, 0.0f};

    c_points3D = {
        {-1.0f, -1.0f, +1.5f, -0.5f, 0.0f, +1.5f, +0.5f, 0.0f, +1.5f, +1.0f, 0.0f, +1.5f},
        {-1.5f, 0.0f, +0.5f, -0.5f, 0.0f, +0.5f, +0.5f, 2.0f, +0.5f, +1.5f, 0.0f, +0.5f},
        {-1.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, +0.5f, 0.0f, -0.5f, +1.5f, 0.0f, -0.5f},
        {-1.0f, 1.0f, -1.5f, -0.5f, 0.0f, -1.5f, +0.5f, 0.0f, -1.5f, +2.5f, 1.0f, -1.5f}};

    // 初始化视图矩阵
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, distance), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::ortho(-width / 2 * 1.0f, width / 2 * 1.0f, -height / 2 * 1.0f, height / 2 * 1.0f, 0.1f, 10.0f);

    // 启用shader
    shader->use();
    shader->setMatrix4f("projection", projection);
    shader->setMatrix4f("view", view);
    shader->setMatrix4f("model", model);
}

void MainWindow::destroy()
{
    // 清理着色器
    delete shader;
    // 销毁缓冲
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO3D);
    glDeleteBuffers(1, &VBO3D);
    // 清理 ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // 清理 GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}

void MainWindow::show()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 清除颜色缓冲区
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 开始新的 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (bezierIndex == BEZIER_LINE)
        {
            render1();
        }
        else if (bezierIndex == BEZIER_SURFACE)
        {
            render2();
        }

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

void MainWindow::debugWidget()
{
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    ImGui::Text("This is a test.");
    ImGui::Text("Framebuffer size: %d x %d", w, h);
    ImGui::Text("Current Bezier rank: %s", ranks[rankIndex]);
    ImGui::Text("Current Display type: %s", bezierTypes[bezierIndex]);
}

void MainWindow::settingWidget()
{
    if (ImGui::Begin("setting"))
    {
        ImGui::PushItemWidth(100); // 设置接下来的控件宽度为100
        // 设置阶数
        ImGui::Combo("Bezier Ranks", &rankIndex, ranks, IM_ARRAYSIZE(ranks));
        if (ImGui::Combo("Display Status", &bezierIndex, bezierTypes, IM_ARRAYSIZE(bezierTypes)))
        {
            switchType();
        }
        ImGui::PopItemWidth(); // 恢复之前的宽度

        ImGui::PushItemWidth(120); // 设置接下来的控件宽度为120
        // 设置视野范围
        if (ImGui::SliderFloat("fov", &fov, 30.0f, 120.0f))
        {
            switchType();
        }
        ImGui::PopItemWidth(); // 恢复之前的宽度

    }// end setting
    ImGui::End();
}

void MainWindow::render1()
{
    for (int i = 0; i < rankIndex + 3; i++)
    {
        drawCircle(c_points[i * 3], c_points[i * 3 + 1], 8.0f, 16);
    }

    // 绑定信息
    vbuffer.clear();
    bezierCurve(c_points, rankIndex + 3, vbuffer, 0.02f); // 50步进

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vbuffer.size(), vbuffer.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 绘制
    glDrawArrays(GL_LINE_STRIP, 0, (int)vbuffer.size() / 3);

    // 鼠标处理
    if (ImGui::IsMouseClicked(0) && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
    {
        ImVec2 pos = ImGui::GetMousePos();
        screenToViewport(pos.x, pos.y, width * 1.0f, height * 1.0f);

        // 检查鼠标点击的位置是否在点的范围内
        for (int i = 0; i < rankIndex + 3; i++)
        {
            if (insideCircle(pos.x, pos.y, c_points[i * 3], c_points[i * 3 + 1], 8.0f))
            {
                draggingIndex = i;
                break;
            }
        }
    }
    else if (ImGui::IsMouseDragging(0) && draggingIndex != -1)
    {
        // 如果正在拖动就更新
        ImVec2 pos = ImGui::GetMousePos();
        screenToViewport(pos.x, pos.y, width * 1.0f, height * 1.0f);
        c_points[draggingIndex * 3] = pos.x;
        c_points[draggingIndex * 3 + 1] = pos.y;
    }
    else if (ImGui::IsMouseReleased(0))
    {
        // 如果鼠标被释放，停止拖动
        draggingIndex = -1;
    }
}

void MainWindow::render2()
{
    // 计算量非常大，只在变化时计算
    if(modfiy3D)
    {
        for (float u = 0; u <= 1 - 0.02f; u += 0.02f)
        {
            for (float v = 0; v <= 1 - 0.02f; v += 0.02f)
            {
                std::vector<std::vector<float>> quadVertices;
                for (int du = 0; du <= 1; ++du)
                {
                    for (int dv = 0; dv <= 1; ++dv)
                    {
                        float x = 0.0f, y = 0.0f, z = 0.0f;
                        for (int i = 0; i < 4; ++i)
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                float basis = combination(3, i) * std::pow(1 - (u + du * 0.02f), 3 - i) * std::pow(u + du * 0.02f, i) * combination(3, j) * std::pow(1 - (v + dv * 0.02f), 3 - j) * std::pow(v + dv * 0.02f, j);
                                x += basis * c_points3D[i][3 * j];
                                y += basis * c_points3D[i][3 * j + 1];
                                z += basis * c_points3D[i][3 * j + 2];
                            }
                        }
                        quadVertices.push_back({x, y, z});
                    }
                }
                // Add two triangles forming the quad
                vbuffer3D.insert(vbuffer3D.end(), quadVertices[0].begin(), quadVertices[0].end());
                vbuffer3D.insert(vbuffer3D.end(), quadVertices[1].begin(), quadVertices[1].end());
                vbuffer3D.insert(vbuffer3D.end(), quadVertices[2].begin(), quadVertices[2].end());

                vbuffer3D.insert(vbuffer3D.end(), quadVertices[2].begin(), quadVertices[2].end());
                vbuffer3D.insert(vbuffer3D.end(), quadVertices[1].begin(), quadVertices[1].end());
                vbuffer3D.insert(vbuffer3D.end(), quadVertices[3].begin(), quadVertices[3].end());
            }
        }

        glBindVertexArray(VAO3D);
        glBindBuffer(GL_ARRAY_BUFFER, VBO3D);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vbuffer3D.size(), vbuffer3D.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        modfiy3D = false;
    }

    // 绘制线框图
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, (int)vbuffer3D.size() / 3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (ImGui::IsMouseDragging(0)) // 0 是左键，1 是右键
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
        shader->setMatrix4f("model", model);
    }
    // 获取ImGui的IO对象
    ImGuiIO &io = ImGui::GetIO();
    // 如果滚轮有滚动
    if (io.MouseWheel != 0)
    {
        distance -= io.MouseWheel * zoom_speed;
        view = glm::mat4(1.0f);
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, distance), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader->setMatrix4f("view", view);
    }
}

void MainWindow::switchType()
{
    if (bezierIndex == BEZIER_LINE)
    {
        projection = glm::ortho(-width / 2 * 1.0f, width / 2 * 1.0f, -height / 2 * 1.0f, height / 2 * 1.0f, 0.1f, 10.0f);
        model = glm::mat4(1.0f);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindVertexArray(VAO);
    }
    else if (bezierIndex == BEZIER_SURFACE)
    {
        float aspect = float(width) / float(height); // 宽高比
        float near = 0.1f;                           // 近裁剪面
        float far = 100.0f;                          // 远裁剪面
        projection = glm::perspective(glm::radians(fov), aspect, near, far);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO3D);
        glBindVertexArray(VAO3D);
    }
    shader->setMatrix4f("projection", projection);
    shader->setMatrix4f("model", model);
}

void MainWindow::drawCircle(float x, float y, float radius, int nums)
{
    vbuffer.clear();
    vbuffer.push_back(x); // center x
    vbuffer.push_back(y); // center y

    for (int i = 0; i <= nums; ++i)
    {
        vbuffer.push_back(x + (radius * cos(i * 2.0f * 3.14f / nums)));
        vbuffer.push_back(y + (radius * sin(i * 2.0f * 3.14f / nums)));
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, vbuffer.size() * sizeof(float), &vbuffer[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, nums + 2);
}