#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    GLFWwindow* GetWindow();
    int GetWindowWidth();
    int GetWindowHeight();

private:
    GLFWwindow* window;
    int width, height;
    const char* title;
};
