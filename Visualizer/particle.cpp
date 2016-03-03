#include "particle.hpp"

Particle_Viewer::Particle_Viewer(int Id, spacePointType_e type, osg::Vec3 initialPosition, osg::ref_ptr<osg::ShapeDrawable> shape)
{
    osg::Vec3 fixPosition = this->fixPosition(initialPosition);

    this->id = Id;
    this->type = type;

    this->particleNode = new osg::Geode;
    particleNode->addDrawable(shape.get());

    this->setPosition(fixPosition);
    this->initialPosition = fixPosition;
    this->addChild(particleNode.get());
}

int Particle_Viewer::getId()
{
    return id;
}

osg::Geode *Particle_Viewer::getNode()
{
    return dynamic_cast<osg::Geode *> (this->getChild(0));
}

spacePointType_e Particle_Viewer::getType()
{
    return type;
}

void Particle_Viewer::setInitialPosition(osg::Vec3 initial)
{
    this->initialPosition= initial;
}

void Particle_Viewer::setFinalPosition(osg::Vec3 final)
{
    this->finalPosition= this->fixPosition(final);
}

void Particle_Viewer::setNextPosition(osg::Vec3 nextPosition)
{
    this->nextPosition = nextPosition;
}

void Particle_Viewer::translate(float time)
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode( osg::AnimationPath::NO_LOOPING );
    osg::AnimationPath::ControlPoint pointA(this->initialPosition);
    osg::AnimationPath::ControlPoint pointB(this->finalPosition);
    path->insert( 0.0f, pointA );
    path->insert( time, pointB );

    osg::ref_ptr<osg::AnimationPathCallback> cb = new osg::AnimationPathCallback( path );
    this->setUpdateCallback( cb );

}

osg::Vec3 Particle_Viewer::getCurrentPosition()
{
    return this->getPosition();
}

osg::Vec3 Particle_Viewer::getInitialPosition()
{
    return this->initialPosition;
}

osg::Vec3 Particle_Viewer::getFinalPosition()
{
    return this->finalPosition;
}

osg::Vec3 Particle_Viewer::getNextPosition()
{
    return this->nextPosition;
}

osg::Vec3 Particle_Viewer::fixPosition(osg::Vec3 position)
{
    osg::Vec3 fixPosition;
    fixPosition.x()=position.x();
    fixPosition.y()=position.z();
    fixPosition.z()=position.y();
    return fixPosition;
}


