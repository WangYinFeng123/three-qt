#include "animationhandler.h"
#include "node-visitors/modelnodevisitor.h"

#include <osgAnimation/BasicAnimationManager>
using osgAnimation::BasicAnimationManager;

#include <set>
using std::set;
#include <iostream>
using std::cout;
using std::endl;

AnimationHandler::AnimationHandler()
{}

AnimationHandler::~AnimationHandler()
{}

list<string> AnimationHandler::animations(Node* model) {
    list<string> amNames;
    BasicAnimationManager* am = dynamic_cast<BasicAnimationManager*>(model->getUpdateCallback());
    if(NULL == am) return amNames;

    set<string> names;
    osgAnimation::AnimationList list = am->getAnimationList();
    for(osgAnimation::AnimationList::iterator it=list.begin();list.end() != it;it++) {
        ref_ptr<osgAnimation::Animation> ans = *it;
        osgAnimation::ChannelList channels = ans->getChannels();
        for(osgAnimation::ChannelList::iterator j =channels.begin();channels.end() != j;j++) {
            ref_ptr<osgAnimation::Channel> channel = *j;
            string name = channel->getTargetName();
            if(names.end() != names.find(name)) continue;
            amNames.push_back(name);
            names.insert(name);
        }
    }

    return amNames;
}

void AnimationHandler::play(Node* model,string name) {
    BasicAnimationManager* am = dynamic_cast<BasicAnimationManager*>(model->getUpdateCallback());
    if(NULL == am) return;

    osgAnimation::AnimationList list = am->getAnimationList();
    for(osgAnimation::AnimationList::iterator i=list.begin();list.end() != i;i++) {
        am->playAnimation(i->get());
        return;
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

    am->registerAnimation(namedAnimation);
    am->playAnimation(namedAnimation);
}

void AnimationHandler::stop(Node* model,string name) {
    BasicAnimationManager* am = dynamic_cast<BasicAnimationManager*>(model->getUpdateCallback());
    if(NULL == am) return;

    osgAnimation::AnimationList list = am->getAnimationList();
    for(osgAnimation::AnimationList::iterator i=list.begin();list.end() != i;i++) {
        am->playAnimation(i->get());
        return;
    }
}

void AnimationHandler::stopAll(Node* model) {
    BasicAnimationManager* am = dynamic_cast<BasicAnimationManager*>(model->getUpdateCallback());
    if(NULL == am) return;
    am->stopAll();
}

void AnimationHandler::update(Node* model,string name,double time) {
    BasicAnimationManager* am = dynamic_cast<BasicAnimationManager*>(model->getUpdateCallback());
    if(NULL == am) return;

    osgAnimation::AnimationList list = am->getAnimationList();
    for(osgAnimation::AnimationList::iterator i=list.begin();list.end() != i;i++) {
        if(i->get()->getName() != name) continue;
        i->get()->update(time);return;
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

    am->registerAnimation(namedAnimation);
    namedAnimation->setWeight(1.0);
    namedAnimation->setStartTime(0);
    namedAnimation->update(time);
}
