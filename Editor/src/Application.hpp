#pragma once

#include <imgui.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();

    void Run();
    void Update();

private:
    static void glfw_error_callback(int error, const char *description);

    GLFWwindow *mWindow{nullptr};
    ImVec4 mClearColor{0.45f, 0.55f, 0.60f, 1.00f};
};