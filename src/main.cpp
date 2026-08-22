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

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    // Window name is student's full ID
    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Md.Shaad",
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

    /*
       Star made only with triangles.

       Each triangle uses the center point
       and two consecutive points of the star.
    */

    float vertices[] =
    {
        // Triangle 1
         0.0f,  0.0f, 0.0f,
         0.0f,  0.8f, 0.0f,
         0.235f, 0.323f, 0.0f,

        // Triangle 2
         0.0f,  0.0f, 0.0f,
         0.235f, 0.323f, 0.0f,
         0.761f, 0.247f, 0.0f,

        // Triangle 3
         0.0f,  0.0f, 0.0f,
         0.761f, 0.247f, 0.0f,
         0.380f, -0.123f, 0.0f,

        // Triangle 4
         0.0f,  0.0f, 0.0f,
         0.380f, -0.123f, 0.0f,
         0.470f, -0.647f, 0.0f,

        // Triangle 5
         0.0f,  0.0f, 0.0f,
         0.470f, -0.647f, 0.0f,
         0.0f, -0.400f, 0.0f,

        // Triangle 6
         0.0f,  0.0f, 0.0f,
         0.0f, -0.400f, 0.0f,
        -0.470f, -0.647f, 0.0f,

        // Triangle 7
         0.0f,  0.0f, 0.0f,
        -0.470f, -0.647f, 0.0f,
        -0.380f, -0.123f, 0.0f,

        // Triangle 8
         0.0f,  0.0f, 0.0f,
        -0.380f, -0.123f, 0.0f,
        -0.761f, 0.247f, 0.0f,

        // Triangle 9
         0.0f,  0.0f, 0.0f,
        -0.761f, 0.247f, 0.0f,
        -0.235f, 0.323f, 0.0f,

        // Triangle 10
         0.0f,  0.0f, 0.0f,
        -0.235f, 0.323f, 0.0f,
         0.0f, 0.8f, 0.0f
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Press S to close the window
        processInput(window);

        // Yellow background
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Cyan color
        int vertexColorLocation =
            glGetUniformLocation(shaderProgram, "ourColor");

        glUniform4f(
            vertexColorLocation,
            0.0f, 1.0f, 1.0f, 1.0f
        );

        // Draw star using triangles
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 30);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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