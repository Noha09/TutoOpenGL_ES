#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3dll.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
    GLFWwindow* window;

    // Inicializar la librería
    if (!glfwInit())
    {
        return -1;
    }

    // Crear una ventana en modo ventana y su contexto OpenGL
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Me Quiero Morir", NULL, NULL);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Actualizar el contexto de la ventana
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // Especifica la parte de la ventana en la que OpenGL dibujará (en píxeles), convertir de normalizado a píxeles
    glMatrixMode(GL_PROJECTION); // La matriz de proyección define las propiedades de la cámara que ve los objetos en el marco de coordenadas mundo. Aquí se suele definir el factor de zoom, la relación de aspecto y los planos de recorte cercano y lejano.
    glLoadIdentity(); // Reemplaza la matriz actual con la matriz identidad y nos inicia de nuevo porque las transformaciones matriciales como glOrpho y glRotate se acumulan, básicamente nos pone en (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 600); // sistema de coordenadas esencialmente fijado
    glMatrixMode(GL_MODELVIEW); // (modo matricial por defecto) La matriz modelview define cómo se transforman tus objetos (es decir, traslación, rotación y escalado) en tu mundo
    glLoadIdentity(); // Lo mismo que el comentario anterior

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

    GLfloat halfSideLength = 200;

    // Dibujando un triangulo (creo)
    GLfloat vertices[] =
    {
        halfScreenWidth, halfScreenHeight + halfSideLength, 0.0, // Vértice superior central
        halfScreenWidth - halfSideLength, halfScreenHeight - halfSideLength, 0.0, // Esquina inferior izquierda
        halfScreenWidth + halfSideLength, halfScreenHeight - halfSideLength, 0.0 // Esquina inferior derecha
    };

    GLfloat colour[] =
    {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    // Bucle hasta que el usuario cierre la ventana
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderizar OpenGL aquí
        glEnableClientState(GL_VERTEX_ARRAY); // Indica a OpenGL que está utilizando una matriz de vértices para el atributo de función fija
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices); // Apuntan a los vértices que se van a utilizar
        glColorPointer(3, GL_FLOAT, 0, colour);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Dibuja los vértices
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY); // Indica a OpenGL que ha terminado de utilizar el atributo de matriz de vértices

        // Intercambiar los búferes delantero y trasero
        glfwSwapBuffers(window);

        // Sondear y procesar eventos
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}