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

#include <iostream>
#include <SDL/SDL.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define numOf(x) (sizeof(x)/sizeof*(x))

#define X 0
#define Y 0
#define WIDTH 800
#define HEIGHT 600
#define LOG(x) printf(x)
#define BACKEND "alut"

using std::cout;
using std::endl;
using std::string;

class SDL {
private:
	int axisx;
	int axisy;
	SDL_Event keyevent;
public:
	SDL(int,int);
	int mainLoop();
};

class OpenAL {
private:
	ALuint Buffer;
	ALuint Source;
	ALfloat* SourcePos;
	ALfloat* SourceVel;
public:
	OpenAL();
	ALboolean Init(const char*);
};

class OpenGL {
public:
	OpenGL();
	void Init(int,char**,int,int);
	void loopCycle();
};
static void baseScene(void);
static void baseReshape(int,int);

#endif /* PLATFORM_H */