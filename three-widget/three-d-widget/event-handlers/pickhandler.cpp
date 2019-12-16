#include "pickhandler.h"

#include <osg/Matrix>
using osg::Matrix;
#include <osg/MatrixTransform>
using osg::MatrixTransform;
#include <osgViewer/Viewer>
using osgViewer::Viewer;
using osgViewer::View;
#include <osgUtil/LineSegmentIntersector>
using osgUtil::LineSegmentIntersector;
using osgUtil::Intersector;
#include <osgUtil/IntersectVisitor>
using osgUtil::IntersectionVisitor;
#include <osg/Shader>
using osg::Shader;
#include <osg/Uniform>
using osg::Uniform;
#include <osg/NodeVisitor>
using osg::NodeVisitor;
#include <osg/Vec4>
using osg::Vec4;
#include <osg/CopyOp>
using osg::CopyOp;

#include <iostream>
#include <sstream>
using namespace std;

PickHandler::PickHandler()
{}

PickHandler::~PickHandler() {
    if(stateSet.valid()) stateSet->removeAttribute(program);
}

bool PickHandler::handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor*) {
    if(!scene.valid()) scene = dynamic_cast<Group*>(obj);

    switch(ea.getEventType()) {
    case GUIEventAdapter::MOVE: {
        break;}
    case GUIEventAdapter::PUSH: {
        if(stateSet.valid()) stateSet->removeAttribute(program);
        stateSet = nullptr;

        if(GUIEventAdapter::MIDDLE_MOUSE_BUTTON == ea.getButtonMask()) { if(canceled)canceled();break; }
        if(GUIEventAdapter::LEFT_MOUSE_BUTTON != ea.getButtonMask()) { if(canceled)canceled(); break; }

        auto view = dynamic_cast<View*>(&aa);
        LineSegmentIntersector::Intersections lis;
        if(!view->computeIntersections(ea.getX(),ea.getY(),lis,0x2)) { if(canceled) canceled();break;}

        auto li = *lis.begin();
        auto xyz = li.getWorldIntersectPoint();
        auto ss = li.drawable->getOrCreateStateSet();

        map<string,string> details;
        stringstream ssId,ssXyz;
        ssId << reinterpret_cast<long long>(li.drawable.get());
        details["id"] = ssId.str();
        details["library"] = li.drawable->libraryName();
        details["class"] = li.drawable->className();
        details["name"] = li.drawable->getName();
        ssXyz << "[" << xyz.x() << ',' << xyz.y() << ',' << xyz.z() << ']';
        details["xyz"] = ssXyz.str();
        if(stateSet == ss) { stateSet = nullptr; if(canceled)canceled(); break; }
        stateSet = ss;
        setShaders(ss);
        if(pickedModel) pickedModel(details);
        break;}
    default:break;
    }

    return false;
}

void PickHandler::remove(Node* modelID) {
    scene->removeChild(modelID);
}

static const char* vertSource = "\
        void main() {\
            gl_Position = ftransform();\
        }\
                                ";

static const char* fragSource = "\
        uniform vec4 mainColor;\
        void main() {\
            gl_FragColor = mainColor;\
        }\
                                ";

struct ColorCallback : public Uniform::Callback {
    ColorCallback() : incRed(false) {}
    virtual void operator()(Uniform* uniform, NodeVisitor*) {
        if(!uniform) return;

        Vec4 color;
        uniform->get(color);

        if(incRed) {
            if(color.y() < 1.0) color.y() += 0.01;
            else incRed = false;
        } else {
            if(color.y() > 0.0) color.y() -= 0.01;
            else incRed = true;
        }

        uniform->set(color);
    }

    bool incRed;
};

void PickHandler::setShaders(StateSet* ss) {
    auto vertShader = new Shader(Shader::VERTEX,vertSource);
    auto fragShader = new Shader(Shader::FRAGMENT,fragSource);
    program = new Program;
    program->addShader(vertShader);
    program->addShader(fragShader);
    auto mainColor = new Uniform("mainColor",Vec4(1.0,0.5,0.5,0.5));
    mainColor->setUpdateCallback(new ColorCallback);
    ss->addUniform(mainColor);
    ss->setAttributeAndModes(program);
}
