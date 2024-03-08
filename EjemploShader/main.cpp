#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3dll.lib")

#define _USE_MATH_DEFINES

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void create(GLuint VAOs[], int index)
{
    glBindVertexArray(VAOs[index]);
    glBindBuffer(GL_ARRAY_BUFFER, VAOs[index]);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);
}

float vertices[] = {
    // positions
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f};

void rotation(float angle, int eje)
{
    float vcos = (float)(cos(angle * M_PI / 180.0));
    float vsin = (float)(sin(angle * M_PI / 180.0));
    float matrot[3][3];

    if (eje == 1)
    {
        matrot[0][0] = 1;
        matrot[0][1] = 0;
        matrot[0][2] = 0;
        matrot[1][0] = 0;
        matrot[1][1] = vcos;
        matrot[1][2] = vsin;
        matrot[2][0] = 0;
        matrot[2][1] = -vsin;
        matrot[2][2] = vcos;
    }
    else if (eje == 2)
    {
        matrot[0][0] = vcos;
        matrot[0][1] = 0;
        matrot[0][2] = vsin;
        matrot[1][0] = 0;
        matrot[1][1] = 1;
        matrot[1][2] = 0;
        matrot[2][0] = vsin;
        matrot[2][1] = 0;
        matrot[2][2] = vcos;
    }
    else
    {
        matrot[0][0] = vcos;
        matrot[0][1] = vsin;
        matrot[0][2] = 0;
        matrot[1][0] = -vsin;
        matrot[1][1] = vcos;
        matrot[1][2] = 0;
        matrot[2][0] = 0;
        matrot[2][1] = 0;
        matrot[2][2] = 1;
    }

    for (int i = 0; i < 6; i++)
    {
        float p[3];
        float pr[3];

        p[0] = vertices[i * 3 + 0];
        p[1] = vertices[i * 3 + 1];
        p[2] = vertices[i * 3 + 2];

        pr[0] = p[0] * matrot[0][0] + p[1] * matrot[1][0] + p[2] * matrot[2][0];
        pr[1] = p[0] * matrot[0][1] + p[1] * matrot[1][1] + p[2] * matrot[2][1];
        pr[2] = p[0] * matrot[0][2] + p[1] * matrot[1][2] + p[2] * matrot[2][2];

        vertices[i * 3 + 0] = pr[0];
        vertices[i * 3 + 1] = pr[1];
        vertices[i * 3 + 2] = pr[2];
    }
}

int main(void)
{
    GLFWwindow *window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context

    window = glfwCreateWindow(640, 480, "Me Quiero Morir", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    glClearColor(0.35, 0.3, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Funcion de rotacion
    // rotation(45.0, 1);
    // rotation(45.0, 2);
    rotation(45.0, 3);

    float colors[] = {
        // colors
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f};
    float texcoords[] = {
        // texture coords
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // using separated buffers
    // GLuint  equivalent to unsigned int
    // vertex buffer objects, vertex array object, element buffer object, color buffer object , texture buffer objects
    GLuint VBO, VAO, EBO, CBO, TBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &CBO);
    glGenBuffers(1, &TBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); // Array for buffers

    // binf data for buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // index in shader, size, type,  normalized?,  stride ,      array buffer offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    // 3er attribute buffer : texcoords
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    ///////////Prepare the shader ////////////

    std::string vertexShader =
        // Vertex Shader
        "#version 330 core\n"
        "uniform float transition;"
        "layout(location = 0) in vec3 aPos;"
        "layout(location = 1) in vec3 aColor;"
        "out vec4 ourColor;"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos, 1.0); "
        " ourColor = vec4(aColor, 1.0); "
        "}\n";

    std::string fragmentShader =
        // Fragment Shader
        "#version 330 core\n"
        "uniform float transition;"
        "out vec4 FragColor;"
        "in vec4 ourColor;"
        "void main()\n"
        "{\n"
        "  FragColor = mix(ourColor, vec4(1.0, 1.0, 1.0, 1.0), transition);"
        "}\n";

    //------------GUIA DE SHADERS-------------
    // see https://thebookofshaders.com/
    float transitionValue = 0.0f;

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    int transitionLoc = glGetUniformLocation(shader, "transition");

    while (!glfwWindowShouldClose(window))
    {
        // Limpia el búfer de color y profundidad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Incrementa el valor de la transición (ajusta la velocidad según sea necesario)
        transitionValue += 0.01f;

        // Si la transición ha alcanzado su máximo, reiníciala a cero
        if (transitionValue > 1.0f)
            transitionValue = 0.0f;

        // Asigna el valor de la transición a la variable uniforme en el shader
        glUniform1f(transitionLoc, transitionValue);

        // Renderiza tu objeto
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Intercambia los búferes frontal y trasero
        glfwSwapBuffers(window);

        // Poll para eventos y actualizaciones
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
