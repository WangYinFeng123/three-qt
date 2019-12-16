#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <osg/Node>
using osg::Node;
#include <osg/Group>
using osg::Group;
#include <osgGA/GUIEventHandler>
using osgGA::GUIEventHandler;
using osgGA::GUIEventAdapter;
using osgGA::GUIActionAdapter;
#include <osg/ref_ptr>
using osg::ref_ptr;
#include <string>
using std::string;
#include <list>
using std::list;
#include <map>
using std::map;
#include <osgAnimation/Animation>
using osgAnimation::Animation;

class AnimationHandler : public GUIEventHandler
{
public:
    AnimationHandler();
    virtual ~AnimationHandler();
    list<string> animations(Node* model);
    void play(Node* model,string name);
    void stop(Node* model,string name);
    void stopAll(Node* model);
    void update(Node* model,string name,double time);
};

#endif // ANIMATIONHANDLER_H
