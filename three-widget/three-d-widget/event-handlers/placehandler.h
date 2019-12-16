#ifndef PLACEHANDLER_H
#define PLACEHANDLER_H

#include <osg/ref_ptr>
using osg::ref_ptr;
#include <osg/Node>
using osg::Node;
#include <osg/MatrixTransform>
using osg::MatrixTransform;
#include <osg/Group>
using osg::Group;
#include <osgGA/GUIEventHandler>
using osgGA::GUIEventHandler;
using osgGA::GUIEventAdapter;
using osgGA::GUIActionAdapter;
#include <list>
using std::list;
#include <functional>
using std::function;

class PlaceHandler : public GUIEventHandler
{
public:
    PlaceHandler();
    virtual ~PlaceHandler();
    virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);
    void placeByMouse(ref_ptr<Node> model);
    void place(ref_ptr<Node> model);
    void remove(Node* modelAddress);
private:
    Group* scene;
    ref_ptr<MatrixTransform> placed;
    list<function<void()>> fns;
};

#endif // PLACEHANDLER_H
