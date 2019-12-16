#include "controls.h"
#include "threewidget.h"
#if defined(OSGEARTH)
#include "threeearthwidget.h"
#endif

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
using std::cout;
using std::cerr;
using std::endl;

namespace Controls {
    struct Controls_GUIEventHandler;

    struct Controls_Plugin {
        ThreeWidget* tw;
        ref_ptr<Controls_GUIEventHandler> handler;
    };

    struct Controls_GUIEventHandler : public GUIEventHandler {
#if defined(QT5)
        function<bool(string,float[3])> mouseOverCallback;
        function<bool(MouseButtonMask,string,float[3])> mouseClickCallback;
        function<bool(ScrollingMotion,double)> mouseWheelCallback;
#else
        MouseOverEventHandler* mouseOverCallback;
        MouseClickEventHandler* mouseClickCallback;
#endif
        bool scroll;
        ScrollingMotion sm;
        Controls_GUIEventHandler() : GUIEventHandler(),mouseOverCallback(NULL), mouseClickCallback(NULL), scroll(false) {}
        virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor*) {
            View* view = dynamic_cast<View*>(&aa);
            LineSegmentIntersector::Intersections lis;

            //鼠标事件
            switch(ea.getEventType()) {
            case GUIEventAdapter::MOVE: {
#if defined(QT5)
                if(!mouseOverCallback) break;
#else
                if(mouseOverCallback == NULL) break;
#endif
                if(!view->computeIntersections(ea.getX(),ea.getY(),lis,0x2)) {
#if defined(QT5)
                    return mouseOverCallback("",nullptr);
#else
                    return (*mouseOverCallback)("",NULL);
#endif
                }

                NodePath np = lis.begin()->nodePath;
                Transform* n = NULL;
                for(NodePath::reverse_iterator it = np.rbegin();np.rend() != it;it++) {
                    n = dynamic_cast<osg::Transform*>(*it);
                    if(n != NULL && !n->getName().empty()) break;
                }

                Vec3 point = lis.begin()->getWorldIntersectPoint();
                float xyz[3] = {point[0],point[1],point[2]};

#if defined(QT5)
                return mouseOverCallback(n->getName(),xyz);
#else
                return (*mouseOverCallback)(n->getName(),xyz);
#endif
                }
            case GUIEventAdapter::PUSH: {
#if defined(QT5)
                if(!mouseClickCallback) break;
#else
                if(mouseClickCallback == NULL) break;
#endif
                if(!view->computeIntersections(ea.getX(),ea.getY(),lis,0x2)) {
#if defined(QT5)
                    return mouseClickCallback(static_cast<MouseButtonMask>(ea.getButtonMask()),"",nullptr);
#else
                    return (*mouseClickCallback)(static_cast<MouseButtonMask>(ea.getButtonMask()),"",NULL);
#endif
                }
                NodePath np = lis.begin()->nodePath;
                Transform* n = NULL;
                for(NodePath::reverse_iterator it = np.rbegin();np.rend() != it;it++) {
                    n = dynamic_cast<osg::Transform*>(*it);
                    if(n != NULL && !n->getName().empty()) break;
                }
                Vec3 point = lis.begin()->getWorldIntersectPoint();
                float xyz[3] = {point[0],point[1],point[2]};
#if defined(QT5)
                return mouseClickCallback(static_cast<MouseButtonMask>(ea.getButtonMask()),n->getName(),xyz);
#else
                return (*mouseClickCallback)(static_cast<MouseButtonMask>(ea.getButtonMask()),n->getName(),xyz);
#endif
            }
            case GUIEventAdapter::SCROLL: {
#if defined(QT5)
                if(!mouseWheelCallback) break;
#endif
                ThreeManipulator* tm = dynamic_cast<ThreeManipulator*>(view->getCameraManipulator());
#if defined (OSGEARTH)
                auto em = dynamic_cast<EarthManipulator*>(view->getCameraManipulator());
#endif

                if(tm != NULL) {
#if defined(QT5)
                    return mouseWheelCallback(sm,tm->getDistance());
#endif
                }
#if defined (OSGEARTH)
                else if(em != nullptr) {
                    auto vp = em->getViewpoint();
                    return mouseWheelCallback(sm,vp.getRange());
                }
#endif
            }
            case GUIEventAdapter::FRAME:
                break;
            default:break;
            }

            return false;
        };
    };

    Plugin* CreateThreePlugin(ThreeWidget* tw) {
        Controls_Plugin* p = new Controls_Plugin;
        p->tw = tw;
        p->handler = new Controls_GUIEventHandler;
        p->tw->viewer->addEventHandler(p->handler);
        return reinterpret_cast<Plugin*>(p);
    }

    void DestoryThreePlugin(Plugin* plugin) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->tw->viewer->removeEventHandler(p->handler);
        delete reinterpret_cast<Controls_Plugin*>(p);
    }

    void SetMouseButton(Plugin* plugin,MouseButtonMask mouseCenter, MouseButtonMask mousePan,MouseButtonMask mouseRotate) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->tw->mouseLeft = mouseCenter;
        p->tw->mouseMid = mousePan;
        p->tw->mouseRight = mouseRotate;
    }

#if defined(QT5)
    void SetMouseWheel(Plugin* plugin,ScrollingMotion mouseWheelUp, ScrollingMotion mouseWheelDown) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->tw->mouseWheelUp = mouseWheelUp;
        p->tw->mouseWheelDown = mouseWheelDown;
    }

    void SetMouseOverEventHandler(Plugin* plugin,function<bool(string name,float xyz[3])> f) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->handler->mouseOverCallback = f;
    }

    void SetMouseClickEventHandler(Plugin* plugin,function<bool(MouseButtonMask,string name,float xyz[3])> f) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->handler->mouseClickCallback = f;
    }

    void SetMouseWheelEventHandler(Plugin* plugin,function<bool(ScrollingMotion,double distance)> f) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->handler->mouseWheelCallback = f;
    }
#else
    void SetMouseOverEventHandler(Plugin* plugin,MouseOverEventHandler* f) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->handler->mouseOverCallback = f;
    }

    void SetMouseClickEventHandler(Plugin* plugin,MouseClickEventHandler* f) {
        Controls_Plugin* p = reinterpret_cast<Controls_Plugin*>(plugin);
        p->handler->mouseClickCallback = f;
    }
#endif

#if defined (OSGEARTH)
    struct _Controls_EarthPlugin {
        ThreeEarthWidget* tew;
        ref_ptr<Controls_GUIEventHandler> handler;
    };

    EarthPlugin* CreateThreePlugin(ThreeEarthWidget* tew) {
        _Controls_EarthPlugin* p = new _Controls_EarthPlugin;
        p->tew = tew;
        p->handler = new Controls_GUIEventHandler;
        p->tew->viewer->addEventHandler(p->handler);
        return reinterpret_cast<EarthPlugin*>(p);
    }

    void DestoryThreePlugin(EarthPlugin* plugin) {
        _Controls_EarthPlugin* p = reinterpret_cast<_Controls_EarthPlugin*>(plugin);
        delete reinterpret_cast<_Controls_EarthPlugin*>(p);
    }

    void SetMouseWheelEventHandler(EarthPlugin* plugin,function<void(ScrollingMotion,double range)> f) {
        _Controls_EarthPlugin* p = reinterpret_cast<_Controls_EarthPlugin*>(plugin);
        p->handler->mouseWheelCallback = f;
    }
#endif
}
