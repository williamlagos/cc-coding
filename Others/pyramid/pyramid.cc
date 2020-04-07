/*
 * OpenSceneGraph Pyramid sample
 */

#include <graphics.h>

int main(int argc, char* argv[]){
	Scene* sce = new Scene();
	sce->createPyramid();
	sce->drawScene();
	return 0;
};
