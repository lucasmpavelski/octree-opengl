//
// Octree implementation example in OpenGL
// octree_fn.cpp
//
// Created by Lucas M. Pavelski (lmpavelski@yahoo.com.br) on 01/01/2013
//
// If you find it useful, please let me know!
//

#include "octree_fn.h"

namespace octree {

void drawCube(double center_x, double center_y, double center_z, double size)
{
    double half_size = size / 2.0;
    double front     = center_z - half_size;
    double back      = center_z + half_size;
    double left      = center_x - half_size;
    double right     = center_x + half_size;
    double bottom    = center_y - half_size;
    double top       = center_y + half_size;

    glPushMatrix();

    // red side - front
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(right, bottom, front);
    glVertex3f(right, top,    front);
    glVertex3f(left,  top,    front);
    glVertex3f(left,  bottom, front);
    glEnd();

    // green side - back
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(right, bottom, back);
    glVertex3f(right, top,    back);
    glVertex3f(left,  top,    back);
    glVertex3f(left,  bottom, back);
    glEnd();

    // blue side - right
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(right, bottom, front);
    glVertex3f(right, top,    front);
    glVertex3f(right, top,    back);
    glVertex3f(right, bottom, back);
    glEnd();

    // yellow side - left
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(left, bottom, back);
    glVertex3f(left, top,    back);
    glVertex3f(left, top,    front);
    glVertex3f(left, bottom, front);
    glEnd();

    // magneta side - top
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(right, top, back);
    glVertex3f(right, top, front);
    glVertex3f(left,  top, front);
    glVertex3f(left,  top, back);
    glEnd();

    // cyan side - bottom
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(right, bottom, front);
    glVertex3f(right, bottom, back);
    glVertex3f(left,  bottom, back);
    glVertex3f(left,  bottom, front);
    glEnd();

    glPopMatrix();
}

void drawOctree(const string& tree, double center_x, double center_y,
                double center_z, double cube_size)
{
    drawOctree(tree, 0, center_x, center_y, cube_size);
}

int drawOctree(const string& tree, size_t pos, double center_x, double center_y,
               double center_z, double cube_size)
{
    // bad-formed tree
    assert(pos < tree.size());
    // unrecognized char
    assert(tree[pos] == EMPTY || tree[pos] == FILLED || tree[pos] == DIRTY);

    if (tree[pos] == EMPTY)
    {
        return pos + 1;
    }
    else if (tree[pos] == FILLED)
    {
        drawCube(center_x, center_y, center_z, cube_size);
        return pos + 1;
    }
    else // tree[pos] == DIRTY
    {
        double new_cube_size = cube_size / 2.0;
        double bias          = new_cube_size / 2.0;
        double left          = center_x - bias;
        double right         = center_x + bias;
        double bottom        = center_y - bias;
        double top           = center_y + bias;
        double front         = center_z - bias;
        double back          = center_z + bias;

        pos += 1;
        pos = drawOctree(tree, pos, left,  bottom, back,  new_cube_size);
        pos = drawOctree(tree, pos, right, bottom, back,  new_cube_size);
        pos = drawOctree(tree, pos, left,  top,    back,  new_cube_size);
        pos = drawOctree(tree, pos, right, top,    back,  new_cube_size);
        pos = drawOctree(tree, pos, left,  bottom, front, new_cube_size);
        pos = drawOctree(tree, pos, right, bottom, front, new_cube_size);
        pos = drawOctree(tree, pos, left,  top,    front, new_cube_size);
        pos = drawOctree(tree, pos, right, top,    front, new_cube_size);

        return pos;
    }
}

}		/* -----  end of namespace octree  ----- */
