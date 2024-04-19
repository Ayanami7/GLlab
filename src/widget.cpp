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
    ImGui::Text("Current Bezier rank: %s", ranks[rankIndex]);
}

void MainWindow::settingWidget()
{
    if (ImGui::Begin("setting"))
    {
        if (ImGui::Combo("Combo", &rankIndex, ranks, IM_ARRAYSIZE(ranks)))
        {
            maxRank = rankIndex + 2;
            std::cout << "current:" << ranks[rankIndex] << std::endl;
        }
    }
    ImGui::End();
}

void MainWindow::show()
{
    vector<float> points = {0.1f, 0.1f, 0.0f,
                            0.3f, 0.5f, 0.0f,
                            0.7f, 0.7f, 0.0f,
                            1.9f, 0.3f, 0.0f};
    vector<float> vertices;

    float aspect = static_cast<float>(width) / height;
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 0.1f, 10.0f);
    
    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    float radius = 3.0f;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, radius), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);

    shader = new Shader("../../shader/Vertex.glsl", "../../shader/Fragment.glsl");
    shader->use();
    shader->setMatrix4f("projection", projection);
    shader->setMatrix4f("view", view);
    shader->setMatrix4f("model", model);

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

        // 计算并绘制贝塞尔曲线
        vertices.clear();
        bezierCurve(points, vertices, 0.01f);
        display(vertices);

        if (ImGui::IsMouseClicked(0))
        {
            ImVec2 pos = ImGui::GetMousePos();
            std::cout << "Mouse clicked Screen position: (" << pos.x << ", " << pos.y << ")" << std::endl;
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

void MainWindow::display(vector<float> vertices)
{
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

    glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 3);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}