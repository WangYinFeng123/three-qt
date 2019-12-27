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
#include <osgShadow/SoftShadowMap>
using namespace osgShadow;

#include <set>
using namespace std;

namespace ThreeQt {
    struct Shadow::Plugin {
        ThreeWidget* tw;
        ref_ptr<ShadowedScene> scene;
    };

    Shadow::Shadow(ThreeWidget* tw) {
        md = new Plugin();
        md->tw = tw;

        LightSource* ls = new LightSource;
        ls->getLight()->setLightNum(1);

        auto box = md->tw->worldScene->getBound();
        auto pos = box.center();
        pos.x() += box.radius();
        pos.z() += box.radius();
        pos.y() -= box.radius();

        ls->getLight()->setPosition(Vec4(pos,0.0));
        Vec3 dir = -pos;
        dir.normalize();
        ls->getLight()->setDirection(dir);
        ls->getLight()->setAmbient(osg::Vec4(1.6f, 1.6f, 1.6f, 1.0f));
        ls->getLight()->setDiffuse(osg::Vec4(1.6f, 1.6f, 1.6f, 1.0f));
        ls->getLight()->setSpecular(osg::Vec4(2.0f, 2.0f, 2.0f, 1.0f));

        auto shadowMap = new SoftShadowMap;
        shadowMap->setLight(ls);

        md->scene = new ShadowedScene(shadowMap);
        md->scene->addChild(ls);
        md->scene->addChild(md->tw->worldScene);
    }

    Shadow::~Shadow() {
        delete md;
    }

    void Shadow::lighting(bool enable) {
        StateSet* ss = md->scene->getOrCreateStateSet();

        if(enable) {
            md->tw->initScene->replaceChild(md->tw->worldScene,md->scene);
            ss->setMode(GL_LIGHT1,StateAttribute::ON);
        } else {
            md->tw->initScene->replaceChild(md->scene,md->tw->worldScene);
            ss->setMode(GL_LIGHT1,StateAttribute::OFF);
        }
    }
}
