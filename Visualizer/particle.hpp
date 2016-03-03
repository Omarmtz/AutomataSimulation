#ifndef PARTICLE_H
#define PARTICLE_H
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include "Simulator/spacePointType.hpp"
class Particle_Viewer : public osg::PositionAttitudeTransform
{
public:
    Particle_Viewer(int Id,spacePointType_e type,osg::Vec3 initialPosition,osg::ref_ptr<osg::ShapeDrawable> shape);

    int getId();

    osg::Geode * getNode();

    spacePointType_e getType();

    void setInitialPosition(osg::Vec3 initial);
    void setFinalPosition(osg::Vec3 final);
    void setNextPosition(osg::Vec3 nextPosition);

    void translate(float time);

    osg::Vec3 getCurrentPosition();
    osg::Vec3 getInitialPosition();
    osg::Vec3 getFinalPosition();
    osg::Vec3 getNextPosition();

private:

    osg::Vec3 fixPosition(osg::Vec3 position);

    int id;
    spacePointType_e type;
    osg::ref_ptr<osg::Geode> particleNode;

    osg::Vec3 initialPosition;
    osg::Vec3 finalPosition;
    osg::Vec3 nextPosition;
};

#endif // PARTICLE_H
