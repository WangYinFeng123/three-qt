#ifndef PICKHANDLER_H
#define PICKHANDLER_H

#include <osg/ref_ptr>
using osg::ref_ptr;
#include <osg/Node>
using osg::Node;
#include <osg/Group>
using osg::Group;
#include <osg/MatrixTransform>
using osg::MatrixTransform;
#include <osgGA/GUIEventHandler>
using osgGA::GUIEventHandler;
using osgGA::GUIEventAdapter;
using osgGA::GUIActionAdapter;
#include <osgManipulator/CommandManager>
using osgManipulator::CommandManager;
#include <osgManipulator/Dragger>
using osgManipulator::Dragger;
#include <osgManipulator/TranslateAxisDragger>
using osgManipulator::TranslateAxisDragger;
#include <osgManipulator/TrackballDragger>
using osgManipulator::TrackballDragger;
#include <osgManipulator/ScaleAxisDragger>
using osgManipulator::ScaleAxisDragger;
#include <osgManipulator/TabBoxDragger>
using osgManipulator::TabBoxDragger;
#include <osg/Program>
using osg::Program;
#include <osg/StateSet>
using osg::StateSet;
#include <osgViewer/Viewer>
using osgViewer::Viewer;
using osgViewer::View;

#include <list>
#include <map>
using namespace std;

class PickHandler : public GUIEventHandler
{
public:
    PickHandler();
    virtual ~PickHandler();
    virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);
    void remove(Node* modelID);

    function<void(map<string,string>)> pickedModel,hoveredModel;
    function<void()> canceled;
private:
    void setShaders(StateSet* ss);
    ref_ptr<Group> scene;
    ref_ptr<MatrixTransform> pickedObject;
    ref_ptr<Program> program;
    ref_ptr<StateSet> stateSet;
};

#endif // PICKHANDLER_H
