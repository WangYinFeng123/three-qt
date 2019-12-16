#include "shadow.h"
#include "threewidget.h"

#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
using namespace osg;

#include <osgDB/ReadFile>
using namespace osgDB;
#include <osgText/Text>
using namespace osgText;
#include <osgAnimation/Animation>
#include <osgAnimation/BasicAnimationManager>
using namespace osgAnimation;
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgShadow/ShadowVolume>
using namespace osgShadow;

#include <set>
using namespace std;

#include <QSettings>

namespace Shadow {
    struct Shadow_Plugin {
        ThreeWidget* tw;
        ref_ptr<ShadowedScene> scene;
    };

    Plugin* CreateThreePlugin(ThreeWidget* tw) {
        Shadow_Plugin* p = new Shadow_Plugin;
        p->tw = tw;

        LightSource* ls = new LightSource;
        ls->getLight()->setLightNum(1);
        Vec3 pos(5000.0,-5000.0,10000.0);
        ls->getLight()->setPosition(Vec4(pos,0.0));
        Vec3 dir = -pos;
        dir.normalize();
        ls->getLight()->setDirection(dir);
        ls->getLight()->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        ls->getLight()->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        ls->getLight()->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

#if defined(QOPENGLWIDGET)
        ShadowVolume* shadowMap = new ShadowVolume;
#else
        ShadowMap* shadowMap = new ShadowMap;
        shadowMap->setTextureSize(Vec2s(640 * 8,480 * 8));
        shadowMap->setAmbientBias(Vec2(0.8f,0.5f));
        shadowMap->setLight(ls);
#endif
        p->scene = new ShadowedScene(shadowMap);
        p->scene->setCastsShadowTraversalMask(0x1 << 3);
        p->scene->setReceivesShadowTraversalMask(0x1 << 4);
        p->scene->addChild(ls);
        p->scene->addChild(p->tw->worldScene);
        return reinterpret_cast<Plugin*>(p);
    }

    void DestoryThreePlugin(Plugin* p) {
        delete reinterpret_cast<Shadow_Plugin*>(p);
    }

    void Lighting(Plugin* plugin,bool enable) {
        Shadow_Plugin* p =reinterpret_cast<Shadow_Plugin*>(plugin);
        StateSet* ss = p->scene->getOrCreateStateSet();

        if(enable) {
            p->tw->initScene->replaceChild(p->tw->worldScene,p->scene);
	    ss->setMode(GL_LIGHT1,StateAttribute::ON);
	}
        else {
            p->tw->initScene->replaceChild(p->scene,p->tw->worldScene);
	    ss->setMode(GL_LIGHT1,StateAttribute::OFF);
	}
    }
}
