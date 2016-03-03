#ifndef PARTICLEDISPLACER_H
#define PARTICLEDISPLACER_H
#include <osg/AnimationPath>
class particleDisplacer : public osg::AnimationPathCallback
{    
    // NodeCallback interface
public:
    particleDisplacer();
    void operator ()(osg::Node *node, osg::NodeVisitor *nv);

private:
    float time;

};

#endif // PARTICLEDISPLACER_H
