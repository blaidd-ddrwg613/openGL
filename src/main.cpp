#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Texture.h"
#include "Window.h"

void processInput(GLFWwindow* window);

float  mixValue = 0.2;

int main()
{

    Window window(1080, 720, "Learn OpenGL");

    // Create Our Default Shader Program
    Shader defaultShader(RESOURCES_PATH"shaders/default.vert", RESOURCES_PATH"shaders/default.frag");

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

    // Create VBO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute (Attribute we're defining) (# of elements) (type) (normalized) (stride) (offset)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture Coords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Texture texture1(RESOURCES_PATH"textures/container.jpg", false);
    Texture texture2(RESOURCES_PATH"textures/awesomeface.png", true);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    defaultShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(defaultShader.ID, "texture1"), 0);
    // or set it via the texture class
    defaultShader.setInt("texture2", 1);

    // print each row and col of the matrix
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            std::cout << trans[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

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
        glBindVertexArray(VAO);
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

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        mixValue < 0.0f ? mixValue = 0.0f : mixValue -= 0.0001f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        mixValue > 1.0f ? mixValue = 1.0f : mixValue += 0.0001f;
}