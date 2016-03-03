#include "viewer.hpp"

Viewer::Viewer()
{
    this->initialize();
}

Viewer::Viewer(const SpaceConfigPtr_t & spaceConfig, uint width, uint height, uint depth)
{
    this->initialize();
    this->setViewerConfiguration();
    if(spaceConfig){

    this->generateSpaceData(spaceConfig);
    }
    this->setSpaceInformation(width,height,depth);
}

void Viewer::initialize()
{
    xWindowLocation=400;
    yWindowLocation=400;
    xWindowWidth=640;
    yWindowHeight=800;
    screenNumber= 0;
    this->viewer = new osgViewer::Viewer;
    this->util = new ViewerUtils;
    this->backgroundColor = osg::Vec4(1,1,1,1);
    this->sceneRootNode = new osg::Group;
}

void Viewer::setSpaceInformation(uint width, uint height, uint depth)
{
    this->informationNodeScene= new WorldViewer(width,height,depth,
                                                1.0,osg::Vec4(0,0,0,1),
                                                0.5,osg::Vec4(0,0,0,1));
    //SET WORLD GRID MATRIX OPTIONAL..
    this->informationNodeScene->generateGridMatrix((width+height+depth)/3);

    this->sceneRootNode->addChild(informationNodeScene);


    setSceneData();
}

void Viewer::setViewerConfiguration()
{
    this->viewer->getCamera()->setClearColor(backgroundColor);
    viewer->setUpViewInWindow(xWindowLocation,yWindowLocation,xWindowWidth,yWindowHeight,screenNumber);
    viewer->setCameraManipulator(new osgGA::TrackballManipulator);
}

void Viewer::setCustomSceneData(osg::Node *rootNode)
{
    this->viewer->setSceneData(rootNode);
}

void Viewer::updateFromGrid(const SpaceConfigPtr_t &spaceConfig)
{
    ///////DELETING ALL CHILDREN OF TYPE PARTICLE VIEWER !!!ONLY FOR TESTING
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    for (int var = 0; var < this->sceneRootNode->getNumChildren(); ++var) {
        Particle_Viewer * testSphere = dynamic_cast<Particle_Viewer*>(sceneRootNode->getChild(var));

        if (testSphere)
        {
            sceneRootNode->removeChild(var,1);
            var=0;
        }
    }
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    this->generateSpaceData(spaceConfig);

}

void Viewer::setSceneData()
{
    this->viewer->setSceneData(sceneRootNode);
}

void Viewer::generateSpaceData(const SpaceConfigPtr_t &spaceConfig)
{
    spaceDimensions_t dimensions = spaceConfig->getDimensions();

    for(dimension_t x = 0; x < dimensions.x; x++)
    {
        for(dimension_t y = 0; y < dimensions.y; y++)
        {
            for(dimension_t z = 0; z < dimensions.z; z++)
            {
                SpacePointPtr_t point = spaceConfig->getPoint(x, y, z);
                osg::ref_ptr<Particle_Viewer> cellSpace;
                if(point->getType() == spacePointType_e::wall)
                {
                    cellSpace= new Particle_Viewer(x+y,spacePointType_e::wall,osg::Vec3(x,y,z),wall);
                }
                else if (point->getType()==spacePointType_e::cold)
                {
                    cellSpace= new Particle_Viewer(x+y,spacePointType_e::cold,osg::Vec3(x,y,z),coldParticle);
                }
                else if (point->getType()==spacePointType_e::hot)
                {
                    cellSpace= new Particle_Viewer(x+y,spacePointType_e::hot,osg::Vec3(x,y,z),hotParticle);
                }
                this->sceneRootNode->addChild(cellSpace.get());

            }
        }
    }
}

osgViewer::Viewer *Viewer::getViewer()
{
    return this->viewer;
}
