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

    glEnable(GL_DEPTH_TEST);

    std::cout << "Width: " << window.GetWindowWidth() << " Height: " << window.GetWindowHeight() << std::endl;

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

    float vertices_Cube[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
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

    // Cube Render
    VAO VAO_Cube;
    VAO_Cube.Bind();

    VBO VBO_Cube(vertices_Cube, sizeof(vertices_Cube));
    VAO_Cube.LinkAttrib(VBO_Cube, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO_Cube.LinkAttrib(VBO_Cube, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO_Cube.Unbind();
    VBO_Cube.Unbind();

    Shader defaultShader(RESOURCES_PATH"shaders/default.vert", RESOURCES_PATH"shaders/default.frag");
    Texture containerTexture(RESOURCES_PATH"textures/container.jpg", false);
    Texture awesomeTexture(RESOURCES_PATH"textures/awesomeface.png", true);
    defaultShader.use();

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    defaultShader.setInt("texture1", 0);
    defaultShader.setInt("texture2", 1);
    defaultShader.setVec3("color", 0.5, 0.4, 0.7);
    defaultShader.setFloat("alpha", 0.2);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, containerTexture.ID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, awesomeTexture.ID);

    float fov = 45;
//    auto aspect = (float)(window.GetWindowWidth() / window.GetWindowHeight());
    float aspect = 1.5;
    float zNear = 0.1f;
    float zFar = 100.0f;

    // Application Loop
    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        // input
        processInput(window.GetWindow());

        if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            if (fov > 180.0f)
            {
                fov = 180.0f;
            }
            fov += 0.05f;
        }
        if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            if (fov < 45.0f)
            {
                fov = 45.0f;
            }
            fov -= 0.05f;
        }

        std::cout << "FOV: " << fov << std::endl;

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set Some Shader Uniforms
        defaultShader.use();

        // Matrices
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection;

        // Matrix Transformations
//        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3 (0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(fov), aspect , zNear, zFar);

        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

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
//        VAO1.Bind();
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        VAO_Cube.Bind();
        for (auto i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            defaultShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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