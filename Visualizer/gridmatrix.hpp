#ifndef GRIDMATRIX_H
#define GRIDMATRIX_H
#include <osg/Geode>
#include <osg/Switch>
#include <osg/LineWidth>
class GridMatrix : public osg::Switch
{
public:
    GridMatrix(float width, float height, float depth,osg::Vec4 color, float lineWidth,float segments);
    void setViewState(bool isVisible);
private:

    void generateInternalGrid();

    osg::ref_ptr<osg::Geode> gridNode;

    float width;
    float height;
    float depth;
    float xSegment ;
    float ySegment ;
    float zSegment ;

    osg::Vec4 color;
    osg::LineWidth * linewidth;
};

#endif // GRIDMATRIX_H
