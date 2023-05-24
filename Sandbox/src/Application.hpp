#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();

    Application(const Application &) = delete;
    Application(Application &&) = delete;

    Application& operator=(const Application &) = delete;
    Application& operator=(Application &&) = delete;

    void Run();
    void Update();

private:
    GLFWwindow *mWindow;
};