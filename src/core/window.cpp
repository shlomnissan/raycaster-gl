// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window.hpp"

#include <GLFW/glfw3.h>
#include <fmt/format.h>

constexpr auto callback_error =
[](int error, const char* message) {
    fmt::print("Error ({}): {}\n", error, message);
};

Window::Window(int width, int height, std::string_view title) {
    glfwSetErrorCallback(callback_error);

    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    if (window_ == nullptr) {
        glfwTerminate();
        return;
    }

     glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwSwapInterval(1);
    glfwSetWindowUserPointer(window_, this);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

auto Window::Start(const std::function<void(const double delta)> &program) -> void {
    auto last_frame = 0.0f;
    while(!glfwWindowShouldClose(window_)) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

        auto time = glfwGetTime();
        auto delta = time - last_frame;
        last_frame = time;

        program(delta);

        glfwSwapBuffers(window_);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

Window::~Window() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}