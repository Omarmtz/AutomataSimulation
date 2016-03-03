#include "gridmatrix.hpp"
#include <osg/Geometry>

using namespace osg;

GridMatrix::GridMatrix(float width, float height, float depth, osg::Vec4 color, float lineWidth,float segments)
{
    width= this->width = width-0.5 ;
    height= this->height = height-0.5 ;
    depth =this->depth = depth-0.5 ;

    xSegment = ((width+0.5) / (float)segments);
    ySegment = ((height+0.5) /(float) segments);
    zSegment = ((depth+0.5)  / (float)segments);

    color = color;
    linewidth = new LineWidth();

    linewidth->setWidth(lineWidth);

    generateInternalGrid();
}

void GridMatrix::setViewState(bool isVisible)
{
    if(isVisible)
    {
        this->setAllChildrenOn();
    }
    else
    {
        this->setAllChildrenOff();
    }
}

void GridMatrix::generateInternalGrid()
{
    ref_ptr<Geometry> columnsLines = new Geometry();
    ref_ptr<Geometry> rowLines = new Geometry();

    Vec4Array* color = new Vec4Array;
    color->push_back(this->color);

    Vec3Array* columnVertexList = new Vec3Array();
    Vec3Array* rowVertexList = new Vec3Array();

    //FILLING COLUMNS
    for (float x = -0.5; x <= width; x += xSegment) {
        for (float z = -0.5; z <= depth; z += zSegment) {
            columnVertexList->push_back(Vec3(x, -0.5, z));
            columnVertexList->push_back(Vec3(x, height, z));
        }
    }

    //FILLING ROWS
    for (float x = -0.5; x <= width; x += xSegment) {
        for (float y = -0.5; y <= height; y += ySegment) {
            rowVertexList->push_back(Vec3(x, y, -0.5));
            rowVertexList->push_back(Vec3(x, y, depth));
        }
    }

    for (float z = -0.5; z <= depth; z += zSegment) {
        for (float y = -0.5; y <= height; y += ySegment) {
            rowVertexList->push_back(Vec3(-0.5, y, z));
            rowVertexList->push_back(Vec3(width, y, z));
        }
    }


    columnsLines->setVertexArray(columnVertexList);
    rowLines->setVertexArray(rowVertexList);

    columnsLines->setColorArray(color);
    columnsLines->setColorBinding(Geometry::BIND_OVERALL);
    columnsLines->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, columnVertexList->size()));

    rowLines->setColorArray(color);
    rowLines->setColorBinding(Geometry::BIND_OVERALL);
    rowLines->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, rowVertexList->size()));

    this->gridNode = new osg::Geode;
    gridNode->addDrawable(columnsLines.get());
    gridNode->addDrawable(rowLines.get());
    this->addChild(gridNode.get(),true);
}
