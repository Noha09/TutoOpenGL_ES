#pragma comment(lib, "glew32s.lib") // Nota: Estas lineas del codigo son importantes para que compile el proyecto
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3dll.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
    GLFWwindow *window;

    // Inicializar la libreria
    if (!glfwInit())
    {
        return -1;
    }

    // Creamos una ventana en el contexto de OpenGL
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Me Quiero Morir", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Actualizar el contexto de la ventana
    glfwMakeContextCurrent(window);

    float vertices[] =
        {
            150, 150, 0.0, // top right corner
            0, 150, 0.0,   // top left corner
            0, 0, 0.0,     // bottom left corner
            150, 0, 0.0    // bottom right corner
        };

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // Especifica la parte de la ventana en la que OpenGL dibujará (en píxeles), convertir de normalizado a píxeles
    glMatrixMode(GL_PROJECTION);                         // La matriz de proyección define las propiedades de la cámara que ve los objetos en el marco de coordenadas mundo. Aquí se suele definir el factor de zoom, la relación de aspecto y los planos de recorte cercano y lejano.
    glLoadIdentity();                                    // Reemplaza la matriz actual con la matriz identidad y nos inicia de nuevo porque las transformaciones matriciales como glOrpho y glRotate se acumulan, básicamente nos pone en (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);    // Sistema de coordenadas esencialmente establecido
    glMatrixMode(GL_MODELVIEW);                          // (Modo de matriz por defecto) la matriz modelview define cómo se transforman tus objetos (es decir, traslación, rotación y escalado) en tu mundo
    glLoadIdentity();                                    // lo mismo que el comentario anterior

    // Bucle hasta que el usuario cierre la ventana
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderizar OpenGL aquí
        glEnableClientState(GL_VERTEX_ARRAY);      // Indica a OpenGL que está utilizando una matriz de vértices para el atributo de función fija
        glVertexPointer(3, GL_FLOAT, 0, vertices); // Apuntan a los vértices que se van a utilizar
        glDrawArrays(GL_QUADS, 0, 4);              // dibujar los vértices
        glDisableClientState(GL_VERTEX_ARRAY);     // Indica a OpenGL que has terminado de utilizar el atributo array de vértices

        // Intercambiar los búferes delantero y trasero
        glfwSwapBuffers(window);

        // Sondear y procesar eventos
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
