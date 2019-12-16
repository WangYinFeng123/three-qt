#include "modelnodevisitor.h"

#include <osg/ref_ptr>
using osg::ref_ptr;
#include <osg/Array>
using osg::Vec3Array;

NearVertexVisitor::NearVertexVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN)
  , nearGeode(NULL)
  , point(0,0,0)
  , nearX(FLT_MAX),nearY(FLT_MAX),nearZ(FLT_MAX)
{}

void NearVertexVisitor::apply(Geode& node)
{
    osg::BoundingSphere box = node.getBound();
    Vec3 center = box.center();

    if(center.y() < nearY) {
        //std::cout << "geode:" << center.y() << std::endl;
        nearY = center.y();
        nearGeode = &node;
    }

    nearX = (center.x() - point.x()) < nearX ? center.x() : nearX;
    nearZ = (center.z() - point.z()) < nearZ ? center.z() : nearZ;
    traverse(node);
}

Vec3 NearVertexVisitor::nearPoint()
{
    Geometry* nearGeomatry = NULL;
    for(int i=0;i < nearGeode->getNumDrawables();i++) {
        Geometry* node = dynamic_cast<Geometry*>(nearGeode->getDrawable(i));
        osg::BoundingSphere box = node->getBound();
        Vec3 center = box.center();

        if(center.y() < nearY) {
            //std::cout << "geomatry:" << center.y() << std::endl;
            nearY = center.y();
            nearGeomatry = node;
        }

        nearX = (center.x() - point.x()) < nearX ? center.x() : nearX;
        nearZ = (center.z() - point.z()) < nearZ ? center.z() : nearZ;
    }

    if(nearGeomatry != NULL) {
        Geometry* geometra = dynamic_cast<Geometry*>(nearGeomatry);
        Vec3Array* vertexs =  dynamic_cast<Vec3Array*>(geometra->getVertexArray());


        for(Vec3Array::iterator it = vertexs->begin();vertexs->end() != it;it++) {
            Vec3 v = *it;
            Vec3 center = v;
            if(center.y() < nearY) {
                //std::cout  << "vertex:"<< center.y() << std::endl;
                nearY = center.y();
            }

            nearX = (center.x() - point.x()) < nearX ? center.x() : nearX;
            nearZ = (center.z() - point.z()) < nearZ ? center.z() : nearZ;
        }
    }

    Vec3 nearPoint(nearX,nearY,nearZ);
    return nearPoint;
}

SearchNameVisitor::SearchNameVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}

void SearchNameVisitor::apply(MatrixTransform& node) {
    if(node.getName() == inName && 0 < node.getBound().radius()) {
        outNode = &node;
    }

    traverse(node);
}
#include <iostream>
BubbleTextVisitor::BubbleTextVisitor(): NodeVisitor(TRAVERSE_ALL_CHILDREN) {
    minscore = DBL_MAX;
}

void BubbleTextVisitor::apply(osg::Transform& node) {
   MatrixList ml =node.getWorldMatrices();

   Vec3 xyz = center * ml[0];
   if((pos - xyz).length() < minscore) {
       minscore = (pos - xyz).length();
       name = node.getName();
       ss = node.getStateSet();
   }

   traverse(node);
}
