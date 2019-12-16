#ifndef MODELNODEVISITOR_H
#define MODELNODEVISITOR_H

#include <osg/NodeVisitor>
using osg::NodeVisitor;
#include <osg/Geode>
using osg::Geode;
#include <osg/Vec3>
using osg::Vec3;
#include <osg/Group>
using osg::Group;
#include <osg/Node>
using osg::Node;
#include <osg/Geometry>
using osg::Geometry;
#include <osg/MatrixTransform>
using osg::MatrixTransform;
using osg::Matrix;
using osg::MatrixList;
using osg::BoundingSphere;

#include <list>
using std::list;
using std::pair;

struct NearVertexVisitor : public NodeVisitor
{
    NearVertexVisitor();
    virtual void apply(Geode& node);
    Vec3 nearPoint();
    Geode* nearGeode;
    Vec3 point;
    float nearX,nearY,nearZ;
};

struct OptimizingVisitor : public NodeVisitor
{
    OptimizingVisitor();
    virtual void apply(Geometry& node);
    virtual void apply(Geode& node);
};

struct SearchNameVisitor : public NodeVisitor {
    SearchNameVisitor();
    virtual void apply(MatrixTransform& node);
    std::string inName;
    MatrixTransform* outNode;
};

struct BubbleTextVisitor : public NodeVisitor {
    BubbleTextVisitor();
    virtual void apply(osg::Transform& node);
    float minscore;
    Vec3 pos,center;
    std::string name;
    osg::ref_ptr<osg::StateSet> ss;
};

#endif // MODELNODEVISITOR_H
