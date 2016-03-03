#include "worldviewer.hpp"

#include <osg/BlendFunc>
#include <osg/Geometry>

using namespace osg;

WorldViewer::WorldViewer(uint witdh, uint height, uint depth,
                         float cubeLineWidth,osg::Vec4 cubeColor,
                         float gridLineWidth,osg::Vec4 gridColor)
{
    //Set Transparency for WorldViewer
    transparencyMaterial = new Material;
    transparencyMaterial->setAmbient(Material::FRONT_AND_BACK, Vec4(0, 0, 0, 0.3));
    transparencyMaterial->setDiffuse(Material::FRONT_AND_BACK, Vec4(0, 0, 0, 0.3));

    this->getOrCreateStateSet()->setAttributeAndModes(transparencyMaterial.get());
    this->getOrCreateStateSet()->setAttributeAndModes(new BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    this->getOrCreateStateSet()->setRenderingHint(StateSet::TRANSPARENT_BIN);

    this->spaceGridLineWidth= cubeLineWidth;
    this->gridMatrixLineWidth= gridLineWidth;

    this->spaceGridColor= cubeColor;
    this->gridMatrixColor= gridColor;

    //Fix Position Y / Z
    this->sizeDepth = height;
    this->sizeHeight = depth;
    this->sizeWidth = witdh;
    this->generateSpaceGrid();
}

void WorldViewer::generateGridMatrix(float segments)
{
    this->gridMatrix = new GridMatrix(sizeWidth,sizeHeight,sizeDepth,
                                      this->gridMatrixColor,this->gridMatrixLineWidth,segments);

    this->addChild(this->gridMatrix.get());
}

void WorldViewer::setGridVisible(bool isGridVisible)
{
    GridMatrix *gridMatrix;
    for (uint var = 0; var < this->getNumChildren(); ++var)
    {
        gridMatrix = dynamic_cast<GridMatrix *>(this->getChild(var));
        if(gridMatrix)
        {
           gridMatrix->setViewState(isGridVisible);
        }
    }
}

void WorldViewer::generateSpaceGrid()
{
    this->spaceGrid = new SpaceGrid(sizeWidth,sizeHeight,sizeDepth,
                                    this->spaceGridColor,this->spaceGridLineWidth);
    //TODO CHECK FOR AXIS.
    this->axis = this->createAxis(sizeWidth,sizeHeight,sizeDepth);
    this->addChild(this->spaceGrid.get());
    this->addChild(this->axis.get());
}

osg::Geode* WorldViewer::createAxis(uint width,uint height,uint depth)
{
    //Fix Axis Y / Z
    uint temp= height;
    height = depth;
    depth = temp;
    float zero = 0 - 0.5;
    osg::ref_ptr<osg::Geode> geode =new osg::Geode();
    osg::ref_ptr<osg::Geometry> geometry =new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> vertices (new osg::Vec3Array());
    vertices->push_back (osg::Vec3 ( zero,zero,zero));
    vertices->push_back (osg::Vec3 ( width+10, zero, zero));
    vertices->push_back (osg::Vec3 ( zero, zero, zero));
    vertices->push_back (osg::Vec3 ( zero, height+10, zero));
    vertices->push_back (osg::Vec3 ( zero, zero, zero));
    vertices->push_back (osg::Vec3 ( zero, zero, depth+10));
    geometry->setVertexArray (vertices.get());

    osg::ref_ptr<osg::Vec4Array> colors (new osg::Vec4Array());
    colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
    geometry->setColorArray (colors.get(), osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,6));

    geode->addDrawable( geometry.get() );
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);
    return geode.release();
}
