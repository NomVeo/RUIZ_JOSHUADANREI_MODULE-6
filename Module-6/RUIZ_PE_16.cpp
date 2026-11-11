#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

bool culling = false;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (culling)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    glBegin(GL_TRIANGLES);

        // Counterclockwise triangle.
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.8f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.5f, 0.4f);

        // Clockwise triangle.
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.5f, 0.4f);
        glVertex2f(0.8f, -0.4f);

    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int, int)
{
    if (key == 'f' || key == 'F')
    {
        culling = !culling;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q16");

    glFrontFace(GL_CCW);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
