#include "Application.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <spdlog/spdlog.h>

#include <cstdlib>

Application::Application() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::exit(EXIT_FAILURE);
    }

#if defined(__APPLE__)
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

#define MODE 1

#if defined(MODE) && MODE == 1
    const auto monitor = glfwGetPrimaryMonitor();

    mWindow = glfwCreateWindow(1920, 1080, "Editor", monitor, nullptr);
#elif defined(MODE) && MODE == 2
    const auto monitor = glfwGetPrimaryMonitor();
    const auto mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    mWindow = glfwCreateWindow(mode->width, mode->height, "Editor", monitor, nullptr);
#elif defined(MODE) && MODE == 3
    mWindow = glfwCreateWindow(1280, 720, "Editor", nullptr, nullptr);
#endif
    if (mWindow == nullptr) {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Application::Run() {
    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Update();

        ImGui::Render();

        int display_w;
        int display_h;
        glfwGetFramebufferSize(mWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
    }
}

void Application::Update() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Clear Color", (float *) &mClearColor);
    ImGui::End();
}

void Application::glfw_error_callback(int error, const char *description) {
    spdlog::error("GLFW Error {}: {}\n", error, description);
}