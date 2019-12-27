#include "controller.h"
#include "threewidget.h"

#include <osgGA/GUIEventHandler>
using osgGA::GUIEventHandler;
using osgGA::GUIEventAdapter;
using osgGA::GUIActionAdapter;
#include <osgUtil/LineSegmentIntersector>
using osgUtil::LineSegmentIntersector;
using osgUtil::Intersector;
#include <osgUtil/IntersectVisitor>
using osgUtil::IntersectionVisitor;
using osgViewer::View;
using osg::Vec3;
using osg::NodePath;
using osg::Transform;

#include <iostream>
using namespace std;

namespace ThreeQt {
struct Controller::Plugin {
    ThreeWidget* tw;
    ref_ptr<EventHandler> handler;
};

struct Controller::EventHandler : public GUIEventHandler {
    function<void(vec2 xy)> mouseOverCallback;
    function<void(bool,int)> mouseKeyboardCallback;
    function<bool(MouseButton,MouseEventType,vec2 xy,vec2 xyNormalized)> mouseClickCallback;
    function<bool(ScrollingMotion,double)> mouseWheelCallback;
    function<void()> frameCallback;

    bool scroll;
    ScrollingMotion sm;
    double t;
    MouseButton mb;

    EventHandler() : GUIEventHandler(), scroll(false), t(0) {}

    virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor*) {
        auto et = ea.getEventType();
        auto bm = ea.getButtonMask();
        auto key = ea.getKey();

        switch(et) {
        case GUIEventAdapter::MOVE:
            if(!mouseOverCallback) break;
            mouseOverCallback({ea.getX(),ea.getY()});
            break;
        case GUIEventAdapter::PUSH:
            if(!mouseClickCallback) break;
            mb = static_cast<MouseButton>(bm);
            if((ea.getTime() - t) < 0.25)
                t = 0.0,mouseClickCallback(mb,static_cast<MouseEventType>(GUIEventAdapter::DOUBLECLICK),{ea.getX(),ea.getY()},{ea.getXnormalized(),ea.getYnormalized()});
            else
                t = ea.getTime();
        case GUIEventAdapter::DRAG:
        case GUIEventAdapter::RELEASE:
            if(!mouseClickCallback) break;
            return mouseClickCallback(mb,static_cast<MouseEventType>(et),{ea.getX(),ea.getY()},{ea.getXnormalized(),ea.getYnormalized()});
        case GUIEventAdapter::FRAME:
            if(!frameCallback) break;
            frameCallback();
        case GUIEventAdapter::KEYDOWN:
            if(mouseKeyboardCallback) mouseKeyboardCallback(true,key);
            break;
        case GUIEventAdapter::KEYUP:
            if(mouseKeyboardCallback) mouseKeyboardCallback(false,key);
            break;
        default:break;
        }

        return false;
    };
};

Controller::Controller(ThreeWidget* tw) {
    md = new Plugin;
    md->tw = tw;
    md->handler = new EventHandler;
    md->tw->viewer->addEventHandler(md->handler);
}
Controller::~Controller() {
    md->tw->viewer->removeEventHandler(md->handler);
    delete md;
}

void Controller::setMouseOverEventHandler(function<void (vec2 xy)> f) {
    md->handler->mouseOverCallback = f;
}

void Controller::setKeyboardEventhandler(function<void(bool pressed,int key)> f) {
    md->handler->mouseKeyboardCallback = f;
}

void Controller::setMouseClickEventHandler(function<bool (MouseButton, MouseEventType,vec2 xy,vec2 xyNormalized)> f) {
    md->handler->mouseClickCallback = f;
}

void Controller::setMouseWheelEventHandler(function<bool(ScrollingMotion,double distance)> f) {
    md->handler->mouseWheelCallback = f;
}
void Controller::setFrameEventHandler(function<void()> f) {
    md->handler->frameCallback = f;
}

}
