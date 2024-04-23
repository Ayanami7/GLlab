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

    pipeline = new Pipeline();
    mmodel = new Model("../../resource/model/cow.obj");

    float aspect = static_cast<float>(width) / height;
    float near = 0.1f;  // 近裁剪面
    float far = 100.0f; // 远裁剪面
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, cameraDistance), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::mat4(1.0f);

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
        glEnable(GL_DEPTH_TEST);
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
