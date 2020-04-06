/*
 * This file is part of elements project.
 * 
 * Copyright (C) 2009-2011 William Oliveira de Lagos <william.lagos@icloud.com>
 *
 * Elements is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Elements is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elements. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define WIDTH 800
#define HEIGHT 600

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <vector>
#include <time.h>

using namespace std;

struct vec {
    float x;
    float y;
};

class Engine {
public:
    Engine();
    static void init();
    static void display();
    static void reshape(int, int);
    static void defineDirection();
    static void idle();
    static void initGL(void);
    static void initGLUT(int, char**);
    static int start(int, char**);
};

#ifndef TEXRECT_H
#define TEXRECT_H

// Struct to hold texture coords for each frame
struct TexRect
{
    float u1, v1;
    float u2, v2;
};

#endif // TEXRECT_H

#endif /* GRAPHICS_H */
