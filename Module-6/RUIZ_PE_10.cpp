#define GL_SILENCE_DEPRECATION
#include <cstdio>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

GLuint VBOid;

GLfloat vertices[] = {
     0.0f,  0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f,
     0.3f, -0.3f, 0.0f
};

void multiply4x4(float A[16], float B[16], float C[16])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            C[row * 4 + col] = 0.0f;

            for (int k = 0; k < 4; k++)
            {
                C[row * 4 + col] +=
                    A[row * 4 + k] * B[k * 4 + col];
            }
        }
    }
}

void applyMatrix(float matrix[16], int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV == NULL)
        return;

    float x = mapV[startindex];
    float y = mapV[startindex + 1];
    float z = mapV[startindex + 2];
    float w = 1.0f;

    float nx = matrix[0] * x + matrix[1] * y +
               matrix[2] * z + matrix[3] * w;

    float ny = matrix[4] * x + matrix[5] * y +
               matrix[6] * z + matrix[7] * w;

    float nz = matrix[8] * x + matrix[9] * y +
               matrix[10] * z + matrix[11] * w;

    mapV[startindex] = nx;
    mapV[startindex + 1] = ny;
    mapV[startindex + 2] = nz;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.0f, 0.8f, 0.2f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q10");

#ifndef __APPLE__
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        std::fprintf(stderr, "GLEW initialization failed: %s\n",
                     glewGetErrorString(glewStatus));
        return 1;
    }
#endif

    float translate[16] = {
        1, 0, 0, 0.3f,
        0, 1, 0, 0.2f,
        0, 0, 1, 0.0f,
        0, 0, 0, 1
    };

    float scale[16] = {
        2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1
    };

    float combined[16];

    // Translation multiplied by scaling.
    multiply4x4(translate, scale, combined);

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_DYNAMIC_DRAW);

    for (int i = 0; i < 9; i += 3)
        applyMatrix(combined, i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
