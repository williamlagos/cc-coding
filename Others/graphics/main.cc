#include "physics.h"
#include "graphics.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	cout << "Starting engine..." << endl;
	Physics::start(argc,argv);
	Engine::start(argc,argv);
	return 0;
}
