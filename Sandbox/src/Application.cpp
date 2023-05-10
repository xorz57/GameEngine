#include "Application.hpp"

#include <cstdlib>

#define MODE 1

Application::Application() {
    if (!glfwInit()) {
        std::exit(EXIT_FAILURE);
    }

#if defined(__APPLE__)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

#if defined(MODE) && MODE == 1
    const auto monitor = glfwGetPrimaryMonitor();

    mWindow = glfwCreateWindow(1280, 720, "Sandbox", monitor, nullptr);
#elif defined(MODE) && MODE == 2
    const auto monitor = glfwGetPrimaryMonitor();
    const auto mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    mWindow = glfwCreateWindow(mode->width, mode->height, "Sandbox", monitor, nullptr);
#elif defined(MODE) && MODE == 3
    mWindow = glfwCreateWindow(1280, 720, "Sandbox", nullptr, nullptr);
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