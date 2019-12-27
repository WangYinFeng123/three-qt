#include "board.h"
#include "threewidget.h"

#include <sstream>
using namespace std;

#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/BlendFunc>
#include <osg/AutoTransform>
#include <osg/PositionAttitudeTransform>
using namespace osg;

namespace ThreeQt {

struct Board::Finder : public NodeVisitor {
    Finder() : NodeVisitor(TRAVERSE_ALL_CHILDREN),precise(true),outMt(nullptr) {}
    virtual void apply(Geometry& node) {
        auto name = node.getName();

        if(precise) {
            if(name == inName) {
                if(outMt == nullptr) {
                    outMt = &node;
                    return;
                }
            }
        } else {
            if(0 == name.find(inName)) {
                if(outMt == nullptr) {
                    outMt = &node;
                    return;
                }
            }
        }

        traverse(node);
    }

    bool precise;
    string inName;
    Geometry* outMt;
};

struct Board::Plugin {
    ThreeWidget* tw;
    ref_ptr<Camera> hudCamera;
};


Board::Board(ThreeWidget* tw)
{
    md = new Plugin;
    md->tw = tw;

    md->hudCamera = new Camera;
    md->hudCamera->setProjectionMatrix(Matrix::ortho2D(-1.0,1.0,-1.0,1.0));
    md->hudCamera->setReferenceFrame(Transform::ABSOLUTE_RF);
    md->hudCamera->setViewMatrixAsLookAt(Vec3(0,-1,0), Vec3(0,0,0), Vec3(0,0,1));
    md->hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
    md->hudCamera->setRenderOrder(Camera::POST_RENDER);
    md->hudCamera->setAllowEventFocus(false);
    tw->initScene->addChild(md->hudCamera);
}

Board::~Board()
{
    md->tw->initScene->removeChild(md->hudCamera);
    delete md;
}

bool Board::modelNameRepeat(string name) {
    Finder nv; nv.inName = name; md->hudCamera->accept(nv);
    return nullptr != nv.outMt;
}

string Board::modelName(unsigned long long seed) {
    string name;

    do {
        stringstream fmt;
        fmt << "model" << endl
            << hex << seed++ << endl
            << "Editor::Model";
        name = fmt.str();
    } while(modelNameRepeat(name));
    return name;
}

string Board::planeDraw(vec2 lt, vec2 rd) {
    auto geo = new Geometry;
    auto name = modelName(reinterpret_cast<unsigned long long>(geo));
    geo->setName(name);
    geo->setDataVariance(osg::Object::DYNAMIC);
    geo->setUseDisplayList(false);

    auto colors = new Vec4Array;
    colors->push_back(Vec4(1.0,1.0,0.0,1.0));
    geo->setColorArray(colors);
    geo->setColorBinding(osg::Geometry::BIND_OVERALL);

    auto normal = new Vec3Array(1);
    (*normal)[0]=osg::Vec3(0,-1,0);
    geo->setNormalArray(normal);
    geo->setNormalBinding(osg::Geometry::BIND_OVERALL);

    auto pri = new DrawArrays(PrimitiveSet::LINE_LOOP,0,4);
    geo->addPrimitiveSet(pri);

    auto polyMode = new PolygonMode;
    polyMode->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    geo->getOrCreateStateSet()->setAttributeAndModes(polyMode);
    geo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    auto vertex = new Vec3Array(4);
    (*vertex)[0]=osg::Vec3(get<0>(lt),0,get<1>(lt));
    (*vertex)[1]=osg::Vec3(get<0>(lt),0,get<1>(rd));
    (*vertex)[2]=osg::Vec3(get<0>(rd),0,get<1>(rd));
    (*vertex)[3]=osg::Vec3(get<0>(rd),0,get<1>(lt));
    geo->setVertexArray(vertex);

    md->hudCamera->addChild(geo);
    return name;
}

void Board::clear() {
    md->hudCamera->removeChildren(0,md->hudCamera->getNumChildren());
}

}
