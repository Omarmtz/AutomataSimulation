#include "viewerutils.hpp"


ViewerUtils::ViewerUtils()
{

}

osg::ShapeDrawable *ViewerUtils::generateSphereParticle(spacePointType_e type)
{
    osg::ref_ptr<osg::ShapeDrawable> sphere = new osg::ShapeDrawable;
    sphere->setShape(new osg::Sphere(osg::Vec3(),0.5));
    switch (type) {
    case spacePointType_e::wall:
        sphere->setColor(osg::Vec4(0,0,1,1));
        break;
    case spacePointType_e::empty:
        sphere->setColor(osg::Vec4(0,0,0,0));
        break;
    case 1:
        sphere->setColor(osg::Vec4(1,0,0,1));
        break;    
    default:
        sphere->setColor(osg::Vec4(0,0,1,1));
        break;
    }
    return sphere.release();
}

osg::ShapeDrawable *ViewerUtils::generateCubeParticle(spacePointType_e type)
{
    osg::ref_ptr<osg::ShapeDrawable> cube = new osg::ShapeDrawable;
    cube->setShape(new osg::Box(osg::Vec3(),1,1,1));
    switch (type) {
    case spacePointType_e::wall:
        cube->setColor(osg::Vec4());
        break;
    case spacePointType_e::empty:
        cube->setColor(osg::Vec4(0,0,0,0));
        break;
    case 1:
        cube->setColor(osg::Vec4(1,0,0,1));
        break;
    default:
        cube->setColor(osg::Vec4(0,0,1,1));
        break;
    }
    return cube.release();
}
