#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <openglErrorReporting.h>

#include <iostream>

static void error_callback(int error, const char *description)
{
    std::cout << "Error: " <<  description << "\n";
}

void printMessage(std::string message)
{
    std::cout << message << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);


int main()
{
    glfwSetErrorCallback(error_callback);

    // Init GLFW
    if (!glfwInit())
        return -1;

    // Set GLFW Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the GLFW Window Object
    GLFWwindow* window = glfwCreateWindow(1080, 720, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printMessage("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Init GLAD Before we call any OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printMessage("Failed to initialize GLAD");
        return -1;
    }

    // Set the viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Application Loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // Rendering


        // Check and Call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}