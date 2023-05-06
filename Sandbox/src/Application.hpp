#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();

    void Run();
    void Update();

private:
    GLFWwindow *mWindow;
};