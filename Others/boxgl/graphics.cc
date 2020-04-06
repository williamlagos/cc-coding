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

#include <graphics.h>
#include <physics.h>

Engine::Engine() {
    counter = 0;
    direction = true;
    x = 0.0005f;
    y = 0.0005f;
    z = 0.0f;
}

void Engine::reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glLoadIdentity();
}

void Engine::defineDirection()
{
    world.Step(timeStep,1, positionIterations);
    vec position;
    position.x = 0.01f;
    position.y = 0.01f;
    printf("%3.2f - %3.2f",position.x,position.y);
    if(direction){ 
        x = 0.0001f*position.x;
        y = 0.0001f*position.y;
    }else{
        x = -0.0001f*position.x;
        y = -0.0001f*position.y;
    }
    counter = 0;
    direction = !direction;
}

void Engine::display(void)
{
    load_json("elements.json");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glTranslatef(x,y,z);  
    glColor3f(1.0,0.0,0.0); 
    glPointSize(10.0);
    glBegin(GL_TRIANGLES);
      glVertex2f(-0.8f,-0.8f);
      glVertex2f(0.0f,0.8f);
      glVertex2f(0.8f,-0.8f);
    glEnd();
    counter++;
    if(counter == 1000) defineDirection();
    glFlush();
    glutSwapBuffers();
}

void Engine::idle()
{
    static int prev_time = glutGet(GLUT_ELAPSED_TIME);
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    int elapsed_time = curr_time - prev_time;
    prev_time = curr_time;
    glutPostRedisplay();
}

void Engine::initGL(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.5,0.5,0.5);
}

void Engine::initGLUT(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL); // display mode
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);
    main_window = glutCreateWindow("BoxGL");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
}

int Engine::startEngine(int argc, char** argv)
{
    srand(time(0));
    initGLUT(argc, argv);
    initGL();
    initBOX2D(&world);
    glutMainLoop();
    return 0;
}