/*
 * Platform with OpenGL, OpenAL and SDL sample
 */

#include <platform.h>

SDL::SDL(int x, int y)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
	axisx = x;
	axisy = y;
	baseScene();
}

int SDL::mainLoop()
{
	bool exited = true;
	while(exited) {
		while (SDL_PollEvent(&keyevent)){
			switch(keyevent.type){
				case SDL_KEYDOWN:
					cout << "Key down" << endl;
					switch(keyevent.key.keysym.sym){
						case SDLK_LEFT: axisx -= 1; break;
						case SDLK_RIGHT:axisx += 1; break;
						case SDLK_UP: 	
							axisy -= 1;
							exited = false; 
							break;
						case SDLK_DOWN: axisy += 1; break;
						default: 	break;
					}
			}
		}
	}
	return 0;
}


OpenAL::OpenAL()
{

}

ALboolean OpenAL::Init(const char* filename)
{
	ALboolean enumeration;
	const ALCchar *devices;
	// const ALCchar *defaultDeviceName = argv[1];
	const ALCchar *defaultDeviceName = "";
	int ret;
	char *bufferData;
	ALCdevice *device;
	ALvoid *data;
	ALCcontext *context;
	ALsizei size, freq;
	ALenum format;
	ALuint buffer, source;
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	ALboolean loop = AL_FALSE;
	ALCenum error;
	ALint source_state;

	fprintf(stdout, "Using " BACKEND " as audio backend\n");

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
		fprintf(stderr, "enumeration extension not available\n");

	// list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

	if (!defaultDeviceName)
		defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	device = alcOpenDevice(defaultDeviceName);
	if (!device) {
		fprintf(stderr, "unable to open default device\n");
		return -1;
	}

	fprintf(stdout, "Device: %s\n", alcGetString(device, ALC_DEVICE_SPECIFIER));

	alGetError();

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		fprintf(stderr, "failed to make default context\n");
		return -1;
	}
	LOG("make default context");

	/* set orientation */
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	LOG("listener position");
    	alListener3f(AL_VELOCITY, 0, 0, 0);
	LOG("listener velocity");
	alListenerfv(AL_ORIENTATION, listenerOri);
	LOG("listener orientation");

	alGenSources((ALuint)1, &source);
	LOG("source generation");

	alSourcef(source, AL_PITCH, 1);
	LOG("source pitch");
	alSourcef(source, AL_GAIN, 1);
	LOG("source gain");
	alSource3f(source, AL_POSITION, 0, 0, 0);
	LOG("source position");
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	LOG("source velocity");
	alSourcei(source, AL_LOOPING, AL_FALSE);
	LOG("source looping");

	alGenBuffers(1, &buffer);
	LOG("buffer generation");


	alutLoadWAVFile((ALbyte*)"fanfare.wav", &format, &data, &size, &freq, &loop);
	LOG("loading wav file");

	alBufferData(buffer, format, data, size, freq);
	LOG("buffer copy");

	alSourcei(source, AL_BUFFER, buffer);
	LOG("buffer binding");

	alSourcePlay(source);
	LOG("source playing");

	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	LOG("source state get");
	while (source_state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	}

	/* exit context */
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

	return 0;
}


OpenGL::OpenGL()
{

}

void OpenGL::Init(int argc,char** argv,int winHeight,int winWidth)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winHeight,winWidth);
	glutCreateWindow("Platform");
}

void baseScene(void)
{
	baseReshape(WIDTH, HEIGHT);
	float angle = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0,
		  0.0, 0.0,  0.0,
		  0.0, 1.0,  0.0);
	glRotatef(angle,0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3f(-2.0,-2.0,0.0);
		glVertex3f(2.0,0.0,0.0);
		glVertex3f(0.0,2.0,0.0);
		glVertex3f(-1.0,0.0,0.0);
	glEnd();
	angle += 0.1;
	// glutSwapBuffers();
	SDL_GL_SwapBuffers();
}

void baseReshape(int width, int height)
{
	if(height == 0)
		height == 1;
	float ratio = width*1.0/height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,width,height);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGL::loopCycle()
{
	glutDisplayFunc(baseScene);
	glutReshapeFunc(baseReshape);
	glutIdleFunc(baseScene);
	glutMainLoop();
}
