#ifndef ADSORPTIONHANDLER_H
#define ADSORPTIONHANDLER_H

#include <osg/Node>
#include <osg/ref_ptr>
using namespace osg;

#include <osgGA/GUIEventHandler>
using namespace osgGA;

#include <functional>
using namespace std;

class AdsorptionHandler : public GUIEventHandler
{
    static const auto sizeMinimumOfNodePath = 4;
    static const auto indexFirstOfPicked = sizeMinimumOfNodePath - 1;
    static const auto KEY_S = 83;
public:
    static ref_ptr<MatrixTransform> makePicked(Vec3 center);
public:
    AdsorptionHandler(bool xyz[],function<void()> onFinish);
    virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);
    bool sPressed,lbPressed;
    Vec3 vertexPicked,vertexTargeted;
    ref_ptr<MatrixTransform> modelMatrixTransformPicked;
    Matrix modelMatrixPicked;
    ref_ptr<Node> lightPicked,lightTargeted;
    ref_ptr<Group> scene;
    bool xyz[4];
    function<void()> onFinish;
protected:
    virtual ~AdsorptionHandler();
};

#endif // ADSORPTIONHANDLER_H
