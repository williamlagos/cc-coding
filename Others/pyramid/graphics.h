/*
 * OpenSceneGraph Pyramid sample
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

#include <vector>
#include <time.h>

using namespace std;

class Scene {
private:
    osg::Group* root;
    osg::Geode* objectGeode;
    osg::Geometry* objectGeo;
public:
    Scene();
    void createPyramid();
    void* definePyramidVertices();
    void defineColors();
    void drawScene();
};

#endif /* GRAPHICS_H */
