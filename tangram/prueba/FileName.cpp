#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"

"out vec3 ourColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);\n"
"}\n\0";


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Recorrido Virtual Horror Fest", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.25f,  0.5f, 0.0f,  // top right
         0.25f, -0.5f, 0.0f,  // bottom right
        -0.25f, -0.5f, 0.0f,  // bottom left
        -0.25f,  0.5f, 0.0f,   // top left 
        -0.7f,  -0.5f, 0.0f,  // top right
        -0.25f,   0.5f, 0.0f,  // bottom right
    };

    float vertices2[] = {
        0.0f,  0.0f, 0.0f,  0.662, 0.611, 0.415,
       -0.2f, -0.5f, 0.0f,  0.662, 0.611, 0.415,  // t1
        0.2f, -0.5f, 0.0f,  0.662, 0.611, 0.415,

       0.0f,  0.0f, 0.0f,   0.874, 0.211, 0.149,
       0.2f, -0.5f, 0.0f,     0.874, 0.211, 0.149, //T2
       0.4f,  0.1f, 0.0f,  0.874, 0.211, 0.149,

        0.0f,  0.0f, 0.0f,   0.909, 0.431, 0.129,
        -0.2f, -0.5f, 0.0f,     0.909, 0.431, 0.129, //t3
        -0.4f,  0.1f, 0.0f,  0.909, 0.431, 0.129,

        0.0f,  0.0f, 0.0f,  0.368, 0.858, 0.301,
        0.4f,  0.1f, 0.0f,  0.368, 0.858, 0.301, //t4
        0.0f,  0.5f, 0.0f,  0.368, 0.858, 0.301,

        0.0f,  0.0f, 0.0f,   0.894, 0.858, 0.227,
        -0.4f,  0.1f, 0.0f,  0.894, 0.858, 0.227,  //T5
        0.0f,  0.5f, 0.0f,   0.894, 0.858, 0.227,

    };

    float vertices3[] = {
        
        //0.5f,  0.5f, 0.0f, // top right 0
        // 0.5f, -0.5f, 0.0f, // bottom right 1
        //-0.5f, -0.5f, 0.0f, // bottom left 2
        //-0.5f,  0.5f, 0.0f, // top left  3
        //0.0f,  -0.5f, 0.0f, // top right 4
        //

        //amarrillo
        -0.0f,-0.4f,0.0f,    0.976, 1, 0.101,      // 0
        0.50f, -0.4f, 0.0f,     0.976, 1, 0.101,    // 1
        0.20f, 0.4f, 0.0f,    0.976, 0, 1,      // 2 primer triangulo***

        //verde
        0.10f, 0.4f, 0.0f,     0.10, 0.643, 0.254,        // 3
        0.60f, 0.4f, 0.0f,    0.10, 0, 0.254,          // 4
        -0.20f,  0.8f, 0.0f,    0.10, 0.64, 0.254,          // 5


        -0.10f,  0.0f, 0.0f,       1, 1, 0,        // 6
        -0.15f,  -0.8f, 0.0f,     1, 1, 0,        // 7
        0.20f,  -1.0f, 0.0f,      1, 0, 0,        // 8

        0.10f,  0.0f, 0.0f,      0.474, 0.207, 0.207,
       0.15f,  0.3f, 0.0f,     0.474, 1, 0.207,
        -0.20f, 0.3f, 0.0f,        0.474, 0.207, 0.207,


        0.35f,  0.0f, 0.0f,       1, 1, 0,        // 6
       0.35f,  0.9f, 1.0f,     1, 1, 0,        // 7
        0.45f,  0.8f, -0.10f,      1, 0, 0,        // 8



        //-0.10f,  0.0f, 0.0f,       1, 0, 0,        // 6
        //-0.15f,  -0.8f, 0.0f,     1, 0, 1,        // 7
        //0.80f,  -1.0f, 0.0f,      1, 0, 1,        // 8
        -1.0f,   0.5f, 0.0f,  // bottom right 5
    };
    unsigned int indices2[] = {  // note that we start from 0!
        0, 1, 2,  // first Triangle
        4, 3, 5,   // second Triangle
        6, 8, 7,   // third Triangle
        9, 10, 11   // fourth Triangle
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        2, 1, 3,   // second Triangle

        2, 4, 5,   // third Triangle
        //  5, 4, 2   // fourth Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //N?mero de elementos // referencia al buffer
    glGenBuffers(1, &EBO);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Column Major
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glLineWidth(20.0);
        glPointSize(20.0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 15);
        //glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}