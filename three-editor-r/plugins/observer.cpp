#include "observer.h"
#include "threewidget.h"

#include <osgGA/OrbitManipulator>
using osgGA::OrbitManipulator;
#include <osgGA/EventQueue>
using osgGA::EventQueue;
#include <osg/Vec3>
using osg::Vec3;
#include <osgGA/GUIEventAdapter>
using namespace osgGA;
#include <osgUtil/LineSegmentIntersector>
using namespace osgUtil;

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

namespace ThreeQt {

class Observer::ThreeManipulator : public OrbitManipulator
{
public:
    ThreeManipulator();
    void teleport(EventQueue* eq,Vec3 center,float distance);
protected:
    virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
    virtual bool performMouseDeltaMovement( const float dx, const float dy );
    virtual bool performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy );
    virtual bool performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy );
    virtual bool performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy );

    bool startAnimationByCenterAndDistance(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
    virtual bool startAnimationByMousePointerIntersection(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
    virtual void applyAnimationStep( const double currentProgress, const double prevProgress );

    struct ThreeAnimationData : public AnimationData {
        const Referenced* userData;
        osg::Vec3d centerMovement;
        float distanceMovement;

        ThreeAnimationData(const Referenced* userData):userData(userData) {}
        void start( const osg::Vec3d& movement,float distanceMovement, const double startTime );
    };
};

struct Observer::Plugin {
    ThreeWidget* tw;
    ref_ptr<ThreeManipulator> tm;
};

struct Observer::Finder : public osg::NodeVisitor {
    Finder() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
    virtual void apply(Group& node) {
        if(node.getName() == inName && 0 < node.getBound().radius()) {
            outNode = &node;
        }

        traverse(node);
    }

    string inName;
    Group* outNode;
};

Observer::Observer(ThreeWidget* tw) {
    md = new Plugin;
    md->tw = tw;

    md->tm = new ThreeManipulator();
    md->tm->setAllowThrow(false);
    md->tw->viewer->setCameraManipulator(md->tm,false);
}

Observer::~Observer() {
    delete md;
}

void Observer::lookingFor(string name) {
    if(name.empty()) return;

    Finder nv;
    nv.inName = name;
    md->tw->worldScene->accept(nv);
    if(NULL == nv.outNode) return;
    if(0 == nv.outNode->getNumChildren()) return;

    osg::BoundingSphere b = nv.outNode->getBound();
    if(0 == nv.outNode->getNumChildren()) return;
    Vec3 center = nv.outNode->getChild(0)->getBound().center() * nv.outNode->getWorldMatrices()[0];
    float distance = b.radius() * 4;
    md->tm->teleport(md->tw->viewer->getEventQueue(),center,distance);
}

void Observer::lookingFor(vec3 xyz,double distance) {
    Vec3 center(get<0>(xyz),get<1>(xyz),get<2>(xyz));
    md->tm->teleport(md->tw->viewer->getEventQueue(),center,distance == 0.0 ? md->tm->getDistance():distance);
}

void Observer::fixViewpoint() {
    BoundingSphere bound = md->tw->worldScene->getBound();
    Vec3 bc = bound.center();
    float br = bound.radius() * 1.5;
    md->tm->setHomePosition(Vec3(br,-br,br) + bc,bc,Vec3(0,0,1));
    md->tm->home(0);
}

struct UserData_LookingFor : public Referenced {
    UserData_LookingFor(Vec3 center,float distance):center(center),distance(distance) {}
    Vec3 center;
    float distance;
};

Observer::ThreeManipulator::ThreeManipulator() : OrbitManipulator(DEFAULT_SETTINGS) {}

void Observer::ThreeManipulator::ThreeAnimationData::start( const osg::Vec3d& centerMovement,float distanceMovement, const double startTime )
{
    AnimationData::start( startTime );
    this->centerMovement = centerMovement;
    this->distanceMovement = distanceMovement;
}

void Observer::ThreeManipulator::teleport(EventQueue* eq,Vec3 center,float distance) {
    eq->userEvent(new UserData_LookingFor(center,distance));
}

bool Observer::ThreeManipulator::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us ) {
    switch(ea.getEventType()) {
        case GUIEventAdapter::USER: {
            if(NULL != dynamic_cast<const UserData_LookingFor*>(ea.getUserData())) {
                _animationData = new ThreeAnimationData(ea.getUserData());
                setAnimationTime(0.25);
                startAnimationByCenterAndDistance(ea,us);
            }
            return true;
        }
    }

    return OrbitManipulator::handle(ea,us);
}

bool Observer::ThreeManipulator::performMouseDeltaMovement( const float dx, const float dy ) {
    return false;
}

bool Observer::ThreeManipulator::performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy ) {
    return false;
}

// doc in parent
bool Observer::ThreeManipulator::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
    // rotate camera
    if( getVerticalAxisFixed() )
        rotateWithFixedVertical( dx, dy );
    else
        rotateTrackball( _ga_t0->getXnormalized(), _ga_t0->getYnormalized(),
                         _ga_t1->getXnormalized(), _ga_t1->getYnormalized(),
                         getThrowScale( eventTimeDelta ) );
    return true;
}

// doc in parent
bool Observer::ThreeManipulator::performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
    float scale = -0.3f * _distance * getThrowScale( eventTimeDelta );
    auto q = _rotation;
    double test = q.y() * q.z() + q.x() * q.w();
    double heading,pitch,roll;

    if (test > 0.4999)
    { // singularity at north pole
        heading = 2.0 * atan2(q.y(), q.w());
        pitch   = osg::PI_2;
        roll    = 0.0;
    }
    else if (test < -0.4999)
    { // singularity at south pole
        heading = 2.0 * atan2(q.y(), q.w());
        pitch   = -osg::PI_2;
        roll    = 0.0;
    }
    else
    {
        double sqx = q.x() * q.x();
        double sqy = q.y() * q.y();
        double sqz = q.z() * q.z();
        heading = atan2(2.0 * q.z() * q.w() - 2.0 * q.y() * q.x(), 1.0 - 2.0 * sqz - 2.0 * sqx);
        pitch   = asin(2.0 * test);
        roll    = atan2(2.0 * q.y() * q.w() - 2.0 * q.z() * q.x(), 1.0 - 2.0 * sqy - 2.0 * sqx);
    }

    Vec3d dv(dx*scale, dy*scale, 0);
    _center += dv * Matrix::rotate(heading,0,0,1);
    return true;
}


bool Observer::ThreeManipulator::startAnimationByCenterAndDistance(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
    // get current transformation
    osg::Vec3d prevCenter, prevEye, prevUp;
    getTransformation( prevEye, prevCenter, prevUp );
    float prevDistance = getDistance();

    ThreeAnimationData *ad = dynamic_cast< ThreeAnimationData*>( _animationData.get() );
    const UserData_LookingFor* ud= dynamic_cast<const UserData_LookingFor*>(ad->userData);

    // setup animation data and restore original transformation
    ad->start(ud->center - prevCenter,ud->distance - prevDistance, ea.getTime() );
    setTransformation( prevEye, prevCenter, prevUp );
    return true;
}

bool Observer::ThreeManipulator::startAnimationByMousePointerIntersection(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{
    // get current transformation
    osg::Vec3d prevCenter, prevEye, prevUp;
    getTransformation( prevEye, prevCenter, prevUp );

    osgViewer::View* view = dynamic_cast<osgViewer::View*>(&us);
    LineSegmentIntersector::Intersections lis;
    // center by mouse intersection
    if( !view->computeIntersections(ea.getX(),ea.getY(),lis,0x2))
        return false;

    _center = lis.begin()->getWorldIntersectPoint();

    OrbitAnimationData *ad = dynamic_cast< OrbitAnimationData*>( _animationData.get() );

    // setup animation data and restore original transformation
    ad->start( osg::Vec3d(_center) - prevCenter, ea.getTime() );
    setTransformation( prevEye, prevCenter, prevUp );
    return true;
}

void Observer::ThreeManipulator::applyAnimationStep( const double currentProgress, const double prevProgress )
{
    ThreeAnimationData *tad = dynamic_cast< ThreeAnimationData* >( _animationData.get() );
    OrbitAnimationData *ad = dynamic_cast< OrbitAnimationData* >( _animationData.get() );

    if(tad != NULL) {
        // compute new center
        osg::Vec3d prevCenter, prevEye, prevUp;
        getTransformation( prevEye, prevCenter, prevUp );
        float prevDistance = getDistance();
        osg::Vec3d newCenter = osg::Vec3d(prevCenter) + (tad->centerMovement * (currentProgress - prevProgress));
        float newDistance = prevDistance + (tad->distanceMovement * (currentProgress - prevProgress));

        _distance = newDistance;
        _center = newCenter;
    }

    if(ad != NULL) {
        // compute new center
        osg::Vec3d prevCenter, prevEye, prevUp;
        getTransformation( prevEye, prevCenter, prevUp );
        osg::Vec3d newCenter = osg::Vec3d(prevCenter) + (ad->_movement * (currentProgress - prevProgress));
        osg::Vec3d newEye = osg::Vec3d(prevEye) + (ad->_movement * (currentProgress - prevProgress));

        _distance = (prevEye - newCenter).length();

       // apply new transformation
       setTransformation( newEye, newCenter, prevUp );
   }
}


}

void OrbitManipulator::OrbitAnimationData::start( const osg::Vec3d& movement, const double startTime )
{
    AnimationData::start( startTime );
    _movement = movement;
}
