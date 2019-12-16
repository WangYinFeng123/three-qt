#include "animations.h"
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

#include <set>
using namespace std;

#include <QSettings>

namespace Animations {
    struct Animations_Plugin {
        ThreeWidget* tw;
        ref_ptr<MatrixTransform> mtScene;
        ref_ptr<Node> scene;
    };

    struct AnimationVisitor : public NodeVisitor {
        BasicAnimationManager* am;
        AnimationVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
        virtual void apply(Node& node) {
            am = dynamic_cast<BasicAnimationManager*>(node.getUpdateCallback());
            if(NULL != am) return;
            traverse(node);
        }
    };

    Plugin* CreateThreePlugin(ThreeWidget* tw) {
        Animations_Plugin* p = new Animations_Plugin;
        p->tw = tw;

        return reinterpret_cast<Plugin*>(p);
    }

    void DestoryThreePlugin(Plugin* p) {
        delete reinterpret_cast<Animations_Plugin*>(p);
    }

    void TestAnimations(Plugin* plugin,bool enable) {
        Animations_Plugin* p = reinterpret_cast<Animations_Plugin*>(plugin);
        AnimationVisitor av;
        p->tw->worldScene->accept(av);
        cout << "[Animations] 动画管理器：" << av.am << endl;
        if(av.am == NULL) return;
        osgAnimation::AnimationList list = av.am->getAnimationList();
        for(osgAnimation::AnimationList::iterator i=list.begin();list.end() != i;i++) {
            if(enable) av.am->playAnimation(i->get());
            else {
                av.am->update(0);
                av.am->stopAnimation(i->get());
            }
        }
    }

    void SetModelState(Plugin* plugin,string name,double value) {
        Animations_Plugin* p = reinterpret_cast<Animations_Plugin*>(plugin);
        AnimationVisitor av;
        p->tw->worldScene->accept(av);
        if(NULL == av.am) return;

        osgAnimation::AnimationList list = av.am->getAnimationList();
        for(osgAnimation::AnimationList::iterator i=list.begin();list.end() != i;i++) {
            if(i->get()->getName() != name) continue;
            i->get()->update(value);
        }

        ref_ptr<Animation> namedAnimation = new Animation;
        namedAnimation->setName(name);

        for(osgAnimation::AnimationList::iterator it=list.begin();list.end() != it;it++) {
            ref_ptr<osgAnimation::Animation> ans = *it;
            osgAnimation::ChannelList channels = ans->getChannels();
            for(osgAnimation::ChannelList::iterator j =channels.begin();channels.end() != j;j++) {
                ref_ptr<osgAnimation::Channel> channel = *j;
                if(name != channel->getTargetName()) continue;
                namedAnimation->addChannel(channel);
            }
        }

        namedAnimation->setWeight(1.0);
        namedAnimation->setStartTime(0);
        namedAnimation->update(value);
    }

    set<string> Animations(Plugin* plugin) {
        Animations_Plugin* p = reinterpret_cast<Animations_Plugin*>(plugin);
        AnimationVisitor av;
        p->tw->worldScene->accept(av);

        set<string> names;
        if(NULL == av.am) return names;

        osgAnimation::AnimationList animations = av.am->getAnimationList();
        for(osgAnimation::AnimationList::iterator i=animations.begin();animations.end()!=i;i++) {
            osgAnimation::Animation* a=*i;
            osgAnimation::ChannelList channels = a->getChannels();
            for(osgAnimation::ChannelList::iterator j=channels.begin();channels.end()!=j;j++) {
                osgAnimation::Channel* c = *j;
                std::string name = c->getTargetName();
                if(names.end() != names.find(name)) continue;
                names.insert(name);
                std::cout << "动画：" << name << std::endl;
            }
        }

        return names;
    }
}

