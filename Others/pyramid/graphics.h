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

#include <osgAL/SoundManager>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>

#include <vector>
#include <time.h>

using namespace std;

template <class T>
class Matrix {
public:
    Matrix();
};

class Surface {
public:
    Surface(int);
    void whichPoints(std::vector<int>);
};

class Geometry {
public:
//    void createParent(Group*);
    void createColorBind();
    void whichVertexMatrix(Matrix<int>*);
    void whichColorsMatrix(Matrix<float>*);
    void createPrimitiveSet(Surface*);
};

class Group {
public:
    void addChild(Geometry*);
};

class Scene {
private:
    Group* root;
public:
    Scene();
    void createPyramid();
    void createCube();
    void whichPrimitives(int, vector<int>, Geometry*);
    void* defineVertices();
    void* linkSceneObject(Geometry*);
    void* createObject();
    void* defineColors(Geometry*);
    void transformMode(Geometry*);
    void drawScene();
};

class View{
public:
      View();
      void setSceneData();
      void run();
};

class Graphics {
private:
    Surface *surface;
    Geometry *geometry;
    Scene *scene;
public:
    Graphics();
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
