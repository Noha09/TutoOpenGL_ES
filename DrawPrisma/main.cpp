#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <gl/glut.h> //No se usa

float rotationAngle = 0.0f;

void drawTriangularPrism()
{
    const float halfHeight = 0.5f;
    const float baseLength = 1.0f;

    glBegin(GL_TRIANGLES);

    // Definir vértices del prisma triangular
    GLfloat vertices[][3] = {
        // Cara frontal
        {0.0f, halfHeight, 0.0f},                       // Vértice superior
        {-baseLength / 2, -halfHeight, baseLength / 2}, // Vértice inferior izquierdo
        {baseLength / 2, -halfHeight, baseLength / 2},  // Vértice inferior derecho

        // Cara posterior
        {0.0f, halfHeight, 0.0f},                        // Vértice superior
        {baseLength / 2, -halfHeight, -baseLength / 2},  // Vértice inferior derecho
        {-baseLength / 2, -halfHeight, -baseLength / 2}, // Vértice inferior izquierdo

        // Cara inferior
        {-baseLength / 2, -halfHeight, baseLength / 2}, // Vértice inferior izquierdo
        {baseLength / 2, -halfHeight, baseLength / 2},  // Vértice inferior derecho
        {baseLength / 2, -halfHeight, -baseLength / 2}, // Vértice inferior derecho

        // Cara superior
        {0.0f, halfHeight, 0.0f},                        // Vértice superior
        {baseLength / 2, -halfHeight, -baseLength / 2},  // Vértice inferior derecho
        {-baseLength / 2, -halfHeight, -baseLength / 2}, // Vértice inferior izquierdo

        // Cara derecha
        {0.0f, halfHeight, 0.0f},                       // Vértice superior
        {baseLength / 2, -halfHeight, baseLength / 2},  // Vértice inferior derecho
        {baseLength / 2, -halfHeight, -baseLength / 2}, // Vértice inferior derecho

        // Cara izquierda
        {0.0f, halfHeight, 0.0f},                        // Vértice superior
        {-baseLength / 2, -halfHeight, -baseLength / 2}, // Vértice inferior izquierdo
        {-baseLength / 2, -halfHeight, baseLength / 2}   // Vértice inferior izquierdo
    };

    // Definir colores para cada vértice
    GLfloat colors[][3] = {
        {1.0f, 0.0f, 0.0f}, // Rojo
        {0.0f, 1.0f, 0.0f}, // Verde
        {0.0f, 0.0f, 1.0f}  // Azul
    };

    // Dibujar el prisma triangular
    for (int i = 0; i < 6; i += 3)
    {
        glBegin(GL_TRIANGLES);

        glColor3fv(colors[i / 3]);
        glVertex3fv(vertices[i]);

        glColor3fv(colors[i / 3 + 1]);
        glVertex3fv(vertices[i + 1]);

        glColor3fv(colors[i / 3 + 2]);
        glVertex3fv(vertices[i + 2]);
    }

    glEnd();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error al inicializar GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

        drawTriangularPrism();

        glfwSwapBuffers(window);

        glfwPollEvents();

        rotationAngle += 0.1f;
    }

    glfwTerminate();
    return 0;
}
