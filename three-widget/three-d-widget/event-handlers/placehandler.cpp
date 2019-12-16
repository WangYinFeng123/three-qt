#include "placehandler.h"
#include "node-visitors/modelnodevisitor.h"

#include <osg/Matrix>
using osg::Matrix;
#include <osg/MatrixTransform>
using osg::MatrixTransform;
#include <osgViewer/Viewer>
using osgViewer::Viewer;
#include <osgUtil/LineSegmentIntersector>
using osgUtil::LineSegmentIntersector;

#include <iostream>
using namespace std;

PlaceHandler::PlaceHandler() {
    placed = new MatrixTransform;
    scene = nullptr;
}

PlaceHandler::~PlaceHandler() {
    if(scene) scene->removeChild(placed);
}

void PlaceHandler::placeByMouse(ref_ptr<Node> model) {
    for(int i=0;i < placed->getNumChildren();i++) placed->removeChild(0,1);
    placed->addChild(model);
}

void PlaceHandler::place(ref_ptr<Node> model) {
    fns.push_back([=]() { scene->addChild(model); });
}

void PlaceHandler::remove(Node* modelAddress) {
    fns.push_back([=]() { scene->removeChild(modelAddress); });
}

bool PlaceHandler::handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object* node, osg::NodeVisitor*) {
    if(scene == nullptr) scene = dynamic_cast<Group*>(node);
    auto view = dynamic_cast<osgViewer::View*>(&aa);

    switch(ea.getEventType()) {
    case GUIEventAdapter::PUSH:
        if(GUIEventAdapter::RIGHT_MOUSE_BUTTON == ea.getButtonMask()) for(int i=0;i < placed->getNumChildren();i++) placed->removeChild(0,1);
        if(0 == placed->getNumChildren()
        || GUIEventAdapter::LEFT_MOUSE_BUTTON != ea.getButtonMask()) break;
        scene->addChild(dynamic_cast<Node*>(placed->clone(osg::CopyOp::SHALLOW_COPY)));
        return true;
    case GUIEventAdapter::MOVE: {
        if(0 == placed->getNumChildren()) break;
        scene->removeChild(placed);

        LineSegmentIntersector::Intersections lis;
        if(!view->computeIntersections(ea.getX(),ea.getY(),lis)) break;

        auto li = *lis.begin();
        auto pos = li.getWorldIntersectPoint();
        auto box = placed->getChild(0)->getBound();
        auto center = box.center();
        center.y() = 0;

        NearVertexVisitor nvv;
        placed->accept(nvv);
        auto offset = nvv.nearPoint();
        placed->setMatrix(Matrix::translate(pos - center - offset));
        scene->addChild(placed);
        return true;}
    case GUIEventAdapter::FRAME:{
        if(0 == fns.size()) break;
        auto fn = fns.front();
        fn();
        fns.pop_front();
        break;}
    default:break;
    }

    return false;
}
