#include "basic.h"
#include "threewidget.h"

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/BlendFunc>
#include <osg/AutoTransform>
#include <osg/Depth>
#include <osg/LineWidth>
using namespace osg;

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
using namespace osgDB;

#include <osgText/Text>
using namespace osgText;

#include <osgViewer/ViewerBase>
using namespace osgViewer;
#include <osgUtil/Optimizer>
#include <osgUtil/LineSegmentIntersector>
using namespace osgUtil;

#include <set>
using namespace std;

namespace ThreeQt {

struct Basic::Finder : public NodeVisitor {
    Finder() : NodeVisitor(TRAVERSE_ALL_CHILDREN),precise(true),outMt(nullptr) {}
    virtual void apply(Geode& node) {
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
    Geode* outMt;
};

struct Basic::Plugin {
    ThreeWidget* tw;
    ref_ptr<Camera> background;
    ref_ptr<Group> bubbles;
};

Basic::Basic(ThreeWidget* tw)
{
    md = new Basic::Plugin;
    md->tw = tw;

    md->background = new Camera;
    md->background->setClearMask(0);
    md->background->setCullingActive( false );
    md->background->setAllowEventFocus( false );
    md->background->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    md->background->setRenderOrder( osg::Camera::POST_RENDER );
    md->background->setProjectionMatrix( osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0) );

    StateSet* ss = md->background->getOrCreateStateSet();
    ss->setMode( StateAttribute::LIGHT, osg::StateAttribute::OFF);
    ss->setAttributeAndModes(new Depth(Depth::LEQUAL, 1.0, 1.0));

    md->tw->worldScene->addChild(md->background);
    md->bubbles = new Group();
    md->tw->initScene->addChild(md->bubbles);
}

Basic::~Basic()
{
    md->tw->worldScene->removeChild(md->background);
    delete md;
}

void Basic::modelRemove(string name,bool precise) throw(exception) {
    Finder nv; nv.precise=precise; nv.inName = name; md->tw->worldScene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to remove model because the name not found!");
    md->tw->worldScene->removeChild(nv.outMt);
}

string Basic::createBase(vec3 center,int length,int interval) {
    ref_ptr<Geode> sd = new Geode;
    stringstream fmt; fmt << "base" << endl
                          << hex << reinterpret_cast<unsigned long long>(sd.get()) << endl
                          << "Basic::Model";

    sd->setName(fmt.str());

    ref_ptr<Geometry> square = new osg::Geometry();

    auto v_square = new Vec3Array();
    v_square->push_back(Vec3(get<0>(center),get<1>(center),get<2>(center)));
    v_square->push_back(Vec3(get<0>(center) + length * interval,get<1>(center),get<2>(center)));
    v_square->push_back(Vec3(get<0>(center) + length * interval,get<1>(center) + length * interval,get<2>(center)));
    v_square->push_back(Vec3(get<0>(center),get<1>(center) + length * interval,get<2>(center)));

    square->setVertexArray(v_square);
    square->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS,0,4));

    auto colors = new Vec4Array;
    colors->push_back(Vec4(1.0f,1.0f,1.0f,0.1f)); // white
    colors->push_back(Vec4(1.0f,1.0f,1.0f,0.1f)); // white
    colors->push_back(Vec4(1.0f,1.0f,1.0f,0.1f)); // white
    colors->push_back(Vec4(1.0f,1.0f,1.0f,0.1f)); // white

    square->setColorArray(colors, Array::BIND_PER_VERTEX);

    auto blendFunc = new BlendFunc();
    blendFunc->setSource(BlendFunc::SRC_ALPHA);
    blendFunc->setDestination(BlendFunc::ONE_MINUS_CONSTANT_ALPHA);

    auto ss = sd->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc);
    ss->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    sd->addDrawable(square);

    md->tw->worldScene->addChild(sd);
    return sd->getName();
}

string Basic::lineDraw(vec3 beginPos,vec3 endPos,int width) {
    ref_ptr<Geode> geode = new Geode();
    ref_ptr<Vec3Array> vetexs = new Vec3Array();
    ref_ptr<Geometry> geometry = new Geometry();

    vetexs->push_back(Vec3(get<0>(beginPos), get<1>(beginPos),get<2>(beginPos)));
    vetexs->push_back(Vec3(get<0>(endPos), get<1>(endPos), get<2>(endPos)));
    geometry->setVertexArray(vetexs);

    auto stateset = geode->getOrCreateStateSet();
    auto lineWidth = new LineWidth(4.0f);

    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    stateset->setAttribute(lineWidth);
    geometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, 2));

    auto colors = new Vec4Array;
    colors->push_back(Vec4(1.0f,0.0f,0.0f,0.5f)); // white
    colors->push_back(Vec4(1.0f,0.0f,0.0f,0.5f)); // white
    geometry->setColorArray(colors, osg::Array::BIND_PER_VERTEX);
    geode->addDrawable(geometry);
    md->tw->worldScene->addChild(geode);

    stringstream fmt; fmt << "line" << endl
                          << hex << geode.get() << endl
                          << "Basic::Model";

    geode->setName(fmt.str());
    return fmt.str();
}

string Basic::makeMark(vec3 xyz) {
    auto ps = new DrawElementsUInt(PrimitiveSet::LINES);
    ps->push_back(0);
    ps->push_back(1);
    ps->push_back(2);
    ps->push_back(3);

    auto v = new Vec3Array();
    v->push_back(Vec3(-8,8,0));
    v->push_back(Vec3(8,-8,0));
    v->push_back(Vec3(8,8,0));
    v->push_back(Vec3(-8,-8,0));

    auto c = new Vec4Array();
    c->push_back(Vec4(0,1,0,1));
    c->push_back(Vec4(0,1,0,1));
    c->push_back(Vec4(0,1,0,1));
    c->push_back(Vec4(0,1,0,1));

    auto geom = new Geometry();
    geom->setVertexArray(v);
    geom->setColorArray(c);
    geom->addPrimitiveSet(ps);
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    auto geode = new Geode();
    auto ss = geode->getOrCreateStateSet();
    ss->setMode(GL_DEPTH_TEST,StateAttribute::OFF);
    geode->addDrawable(geom);

    auto mt = new MatrixTransform();
    mt->setMatrix(Matrix::translate(Vec3d{get<0>(xyz),get<1>(xyz),get<2>(xyz)}));

    auto ar = new AutoTransform;
    ar->setAutoRotateMode(AutoTransform::ROTATE_TO_SCREEN);
    ar->setAutoScaleToScreen(true);
    ar->addChild(geode);
    mt->addChild(ar);

    stringstream fmt; fmt << "mark_" << endl
                          << hex << mt << endl
                          << "Basic::Model";

    mt->setName(fmt.str());
    md->tw->worldScene->addChild(mt);
    return fmt.str();
}

}
