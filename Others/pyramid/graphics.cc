/*
 * OpenSceneGraph Pyramid sample
 */

#include <graphics.h>

Scene::Scene() 
{
    root = new osg::Group();
    objectGeode = new osg::Geode();
    objectGeo = new osg::Geometry();
    objectGeode->addDrawable(objectGeo);
    root->addChild(objectGeode);
}

void* Scene::definePyramidVertices()
{
    osg::Vec3Array* objVertices = new osg::Vec3Array;
    osg::Vec3 FrontLeft  = osg::Vec3(0,0,0);
    osg::Vec3 FrontRight = osg::Vec3(10,0,0);
    osg::Vec3 BackRight  = osg::Vec3(10,10,0);
    osg::Vec3 BackLeft   = osg::Vec3(0,10,0);
    osg::Vec3 Peak       = osg::Vec3(5,5,10);
    objVertices->push_back(FrontLeft); // front left
    objVertices->push_back(FrontRight); // front right
    objVertices->push_back(BackRight); // back right
    objVertices->push_back(BackLeft); // back left
    objVertices->push_back(Peak); // peak
    return (void*)objVertices;
}

void Scene::createPyramid()
{
    objectGeo->setVertexArray((osg::Vec3Array*)definePyramidVertices());

    osg::DrawElementsUInt* basePyramid =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    basePyramid->push_back(3);
    basePyramid->push_back(2);
    basePyramid->push_back(1);
    basePyramid->push_back(0);
    objectGeo->addPrimitiveSet(basePyramid);
        
    osg::DrawElementsUInt* pFaceOne =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);   
    pFaceOne->push_back(0);
    pFaceOne->push_back(1);
    pFaceOne->push_back(4);
    objectGeo->addPrimitiveSet(pFaceOne);

    osg::DrawElementsUInt* pFaceTwo =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);   
    pFaceTwo->push_back(1);
    pFaceTwo->push_back(2);
    pFaceTwo->push_back(4);
    objectGeo->addPrimitiveSet(pFaceTwo);

    osg::DrawElementsUInt* pFaceThree =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);   
    pFaceThree->push_back(2);
    pFaceThree->push_back(3);
    pFaceThree->push_back(4);
    objectGeo->addPrimitiveSet(pFaceThree);

    osg::DrawElementsUInt* pFaceFour =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);   
    pFaceFour->push_back(3);
    pFaceFour->push_back(0);
    pFaceFour->push_back(4);
    objectGeo->addPrimitiveSet(pFaceFour);
    
    defineColors();
}
void Scene::defineColors()
{
    osg::Vec4Array* colors = new osg::Vec4Array;
    osg::Vec4 Red   = osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f);
    osg::Vec4 Green = osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f);
    osg::Vec4 Blue  = osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f);
    osg::Vec4 White = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors->push_back(Red); //index 0 red
    colors->push_back(Green); //index 1 green
    colors->push_back(Blue); //index 2 blue
    colors->push_back(White); //index 3 white

    objectGeo->setColorArray(colors);
    objectGeo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
}
void Scene::drawScene()
{
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);
    viewer.run();
}