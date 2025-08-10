#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <openglErrorReporting.h>

#include <iostream>
#include <cmath>

#include "Shader.h"


static void error_callback(int error, const char *description)
{
    std::cout << "Error: " <<  description << "\n";
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
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    // Create the GLFW Window Object
    GLFWwindow* window = glfwCreateWindow(1080, 720, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Init GLAD Before we call any OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create Our Default Shader Program
    Shader defaultShader(RESOURCES_PATH"shaders/default.vert", RESOURCES_PATH"shaders/default.frag");

    // Triangle vertices
    float vertices[] =
            {
            //  Position(X,Y,Z)             // Colors(R,G,B)
            -0.5f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,0.0f, 0.0f, 1.0f
            };

    // Create VBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute (Attribute we're defining) (# of elements) (type) (normalized) (stride) (offset)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Application Loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // Rendering
        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Enable Shader Program
        defaultShader.use();

        // Renders The Triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and Call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void getMaxAttributes()
{
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "GL_MAX_VERTEX_ATTRIBS: " << attributes << std::endl;
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