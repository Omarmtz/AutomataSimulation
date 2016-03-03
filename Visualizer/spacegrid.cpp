#include "spacegrid.hpp"

#include <osg/Geometry>

using namespace osg;

SpaceGrid::SpaceGrid(float width, float height, float depth, osg::Vec4 color, float lineWidth)
{
    width= this->width = width - 0.5;
    height= this->height = height - 0.5;
    depth =this->depth = depth - 0.5;
    float zero = 0 - 0.5;
    color = color;
    linewidth = new LineWidth();

    linewidth->setWidth(lineWidth);

    Vec4Array* colorArray = new Vec4Array;
    colorArray->push_back(color);

    ref_ptr<Geometry> lowerLines = new Geometry();
    ref_ptr<Geometry> upperLines = new Geometry();
    ref_ptr<Geometry> edgeLines = new Geometry();

    Vec3Array *lowerVertexList = new Vec3Array();

    lowerVertexList->push_back(Vec3(zero, zero, zero));
    lowerVertexList->push_back(Vec3(width, zero, zero));
    lowerVertexList->push_back(Vec3(width, zero, depth));
    lowerVertexList->push_back(Vec3(zero, zero, depth));

    Vec3Array *upperVertexList = new Vec3Array();

    upperVertexList->push_back(Vec3(zero, height, zero));
    upperVertexList->push_back(Vec3(width, height, zero));
    upperVertexList->push_back(Vec3(width, height, depth));
    upperVertexList->push_back(Vec3(zero, height, depth));

    Vec3Array *edgesVertexList = new Vec3Array();

    edgesVertexList->push_back(Vec3(width, zero, depth));
    edgesVertexList->push_back(Vec3(width, height, depth));

    edgesVertexList->push_back(Vec3(zero, zero, zero));
    edgesVertexList->push_back(Vec3(zero, height, zero));

    edgesVertexList->push_back(Vec3(width, zero, zero));
    edgesVertexList->push_back(Vec3(width, height, zero));

    edgesVertexList->push_back(Vec3(zero, zero, depth));
    edgesVertexList->push_back(Vec3(zero, height, depth));

    lowerLines->setVertexArray(lowerVertexList);
    upperLines->setVertexArray(upperVertexList);
    edgeLines->setVertexArray(edgesVertexList);

    lowerLines->setColorArray(colorArray);
    lowerLines->setColorBinding(Geometry::BIND_OVERALL);
    lowerLines->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINE_LOOP, 0, lowerVertexList->size()));

    upperLines->setColorArray(colorArray);
    upperLines->setColorBinding(Geometry::BIND_OVERALL);
    upperLines->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINE_LOOP, 0, upperVertexList->size()));

    edgeLines->setColorArray(colorArray);
    edgeLines->setColorBinding(Geometry::BIND_OVERALL);
    edgeLines->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, edgesVertexList->size()));


    lowerLines->getOrCreateStateSet()->setAttributeAndModes(linewidth, StateAttribute::ON);
    upperLines->getOrCreateStateSet()->setAttributeAndModes(linewidth, StateAttribute::ON);
    edgeLines->getOrCreateStateSet()->setAttributeAndModes(linewidth, StateAttribute::ON);

    this->addDrawable(lowerLines.get());
    this->addDrawable(upperLines.get());
    this->addDrawable(edgeLines.get());
}
