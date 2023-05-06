#include "Application.hpp"

#include <cstdlib>

Application::Application() {
    if (!glfwInit()) {
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    mWindow = glfwCreateWindow(1280, 720, "Sandbox", nullptr, nullptr);
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
}

Application::~Application() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Application::Run() {
    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();

        Update();

        int display_w;
        int display_h;
        glfwGetFramebufferSize(mWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mWindow);
    }
}

void Application::Update() {
    // ...
}