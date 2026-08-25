#include "glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

// Fragment Shader
const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = ourColor;\n"
    "}\n\0";

int main()
{
    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with student's full name
    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Md. Shaad",
        NULL,
        NULL
    );

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create Shader Program
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // -------------------------------
    // Square + Triangle vertices
    // -------------------------------

    // Cyan square
    float squareVertices[] =
    {
        // First triangle
        -0.6f, -0.5f, 0.0f,
         0.6f, -0.5f, 0.0f,
         0.6f,  0.3f, 0.0f,

        // Second triangle
        -0.6f, -0.5f, 0.0f,
         0.6f,  0.3f, 0.0f,
        -0.6f,  0.3f, 0.0f
    };

    // Magenta triangle
    // Shares the two top corners of the square
    float triangleVertices[] =
    {
        -0.6f, 0.3f, 0.0f,
         0.6f, 0.3f, 0.0f,
         0.0f, 0.8f, 0.0f
    };

    unsigned int squareVAO, squareVBO;
    unsigned int triangleVAO, triangleVBO;

    // -------------------------------
    // Square VAO and VBO
    // -------------------------------

    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &squareVBO);

    glBindVertexArray(squareVAO);

    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(squareVertices),
        squareVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // -------------------------------
    // Triangle VAO and VBO
    // -------------------------------

    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(triangleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(triangleVertices),
        triangleVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Check keyboard input
        processInput(window);

        // White background
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        int vertexColorLocation =
            glGetUniformLocation(shaderProgram, "ourColor");

        // -------------------------------
        // Draw Cyan Square
        // -------------------------------

        glUniform4f(
            vertexColorLocation,
            0.0f, 1.0f, 1.0f, 1.0f
        );

        glBindVertexArray(squareVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // -------------------------------
        // Draw Magenta Triangle
        // -------------------------------

        glUniform4f(
            vertexColorLocation,
            1.0f, 0.0f, 1.0f, 1.0f
        );

        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete resources
    glDeleteVertexArrays(1, &squareVAO);
    glDeleteBuffers(1, &squareVBO);

    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);

    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}

// Close window when S is pressed
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// Resize callback
void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(0, 0, width, height);
}