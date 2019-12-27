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

#include <map>
#include <set>
using namespace std;

#include <QSettings>

namespace ThreeQt {
    struct Animations::Plugin {
        ThreeWidget* tw;
        ref_ptr<MatrixTransform> mtScene;
        ref_ptr<Node> scene;
    };

    struct Animations::AnimationVisitor : public NodeVisitor {
        map<string,BasicAnimationManager*> ams;

        AnimationVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
        virtual void apply(Node& node) {
            auto am = dynamic_cast<BasicAnimationManager*>(node.getUpdateCallback());
            if(nullptr != am) ams[am->getName()] = am;
            traverse(node);
        }
    };

    Animations::Animations(ThreeWidget* tw) {
        md = new Plugin;
        md->tw = tw;
    }

    Animations::~Animations() {
        delete md;
    }

    void Animations::TestAnimations(bool enable) {
        AnimationVisitor av;
        md->tw->worldScene->accept(av);
        cout << "[Animations] 动画管理器：" << av.ams.size() << endl;

        for(auto kv : av.ams) {
            osgAnimation::AnimationList list = kv.second->getAnimationList();
            for(osgAnimation::AnimationList::iterator i=list.begin();list.end() != i;i++) {
                if(enable) kv.second->playAnimation(i->get());
                else {
                    kv.second->update(0);
                    kv.second->stopAnimation(i->get());
                }
            }
        }
    }

    void Animations::TestAnimation(string animationName,bool enable) {
        AnimationVisitor av;
        md->tw->worldScene->accept(av);

        for(auto kv : av.ams) {
            osgAnimation::AnimationList list = kv.second->getAnimationList();
            ref_ptr<Animation> namedAnimation = new Animation;
            namedAnimation->setName(animationName);
            for(osgAnimation::AnimationList::iterator it=list.begin();list.end() != it;it++) {
                ref_ptr<osgAnimation::Animation> ans = *it;
                osgAnimation::ChannelList channels = ans->getChannels();
                for(osgAnimation::ChannelList::iterator j =channels.begin();channels.end() != j;j++) {
                    ref_ptr<osgAnimation::Channel> channel = *j;
                    if(animationName == channel->getTargetName())
                    {
                        namedAnimation->addChannel(channel);
                    }
                }
            }

          //  namedAnimation->setPlayMode(osgAnimation::Animation::STAY);
          //  namedAnimation->setWeight(1.0);
          //  namedAnimation->setStartTime(0);

            if(enable)
            {
                kv.second->registerAnimation(namedAnimation);
                kv.second->playAnimation(namedAnimation);
                kv.second->unregisterAnimation(namedAnimation);
            }
            else{
                kv.second->stopAll();
            }
        }
    }

    void Animations::SetModelState(string name,double value) {
        AnimationVisitor av;
        md->tw->worldScene->accept(av);

        for(auto kv : av.ams) {
            osgAnimation::AnimationList list = kv.second->getAnimationList();
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
    }

    set<string> Animations::AnimationNames(string modelName) {
        AnimationVisitor av;
        md->tw->worldScene->accept(av);

        set<string> names;
        for(auto kv : av.ams) {
            if(modelName == kv.first) continue;
            cout << kv.first << endl;

            osgAnimation::AnimationList animations = kv.second->getAnimationList();
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
        }

        return names;
    }
}
