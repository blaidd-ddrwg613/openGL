#include "Window.h"

int Window::width, Window::height;

Window::Window(int width, int height, const char* title)
{
    Window::width = width;
    Window::height = height;

    if (!glfwInit())
    {
        std::cout << "ERROR::FAILED TO INIT GLFW" << std::endl;
    }

    // Set GLFW Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Init GLAD Before we call any OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::GetWindow()
{
    return window;
}

int Window::GetWindowWidth()
{
    return width;
}

int Window::GetWindowHeight()
{
    return height;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

