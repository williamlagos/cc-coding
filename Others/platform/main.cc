/*
 * OpenGL, OpenAL and SDL examples.
 * Copyright (r) 2009-2020 William Oliveira de Lagos
 * Credits to fanfare.wav (CC - Freesound): Opening fanfare created with Ableton Live Orchestral Brass and Mallets packs. 
 * The fanfare was composed for Futurice Space Academy, a multiplayer game for planetarium that we created 
 * for Futubileet 2016 in Heureka Science Center.
 */

#include "platform.h"
#include <iostream>
#include <pthread.h>

using namespace std;

void* sound_thread(void* ptr) {
	cout << "Sound thread" << endl;
	OpenAL* oal = new OpenAL();
	oal->Init("./fanfare.wav");
}

void* graphics_thread(void* ptr) {
	cout << "Graphics thread" << endl;
	OpenGL* ogl = new OpenGL();
	ogl->Init(0, NULL, WIDTH, HEIGHT);
	ogl->loopCycle();
}

int main(int argc, char **argv)
{
	cout << "Starting platform..." << endl;
	pthread_t sound, graphics;
	pthread_create(&sound, NULL, sound_thread, NULL);
	// pthread_create(&graphics, NULL, graphics_thread, NULL);
	cout << "Main thread" << endl;
	SDL* sdl = new SDL(X, Y);
	sdl->mainLoop();
	return 0;
}
