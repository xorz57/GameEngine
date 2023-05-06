#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();

    void Run();

private:
    static void glfw_error_callback(int error, const char *description);

    GLFWwindow *window = nullptr;
};