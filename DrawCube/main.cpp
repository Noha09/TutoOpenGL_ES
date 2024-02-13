#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3dll.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Me Quiero Morir", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

        DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);
        DrawCube(halfScreenWidth, halfScreenHeight, -500, 200); 

        glPopMatrix();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const GLfloat rotationSpeed = 10;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            rotationX -= rotationSpeed;
            break;
        case GLFW_KEY_DOWN:
            rotationX += rotationSpeed;
            break;
        case GLFW_KEY_RIGHT:
            rotationY += rotationSpeed;
            break;
        case GLFW_KEY_LEFT:
            rotationY -= rotationSpeed;
            break;
        }

    }
}

void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat faceVertices[] =
    {
        // Front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,

        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,

        // Back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

        // Left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,

        // Right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,

        // Top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,

        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,

        // Bottom face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength
    };

    GLfloat colors[] =
    {
        // Front face
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        // Back face
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        // Left face
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        // Right face
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        // Top face
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        // Bottom face
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo
        1.0f, 0.0f, 0.0f,  // Rojo

    };

    GLfloat lineVertices[72];
    for (int i = 0; i < 36; ++i) {
        lineVertices[2 * i] = faceVertices[i];
        lineVertices[2 * i + 1] = faceVertices[i];
    }

    GLfloat lineColors[] = {
        1.0f, 1.0f, 1.0f,  // Blanco para las líneas (replica para cada línea)
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Pintar las caras
    glVertexPointer(3, GL_FLOAT, 0, faceVertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Pintar las líneas
    glVertexPointer(3, GL_FLOAT, 0, lineVertices); 
    glColorPointer(3, GL_FLOAT, 0, lineColors); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
    glDrawArrays(GL_LINES, 0, 72); 

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
