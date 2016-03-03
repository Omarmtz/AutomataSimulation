#include "particledisplacer.hpp"
#include <osg/AnimationPath>

#include <Visualizer/particle.hpp>
#include <iostream>
particleDisplacer::particleDisplacer():time(1)
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode( osg::AnimationPath::NO_LOOPING );
    this->setAnimationPath(path);
}

void particleDisplacer::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{
    Particle_Viewer * particle = dynamic_cast<Particle_Viewer*>(node);

    if (!particle)return;

    if(this->getAnimationPath()->empty())
    {
        osg::AnimationPath::ControlPoint pointA(particle->getInitialPosition());
        osg::AnimationPath::ControlPoint pointB(particle->getFinalPosition());
        this->getAnimationPath()->insert( 0.0f, pointA );
        this->getAnimationPath()->insert( time, pointB );
    }
    else if(particle->getNextPosition() == particle->getFinalPosition())
    {
        return;
    }
    else if(particle->getFinalPosition() == particle->getPosition())
    {
        std::cout<<"Moving Particle to next Position ID:"<<particle->getId()<<std::endl;
        std::cout<<"Time Simulation:"<<this->getAnimationTime()<<std::endl;
        this->setPause(true);
        this->getAnimationPath()->clear();

        osg::Vec3 next = particle->getNextPosition();

        osg::AnimationPath::ControlPoint pointA(particle->getPosition());
        osg::AnimationPath::ControlPoint pointB(next);
        particle->setFinalPosition(next);
        this->getAnimationPath()->insert( 0.0f, pointA );
        this->getAnimationPath()->insert( time, pointB );
        this->reset();
        this->setPause(false);

    }

    AnimationPathCallback::operator ()(node,nv);
}
