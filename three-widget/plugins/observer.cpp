#include "observer.h"
#include "threewidget.h"
#include "threemanipulator.h"
#include "teleportmanipulator.h"

#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/Depth>
using namespace osg;

#include <osgDB/ReadFile>
using namespace osgDB;

#include <osgText/Text>
using namespace osgText;

#include <osgViewer/ViewerBase>
using namespace osgViewer;
#include <osgUtil/Optimizer>

#include <osgGA/FirstPersonManipulator>
using osgGA::FirstPersonManipulator;

#include <set>
using namespace std;

#include <QSettings>

static QSettings settings(GLOBAL_COMPANY,GLOBAL_NAME);

namespace Observer {
    struct Observer_Plugin {
        ThreeWidget* tw;
        ref_ptr<ThreeManipulator> tm;
        ref_ptr<TeleportManipulator> tpm;
    };

    struct Observer_LookingForVisitor : public NodeVisitor {
        Observer_LookingForVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
        virtual void apply(MatrixTransform& node) {
            if(node.getName() == inName && 0 < node.getBound().radius()) {
                outNode = &node;
            }

            traverse(node);
        }

        string inName;
        MatrixTransform* outNode;
    };

    Plugin* CreateThreePlugin(ThreeWidget* tw) {
        Observer_Plugin* p = new Observer_Plugin;
        p->tw = tw;
        p->tm = tw->tm;
        p->tpm = new TeleportManipulator();
        p->tpm->setAllowThrow(false);
        return reinterpret_cast<Plugin*>(p);
    }

    void DestoryThreePlugin(Plugin* plugin) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        delete p;
    }

    void SwitchFirstPerson(Plugin* plugin,bool enable) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        Vec3d e,c,u;
        Quat r;
        if(enable) {
            p->tm->getTransformation(e,r);
            p->tw->viewer->setCameraManipulator(p->tpm);
            p->tpm->setTransformation(e,r);

            p->tm->getHomePosition(e,c,u);
            p->tpm->setHomePosition(e,c,u);
        } else {
            p->tpm->getTransformation(e,r);
            p->tw->viewer->setCameraManipulator(p->tm);
            p->tm->setTransformation(e,r);

//            p->tpm->getTransformation(e,c,u);
//            double distance = (p->tm->getCenter() - c).length();
//            p->tm->setCenter(c);
        }
    }

    void LookingFor(Plugin* plugin,string name) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        if(name.empty()) return;

        Observer_LookingForVisitor nv;
        nv.inName = name;
        p->tw->worldScene->accept(nv);
        if(NULL == nv.outNode) return;
        if(0 == nv.outNode->getNumChildren()) return;

        BoundingSphere b = nv.outNode->getBound();
        if(0 == nv.outNode->getNumChildren()) return;
        Vec3 center = nv.outNode->getChild(0)->getBound().center() * nv.outNode->getWorldMatrices()[0];
        float distance = b.radius() * 4;
        p->tm->teleport(p->tw->viewer->getEventQueue(),center,distance);
    }

    void LookingFor(Plugin* plugin,float xyz[3],float distance) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        if(xyz == NULL) return;

        Vec3 center(xyz[0],xyz[1],xyz[2]);
        p->tm->teleport(p->tw->viewer->getEventQueue(),center,distance);
    }

    void Home(Plugin* plugin) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        p->tm->home(0);
    }

    void HomePosition(Plugin* plugin,float eye[3],float center[3],float up[3]) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);

        Vec3d e,c,u;
        p->tm->getHomePosition(e,c,u);
        eye[0] = e[0],eye[1] = e[1],eye[2] = e[2];
        center[0] = c[0],center[1] = c[1],center[2] = c[2];
        up[0] = u[0],up[1] = u[1],up[2] = u[2];
    }

    void SetHomePosition(Plugin* plugin,float eye[3],float center[3],float up[3]) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        p->tm->setHomePosition(Vec3(eye[0],eye[1],eye[2]),Vec3(center[0],center[1],center[2]),Vec3(up[0],up[1],up[2]));
    }

    void CameraPosition(Plugin* plugin,float eye[3],float center[3],float up[3]) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        Vec3d e,c,u;
        p->tm->getTransformation(e,c,u);
        eye[0] = e[0],eye[1] = e[1],eye[2] = e[2];
        center[0] = c[0],center[1] = c[1],center[2] = c[2];
        up[0] = u[0],up[1] = u[1],up[2] = u[2];
    }

    void SetCameraPosition(Plugin* plugin,float eye[3],float center[3],float up[3]) {
        Observer_Plugin* p = reinterpret_cast<Observer_Plugin*>(plugin);
        p->tm->setTransformation(Vec3(eye[0],eye[1],eye[2]),Vec3(center[0],center[1],center[2]),Vec3(up[0],up[1],up[2]));
    }
}
