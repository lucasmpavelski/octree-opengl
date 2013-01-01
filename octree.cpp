//
// Octree implementation example in OpenGL
// octree.cpp
//
// Created by Lucas M. Pavelski (lmpavelski@yahoo.com.br) on 01/01/2013
//
// If you find it useful, please let me know!
//

// Includes
#include <GL/glut.h>
#include "octree_fn.h"
using namespace octree;

// Defines
#define APP_NAME "OctTree"
#define WINDOW_W 600
#define WINDOW_H 600

// Global Variables
double rotate_y          = 0.0;
double rotate_x          = 0.0;
double zoom              = 1.0;

// Constants
const double rotate_step = 5.0;
const double zoom_step   = 0.01;
const double cube_size   = 1.0;
const double center_x    = 0.0;
const double center_y    = 0.0;
const double center_z    = 0.0;

// Example octree for a cube grid: "2", "1" and "0" are the symbols for dirty,
// filled and empty nodes, respectively
const string tree        = "2"
                             "2"
                               "11101000"
                             "2"
                               "11010100"
                             "2"
                               "10110010"
                             "2"
                               "01110001"
                             "2"
                               "10001110"
                             "2"
                               "01001101"
                             "2"
                               "00101011"
                             "2"
                               "00010111";

// Prototypes
void reshape(int width, int height);
void display();
void keyboard(unsigned char key, int x, int y);

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
    glOrtho(0.0, width, 0.0, height, 0, 50000);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glScaled(zoom, zoom, zoom);

    drawOctree(tree, center_x, center_y, center_z, cube_size);

    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'd')
        rotate_y += rotate_step;
    else if (key == 'a')
        rotate_y -= rotate_step;
    else if (key == 'w')
        rotate_x += rotate_step;
    else if (key == 's')
        rotate_x -= rotate_step;
    else if (key == 'q')
        zoom *= (1.0 + zoom_step);
    else if (key == 'e')
        zoom *= (1.0 - zoom_step);

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_W) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_H) / 2);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow(APP_NAME);

    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

