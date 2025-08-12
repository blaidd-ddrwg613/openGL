#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void processInput(GLFWwindow* window);



int main()
{
    Window window(1080, 720, "Learn OpenGL");

    std::cout << "Width: " << window.GetWindowWidth() << " Height: " << window.GetWindowHeight() << std::endl;

    Shader defaultShader(RESOURCES_PATH"shaders/default.vert", RESOURCES_PATH"shaders/default.frag");
    Texture texture1(RESOURCES_PATH"textures/container.jpg", false);
    Texture texture2(RESOURCES_PATH"textures/awesomeface.png", true);

    // Rectangle vertices
    float vertices[] = {
            // positions          // Color           // texture coords
            0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,0.0f, 0.0f, 1.0f,0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,1.0f, 1.0f, 0.0f,0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    defaultShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(defaultShader.ID, "texture1"), 0);
    // or set it via the texture class
    defaultShader.setInt("texture2", 1);

    // Setting Textures
    texture1.UseTexture(GL_TEXTURE0, texture1.ID);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture1.ID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2.ID);

    // Application Loop
    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        // input
        processInput(window.GetWindow());

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set Some Shader Uniforms
        defaultShader.use();

        // Matrices
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection;

        // Matrix Transformations
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3 (0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)(window.GetWindowWidth() / window.GetWindowHeight()), 0.1f, 100.0f);


        unsigned int transformLoc = glGetUniformLocation(defaultShader.ID, "transform");
        int modelLoc = glGetUniformLocation(defaultShader.ID, "model");
        int viewLoc = glGetUniformLocation(defaultShader.ID, "view");
        int projectionLoc = glGetUniformLocation(defaultShader.ID, "projection");

        // (1. uniform Loctaion) (2. # of Matricies we want to send) (3. transpose the matrix (no need with GLM)
        // (4. Matrix Data (GLM stores their matrices' data in a way that doesn't always match OpenGL's expectations,
        // so we first convert the data with GLM's built-in function value_ptr.)
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Render Triangle
        VAO1.Bind();
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and Call events and swap the buffers
        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}