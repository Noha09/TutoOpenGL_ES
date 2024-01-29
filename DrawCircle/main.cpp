#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3dll.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

const int num_coords = 2;
const float a = -100, b = 100, r = 100, delta = 2.0f, step = (b - a) / delta;
const static float len_points = step * num_coords;

int main(void)
{
    GLfloat puntos[400];

    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Me Quiero Morir", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat pointVertex2[] = { SCREEN_WIDTH * 0.75, SCREEN_HEIGHT / 2 };

    float x = -r, y;
    for (int i = 0; i < 400; i += 4)
    {
        y = sqrt((r * r) - (x * x));

        puntos[i] = (SCREEN_WIDTH / 2) + x;
        puntos[i + 1] = (SCREEN_HEIGHT / 2) + y;

        puntos[i + 2] = (SCREEN_WIDTH / 2) - x;
        puntos[i + 3] = (SCREEN_HEIGHT / 2) - y;

        x += delta;
    }

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.22f, 0.43f, 0.34f, 1.0f);

        glEnable(GL_POINT_SMOOTH);
        glEnableClientState(GL_VERTEX_ARRAY);
        glPointSize(1);
        glVertexPointer(2, GL_FLOAT, 0, puntos);
        glDrawArrays(GL_POINTS, 0, 200);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_POINT_SMOOTH);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}