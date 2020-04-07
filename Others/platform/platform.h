/*
 * Platform with OpenGL, OpenAL and SDL sample
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