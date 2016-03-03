#ifndef VIEWER_H
#define VIEWER_H
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>

#include "particle.hpp"
#include "objectmodel.hpp"
#include "worldviewer.hpp"
#include "viewerutils.hpp"
#include "Simulator/SpaceConfig.hpp"
class Viewer
{
public:

    Viewer();
    //Read Space config and create 3D Space
    Viewer(const SpaceConfigPtr_t &spaceConfig, uint width, uint height, uint depth);

    osgViewer::Viewer * getViewer();

    void setCustomSceneData(osg::Node * rootNode);

    void updateFromGrid(const SpaceConfigPtr_t &spaceConfig);

private:
    void initialize();

    void setSpaceInformation(uint width, uint height, uint depth);

    void setViewerConfiguration();

    void setSceneData();

    ////Method to be optimized.
    void generateSpaceData(const SpaceConfigPtr_t & spaceConfig);

    //Viewer configuration
    osgViewer::Viewer* viewer;
    int xWindowLocation;
    int yWindowLocation;
    int xWindowWidth;
    int yWindowHeight;
    int screenNumber;

    osg::Vec4 backgroundColor;

    //world scene data
    osg::Group* sceneRootNode;

    //viewer utilities
    ViewerUtils* util;
    WorldViewer * informationNodeScene;
    ObjectModel* model;

    ///ONLY FOR TESTING !!!
    /// //////////////////////////////////////////////////////////////////////////////////// ///
    /// /// //////////////////////////////////////////////////////////////////////////////////// ///
    /// Create drawables to save memory
    osg::ref_ptr<osg::ShapeDrawable> wall=this->util->generateCubeParticle(spacePointType_e::wall);
    osg::ref_ptr<osg::ShapeDrawable> hotParticle=this->util->generateSphereParticle(spacePointType_e::cold);
    osg::ref_ptr<osg::ShapeDrawable> coldParticle=this->util->generateSphereParticle(spacePointType_e::hot);
    /// //////////////////////////////////////////////////////////////////////////////////// ///
    /// //////////////////////////////////////////////////////////////////////////////////// ///

};

#endif // VIEWER_H
