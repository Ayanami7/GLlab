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
    // 清理 ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // 清理 GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
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
        // 设置显示类型
        if (ImGui::Combo("Display Status", &bezierIndex, bezierTypes, IM_ARRAYSIZE(bezierTypes)))
        {
            if (bezierIndex == BEZIER_LINE)
            {
                projection = glm::ortho(-width / 2 * 1.0f, width / 2 * 1.0f, -height / 2 * 1.0f, height / 2 * 1.0f, 0.1f, 10.0f);
            }
            else if (bezierIndex == BEZIER_SURFACE)
            {
                float aspect = float(width) / float(height); // 宽高比
                float near = 0.1f;                           // 近裁剪面
                float far = 100.0f;                          // 远裁剪面
                projection = glm::perspective(glm::radians(fov), aspect, near, far);
            }
            shader->setMatrix4f("projection", projection);
        }
        ImGui::PopItemWidth(); // 恢复之前的宽度

        ImGui::PushItemWidth(120); // 设置接下来的控件宽度为120
        // 设置相机距离
        if (ImGui::SliderFloat("Camera Distance", &distance, 0.2f, 10.0f))
        {
            // 创建一个滑动条，范围从0.2到10
            view = glm::mat4(1.0f);
            view = glm::lookAt(glm::vec3(0.0f, 0.0f, distance), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shader->setMatrix4f("view", view);
        }
        // 设置视野范围
        if (ImGui::SliderFloat("fov", &fov, 30.0f, 120.0f))
        {
            if (bezierIndex == BEZIER_LINE)
            {
                projection = glm::ortho(-width / 2 * 1.0f, width / 2 * 1.0f, -height / 2 * 1.0f, height / 2 * 1.0f, 0.1f, 10.0f);
            }
            else if (bezierIndex == BEZIER_SURFACE)
            {
                float aspect = float(width) / float(height); // 宽高比
                float near = 0.1f;                           // 近裁剪面
                float far = 100.0f;                          // 远裁剪面
                projection = glm::perspective(glm::radians(fov), aspect, near, far);
            }
            shader->setMatrix4f("projection", projection);
        }
        ImGui::PopItemWidth(); // 恢复之前的宽度

        ImGui::PushItemWidth(180); // 设置接下来的控件宽度为120
        // 创建滑块
        if (ImGui::SliderFloat("Rotation X", &rotationX, -180.0f, 180.0f) ||
            ImGui::SliderFloat("Rotation Y", &rotationY, -180.0f, 180.0f) ||
            ImGui::SliderFloat("Rotation Z", &rotationZ, -180.0f, 180.0f))
        {
            // 计算旋转矩阵
            model = glm::mat4(1.0f);
            if (bezierIndex == BEZIER_LINE)
            {
                ;
            }
            else if (bezierIndex == BEZIER_SURFACE)
            {
                model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::rotate(model, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
            }
            shader->setMatrix4f("model", model);
        }
        ImGui::PopItemWidth(); // 恢复之前的宽度

    }// end setting
    ImGui::End();
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

void MainWindow::render1()
{
    // 绘制控制点
    for (int i = 0; i < rankIndex + 3; i++)
    {
        drawCircle(c_points[i * 3], c_points[i * 3 + 1], 8.0f, 16);
    }
    // 计算并绘制贝塞尔曲线
    std::vector<float> vertices;
    bezierCurve(c_points, rankIndex + 3, vertices, 0.02f); // 50步进

    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 上传顶点数据到VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    // 指定顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINE_STRIP, 0, (int)vertices.size() / 3);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
    std::vector<std::vector<float>> controlPoints = {
        {-1.0f, -1.0f, +1.5f, -0.5f, 0.0f, +1.5f, +0.5f, 0.0f, +1.5f, +1.0f, 0.0f, +1.5f},
        {-1.5f, 0.0f, +0.5f, -0.5f, 0.0f, +0.5f, +0.5f, 2.0f, +0.5f, +1.5f, 0.0f, +0.5f},
        {-1.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, +0.5f, 0.0f, -0.5f, +1.5f, 0.0f, -0.5f},
        {-1.0f, 1.0f, -1.5f, -0.5f, 0.0f, -1.5f, +0.5f, 0.0f, -1.5f, +2.5f, 1.0f, -1.5f}};

    std::vector<float> vertices;
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
                            x += basis * controlPoints[i][3 * j];
                            y += basis * controlPoints[i][3 * j + 1];
                            z += basis * controlPoints[i][3 * j + 2];
                        }
                    }
                    quadVertices.push_back({x, y, z});
                }
            }
            // Add two triangles forming the quad
            vertices.insert(vertices.end(), quadVertices[0].begin(), quadVertices[0].end());
            vertices.insert(vertices.end(), quadVertices[1].begin(), quadVertices[1].end());
            vertices.insert(vertices.end(), quadVertices[2].begin(), quadVertices[2].end());

            vertices.insert(vertices.end(), quadVertices[2].begin(), quadVertices[2].end());
            vertices.insert(vertices.end(), quadVertices[1].begin(), quadVertices[1].end());
            vertices.insert(vertices.end(), quadVertices[3].begin(), quadVertices[3].end());
        }
    }

    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 上传顶点数据到VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    // 指定顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size() / 3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void MainWindow::drawCircle(float x, float y, float radius, int nums)
{
    std::vector<float> vertexData;
    vertexData.push_back(x); // center x
    vertexData.push_back(y); // center y

    for (int i = 0; i <= nums; ++i)
    {
        vertexData.push_back(x + (radius * cos(i * 2.0f * 3.14f / nums)));
        vertexData.push_back(y + (radius * sin(i * 2.0f * 3.14f / nums)));
    }

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, nums + 2);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}