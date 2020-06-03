#include "stretcher.h"
#include "threewidget.h"

#include <iostream>
#include <sstream>
#include <set>
#include <mutex>
using namespace std;

#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/BlendFunc>
#include <osg/AutoTransform>
#include <osg/PositionAttitudeTransform>
using namespace osg;

#include <osgUtil/PolytopeIntersector>
using namespace osgUtil;

#include <osgText/Text>
using namespace osgText;

namespace ThreeQt {

struct Stretcher::Finder : public NodeVisitor {
    Finder() : NodeVisitor(TRAVERSE_ALL_CHILDREN),precise(true),outMt(nullptr) {}
    virtual void apply(PositionAttitudeTransform& node) {
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
    PositionAttitudeTransform* outMt;
};

struct Stretcher::Plugin {
    Editor* ep;
    Controller* cp;
    Stretcher* stp;
    ref_ptr<Group> marks;

    function<void(set<string> name)> pickedEventHandler;
    function<void(string name,vec3 pos)> changedEventHandler;
    function<void()> changedFinishedEventHandler;

    tuple<string,vec3,Vec3,Matrix> intersectWithVertex(vec2 xy, unsigned int mask) {
        LineSegmentIntersector::Intersections lis;
        if(!ep->owner()->viewer->computeIntersections(get<0>(xy),get<1>(xy),lis,mask)) return {"",{0,0,0},{0,0,0},Matrix()};

        string name;
        Vec3 worldPoint,localPoint;
        LineSegmentIntersector::Intersection hit;

        for(auto li : lis) {
            auto np = li.nodePath;
            for(auto n : np) {
                if(string::npos == n->getName().find("\nEditor::")) continue;
                name = n->getName();
                break;
            }

            hit = li;
            worldPoint = li.getWorldIntersectPoint();
            if(!name.empty()) break;
        }

        auto point = worldPoint;
        auto score = DBL_MAX;

        auto geometra = dynamic_cast<Geometry*>(hit.drawable.get());
        auto vertexs =  dynamic_cast<Vec3Array*>(geometra->getVertexArray());
        Vec3 vertexPicked,vertexNavtive;
        Matrix worldMatrix;


        for(auto v : *vertexs) {
            for(auto wm : hit.drawable->getWorldMatrices()) {
                auto mv = (v * wm);
                auto sample = point - mv;
                auto difference = sample.normalize();

                if(difference < score) {
                    score = difference;
                    vertexPicked = mv;
                    worldMatrix = wm;
                    vertexNavtive = v;
                }
            }
        }

        if(string::npos == name.find("\nEditor::")) name = "";
        return {name,{vertexPicked[0],vertexPicked[1],vertexPicked[2]},vertexNavtive,worldMatrix};
    }

    bool absorbing;
    vec3 beginPosAbsorbed;
    string modelNameAbsorbed,absorptionName;
    Matrix worldMatrix;
    Vec3 vertexNative;

    function<void(vec2 xy)> mouseOverHandler() {
        return [&](vec2 xy) {
            stp->markRemove(absorptionName);
            absorptionName = "";

            auto it = intersectWithVertex(xy,0b10);
            modelNameAbsorbed = get<0>(it);
            beginPosAbsorbed = get<1>(it);
            vertexNative = get<2>(it);
            worldMatrix = get<3>(it);

            absorptionName = stp->markDraw(beginPosAbsorbed);
        };
    };

    function<bool(Controller::MouseButton,Controller::MouseEventType,vec2,vec2)> mouseClickHandler() {
        return [=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
            Finder nv;

            if(mb == Controller::Left && met == Controller::Push) {
                absorbing = !modelNameAbsorbed.empty(); //判断是否吸附
                nv.inName = modelNameAbsorbed; this->ep->owner()->worldScene->accept(nv);
                if(nullptr == nv.outMt) absorbing = false;

            }
            else if(mb == Controller::Left && met == Controller::Drag) {
                if(absorbing) {
                    auto kv = intersectWithVertex(xy,0b10);
                    auto end = get<1>(kv);
                    if(get<0>(kv).empty()) end = get<1>(ep->intersect(xy,0b01));
                    auto begin = beginPosAbsorbed;

                    beginPosAbsorbed = end;
                }
            }
            else if(met == Controller::Release) {
                if(absorbing) {  //吸附时
                    absorbing = false;
                }
            }

            return false;
        };
    }
};

Stretcher::Stretcher(Editor* ep)
{
    md = new Plugin;
    md->ep = ep;
    md->cp = new Controller(ep->owner());
    md->stp = this;
    md->marks = new Group();
    md->absorbing = false;
    ep->owner()->worldScene->addChild(md->marks);
    md->cp->setMouseOverEventHandler(md->mouseOverHandler());
    md->cp->setMouseClickEventHandler(md->mouseClickHandler());
}

Stretcher::~Stretcher()
{
    md->ep->owner()->worldScene->removeChild(md->marks);
    delete md->cp;
    delete md;
}

void Stretcher::markRemove(string name) throw(exception) {
    for(int i=0;i < md->marks->getNumChildren();i++) {
        if(name == md->marks->getChild(i)->getName()) {
            md->marks->removeChild(i);
            break;
        }
    }
}

string Stretcher::markDraw(vec3 xyz) {
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
    ss->setMode(GL_LIGHTING, StateAttribute::OFF);
    geode->addDrawable(geom);

    auto mt = new MatrixTransform();
    mt->setMatrix(Matrix::translate(Vec3d{get<0>(xyz),get<1>(xyz),get<2>(xyz)}));

    auto ar = new AutoTransform;
    ar->setAutoRotateMode(AutoTransform::ROTATE_TO_SCREEN);
    ar->setAutoScaleToScreen(true);
    ar->addChild(geode);
    mt->addChild(ar);

    stringstream fmt; fmt << "pick" << endl
                          << hex << mt << endl
                          << "Picker::Model";

    mt->setName(fmt.str());
    md->marks->addChild(mt);
    return fmt.str();
}


}
