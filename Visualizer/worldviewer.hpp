#ifndef WORLDVIEWER_H
#define WORLDVIEWER_H
#include <osg/Group>
#include <osg/Material>
#include "spacegrid.hpp"
#include "gridmatrix.hpp"

class WorldViewer : public osg::Group
{
public:
    WorldViewer(uint witdh, uint height, uint depth,
                float cubeLineWidth, osg::Vec4 cubeColor, float gridLineWidth, osg::Vec4 gridColor);

    void generateGridMatrix(float segments);

    void setGridVisible(bool isGridVisible);
private:

    void generateSpaceGrid();
    osg::Geode* createAxis(uint width,uint height,uint depth);
    osg::ref_ptr<osg::Material> transparencyMaterial;

    osg::ref_ptr<SpaceGrid> spaceGrid;
    osg::ref_ptr<GridMatrix> gridMatrix;
    osg::ref_ptr<osg::Geode> axis;
    uint sizeWidth,sizeHeight,sizeDepth;

    float spaceGridLineWidth;
    float gridMatrixLineWidth;

    osg::Vec4 spaceGridColor;
    osg::Vec4 gridMatrixColor;

};

#endif // WORLDVIEWER_H
