#include <GL/glut.h>
#include <math.h>

const int vertices = 66; // Número de vértices en el rostro del gato

double Matriz[vertices][2] = {{62, 40}, {69, 35}, {69, 35}, {105, 59}, {105, 59}, {70, 80}, {70, 80}, {62, 40},

                              {105, 59},
                              {120, 132},
                              {120, 132},
                              {63, 105},
                              {63, 105},
                              {70, 80},

                              {63, 105},
                              {72, 147},
                              {72, 147},
                              {120, 132},

                              {120, 132},
                              {129, 141},
                              {129, 141},
                              {129, 148},
                              {129, 148},
                              {118, 155},
                              {118, 155},
                              {72, 147},

                              {72, 147},
                              {129, 173},
                              {129, 173},
                              {129, 160},
                              {129, 160},
                              {118, 155},

                              {129, 173},
                              {186, 147},
                              {186, 147},
                              {141, 155},
                              {141, 155},
                              {129, 160},

                              {141, 155},
                              {129, 148},
                              {129, 141},
                              {140, 132},
                              {140, 132},
                              {186, 147},

                              {186, 147},
                              {196, 105},
                              {196, 105},
                              {140, 132},

                              {186, 147},
                              {129, 130},
                              {129, 130},
                              {72, 147},

                              {140, 132},
                              {155, 59},
                              {155, 59},
                              {105, 59},

                              {155, 59},
                              {190, 80},
                              {190, 80},
                              {196, 105},

                              {190, 80},
                              {197, 39},
                              {197, 39},
                              {191, 35},
                              {191, 35},
                              {155, 59}}; // Coordenadas de los vértices

const int Ancho = 500;
const int Alto = 500;

static void PintarLineas(double xi, double yi, double xf, double yf)
{
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2d(xi, yi);
    glVertex2d(xf, yf);
    glEnd();
    glFlush();
}

static void PintarImagen(double Mt[vertices][2])
{
    for (int i = 0; i < (vertices - 1); i++)
    {
        PintarLineas(Mt[i][0], Mt[i][1], Mt[i + 1][0], Mt[i + 1][1]);
    }
    // Conectar el último vértice con el primer vértice para cerrar el polígono
    PintarLineas(Mt[vertices - 1][0], Mt[vertices - 1][1], Mt[0][0], Mt[0][1]);
}

static void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0, Ancho, Alto, 0);
    PintarImagen(Matriz);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(Ancho, Alto);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Me Quiero Morir");
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}