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

#ifndef PLATFORM_H
#define PLATFORM_H

/*#include <osgAL/SoundManager>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <openalpp/Source>*/
#include <iostream>
#include <SDL/SDL.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define numOf(x) (sizeof(x)/sizeof*(x))

using std::cout;
using std::endl;
using std::string;

namespace Zhockon{
class SDL : public Library{
private:
	int axisx;
	int axisy;
	SDL_Event keyevent;
public:
	SDL(string,int,int);
	int baseMove();
};

class OpenAL : public Library{
private:
	ALuint Buffer;
	ALuint Source;
	ALfloat* SourcePos;
	ALfloat* SourceVel;
public:
	OpenAL(int,char**,string);
	ALboolean loadSound(char*);
};

class OpenGL : public Library{
public:
	OpenGL(string);
	void Init(int,char**,int,int);
	void loopCycle();
};
static void baseScene(void);
static void baseReshape(int,int);
};

#endif /* PLATFORM_H */