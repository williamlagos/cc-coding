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

#ifndef PHYSICS_H
#define PHYSICS_H

//#include <Box2D/Box2D.h>
#include <modules.h>

class Physics {
private:
    /*b2Body *groundBody,*body;
    b2Vec2 gravity;
    b2World world;
    b2BodyDef groundBodyDef,bodyDef;
    b2PolygonShape groundBox,dynamicBox;
    b2FixtureDef fixtureDef;*/
    float timeStep;
    int velocityIterations,positionIterations;
public:
    Physics();
    void initBOX2D(/*b2World *wrd*/);
};

class Control { //Input
public:
    Control();
};

class Input : Package{
private:
    Control *control;
public:
    Input();
};

#endif /* PHYSICS_H */
