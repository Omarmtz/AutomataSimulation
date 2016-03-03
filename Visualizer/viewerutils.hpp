#ifndef VIEWERUTILS_H
#define VIEWERUTILS_H

#include <osg/ShapeDrawable>
#include "particletype.hpp"
#include "Simulator/spacePointType.hpp"
class ViewerUtils
{

public:
    ViewerUtils();

    osg::ShapeDrawable * generateSphereParticle(spacePointType_e type);

    osg::ShapeDrawable * generateCubeParticle(spacePointType_e type);

};

#endif // VIEWERUTILS_H
