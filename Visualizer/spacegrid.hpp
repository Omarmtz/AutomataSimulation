#ifndef SPACEGRID_H
#define SPACEGRID_H
#include <osg/Geode>
#include <osg/LineWidth>
class SpaceGrid : public osg::Geode
{
public:
    SpaceGrid(float width, float height, float depth,osg::Vec4 color, float lineWidth);

private:
    float width;
    float height;
    float depth;
    osg::Vec4 color;
    osg::LineWidth * linewidth;
};

#endif // SPACEGRID_H
