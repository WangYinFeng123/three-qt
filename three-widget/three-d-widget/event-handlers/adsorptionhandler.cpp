#include "adsorptionhandler.h"

#include <osgUtil/LineSegmentIntersector>
using namespace osgUtil;

#include <osgViewer/View>
using namespace osgViewer;

#include <osg/MatrixTransform>
#include <osg/Vec3>
#include <osg/PrimitiveSet>
#include <osg/LineWidth>
#include <osg/BlendFunc>
#include <osg/AutoTransform>
using namespace osg;

#include <iostream>
using namespace std;

AdsorptionHandler::AdsorptionHandler(bool xyz[],function<void()> onFinish) : sPressed(false),lbPressed(false),
    onFinish(onFinish)
{
    this->xyz[0] = xyz[0];
    this->xyz[1] = xyz[1];
    this->xyz[2] = xyz[2];
    this->xyz[3] = xyz[3];
}

AdsorptionHandler::~AdsorptionHandler() {
    if(!scene.valid()) return;
    scene->removeChild(lightPicked);
    scene->removeChild(lightTargeted);
}

bool AdsorptionHandler::handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor*) {
    auto view = dynamic_cast<osgViewer::View*>(&aa);
    LineSegmentIntersector::Intersections lis;
    LineSegmentIntersector::Intersection hit;
    auto isInteracted = false;

    switch(ea.getEventType()) {
    case GUIEventAdapter::KEYDOWN:
        if(KEY_S != ea.getKey()) break;
        scene = dynamic_cast<Group*>(obj);
        sPressed = true;
        return true;
    case GUIEventAdapter::MOVE: {
        if(!sPressed) break;
        isInteracted = view->computeIntersections(ea.getX(),ea.getY(),lis);
        if(!isInteracted) break;

        for(auto it=lis.begin();lis.end() != it;it++) {
            auto li = *it;
            if(sizeMinimumOfNodePath > li.nodePath.size()) continue;
            hit = li;
            break;
        }

        if(0 == hit.nodePath.size()) break;

        auto point = hit.getWorldIntersectPoint();
        auto score = DBL_MAX;

        modelMatrixTransformPicked = dynamic_cast<MatrixTransform*>(hit.nodePath[indexFirstOfPicked]);
        modelMatrixPicked = modelMatrixTransformPicked->getMatrix();
        auto geometra = dynamic_cast<Geometry*>(hit.drawable.get());
        auto vertexs =  dynamic_cast<Vec3Array*>(geometra->getVertexArray());

        for(auto i=vertexs->begin();vertexs->end() != i;i++) {
            auto v = *i;
            auto wms = hit.drawable->getWorldMatrices();
            for(auto j=wms.begin();wms.end() != j;j++) {
                auto wm = *j;
                auto mv = (v * wm);
                auto sample = point - mv;
                auto difference = sample.normalize();

                if(difference < score) {
                    score = difference;
                    vertexPicked = mv;
                }
            }
        }

        scene->removeChild(lightPicked);
        lightPicked = makePicked(vertexPicked);
        scene->addChild(lightPicked);
    }
    return true;
    case GUIEventAdapter::PUSH:
        if(!sPressed
        || GUIEventAdapter::LEFT_MOUSE_BUTTON != ea.getButtonMask()
        || !modelMatrixTransformPicked.valid()
        || lbPressed) break;
        lbPressed = true;
    return true;
    case GUIEventAdapter::DRAG: {
        if(GUIEventAdapter::LEFT_MOUSE_BUTTON != ea.getButtonMask()
        || !modelMatrixTransformPicked.valid()
        || !lbPressed) break;
        auto worldScene = modelMatrixTransformPicked->getParent(0);
        worldScene->removeChild(modelMatrixTransformPicked);

        isInteracted = view->computeIntersections(ea.getX(),ea.getY(),lis);
        worldScene->addChild(modelMatrixTransformPicked);
        if(!isInteracted) break;

        if(0 == lis.size()) {
            modelMatrixTransformPicked->setMatrix(modelMatrixPicked);
            break;
        }

        for(auto i=lis.begin();lis.end() != i;i++) {
            auto li = *i;
            if(sizeMinimumOfNodePath > li.nodePath.size()) continue;
            hit = li;
            break;
        }

        hit = *lis.begin();

        auto point = hit.getWorldIntersectPoint();
        auto score = DBL_MAX;
        auto geometra = dynamic_cast<Geometry*>(hit.drawable.get());
        auto vertexs =  dynamic_cast<Vec3Array*>(geometra->getVertexArray());

        if(sizeMinimumOfNodePath > hit.nodePath.size()) {
            vertexTargeted = point;
        } else {
            for(auto i=vertexs->begin();vertexs->end() != i;i++) {
                auto v = *i;
                auto wms = hit.drawable->getWorldMatrices();
                for(auto j=wms.begin();wms.end() != j;j++) {
                    auto wm = *j;
                    auto mv = (v * wm);
                    auto sample = point - mv;
                    auto difference = sample.normalize();

                    if(difference < score) {
                        score = difference;
                        vertexTargeted = mv;
                    }
                }
            }
        }

        Vec3 trans = -(vertexPicked - vertexTargeted);

        trans.set(xyz[0] ? trans.x() : 0,xyz[1] ? trans.y() : 0,xyz[2] ? trans.z() : 0);
        modelMatrixTransformPicked->setMatrix(modelMatrixPicked * Matrix::translate(trans));
        scene->removeChild(lightTargeted);
        lightTargeted = makePicked(vertexTargeted);
        scene->addChild(lightTargeted);
    }
    return true;
    case GUIEventAdapter::RELEASE:
        if(GUIEventAdapter::LEFT_MOUSE_BUTTON != ea.getButton()
        || !modelMatrixTransformPicked.valid()
        || !lbPressed) break;
        lbPressed = false;
        modelMatrixPicked = modelMatrixTransformPicked->getMatrix();
        modelMatrixTransformPicked = nullptr;
        scene->removeChild(lightTargeted);
    return true;
    case GUIEventAdapter::KEYUP:
        if(KEY_S != ea.getKey()
        || !sPressed) break;
        sPressed = false;
        scene->removeChild(lightTargeted);
        scene->removeChild(lightPicked);
        onFinish();
    return true;
    }
    return false;
}

ref_ptr<MatrixTransform> AdsorptionHandler::makePicked(Vec3 center) {
    auto ps = new DrawElementsUInt(PrimitiveSet::LINES);
    ps->push_back(0);
    ps->push_back(1);
    ps->push_back(2);
    ps->push_back(3);

    auto v = new Vec3Array();
    v->push_back(Vec3(-4,4,0));
    v->push_back(Vec3(4,-4,0));
    v->push_back(Vec3(4,4,0));
    v->push_back(Vec3(-4,-4,0));

    auto c = new Vec4Array();
    c->push_back(Vec4(0,1,0,1));
    c->push_back(Vec4(0,1,0,1));
    c->push_back(Vec4(0,1,0,1));
    c->push_back(Vec4(0,1,0,1));

    auto geom = new Geometry();
    geom->setVertexArray(v);
    geom->setColorArray(c);
    geom->addPrimitiveSet(ps);
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    auto geode = new Geode();
    auto ss = geode->getOrCreateStateSet();
    ss->setMode(GL_DEPTH_TEST,StateAttribute::OFF);
    geode->addDrawable(geom);

    auto mt = new MatrixTransform();
    mt->setMatrix(Matrix::translate(center));
    auto ar = new AutoTransform;
    ar->setAutoRotateMode(AutoTransform::ROTATE_TO_SCREEN);
    ar->setAutoScaleToScreen(true);
    ar->addChild(geode);
    mt->addChild(ar);
    return mt;
}
