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

float  mixValue = 0.2;

int main()
{
    Window window(1080, 720, "Learn OpenGL");

    // Create Our Default Shader Program
    Shader defaultShader(RESOURCES_PATH"shaders/default.vert", RESOURCES_PATH"shaders/default.frag");
    Texture texture1(RESOURCES_PATH"textures/container.jpg", false);
    Texture texture2(RESOURCES_PATH"textures/awesomeface.png", true);

    // Triangle vertices
    float vertices[] = {
            // positions          // colors           // texture coords
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

    // Application Loop
    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        // input
        processInput(window.GetWindow());

        // Rendering
        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Setting Textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.ID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.ID);

        defaultShader.use();
        defaultShader.setFloat("mixValue", mixValue);
//        defaultShader.setFloat("offset", sin(glfwGetTime()));

        // Identity matrix
        glm::mat4 trans = glm::mat4(1.0f);
        // Move the rectangle to the bottom right
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        // Rotate the rectangle over time  along the z axis
        trans = glm::rotate(trans,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
        // Scale the rectangle in half
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

        unsigned int transformLoc = glGetUniformLocation(defaultShader.ID, "transform");
        // (1. uniform Loctaion) (2. # of Matricies we want to send) (3. transpose the matrix (no need with GLM)
        // (4. Matrix Data (GLM stores their matrices' data in a way that doesn't always match OpenGL's expectations,
        // so we first convert the data with GLM's built-in function value_ptr.)
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // Render Triangle
        VAO1.Bind();
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // second transformation
        // ---------------------
        trans = glm::mat4(1.0f); // reset it to identity matrix
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = static_cast<float>(sin(glfwGetTime()));
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value

        // now with the uniform matrix being replaced with new transformations, draw it again.
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

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        mixValue < 0.0f ? mixValue = 0.0f : mixValue -= 0.0001f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        mixValue > 1.0f ? mixValue = 1.0f : mixValue += 0.0001f;
}