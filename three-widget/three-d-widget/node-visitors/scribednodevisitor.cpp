#include "scribednodevisitor.h"
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/PolygonOffset>
#include <osg/Material>

#include <map>
using namespace std;

map<unsigned long long,ref_ptr<StateSet>> initSSList;
ScribedNodeVisitor::ScribedNodeVisitor() : NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN) {}

void ScribedNodeVisitor::apply(Geometry& geometry) {
    auto key = reinterpret_cast<unsigned long long>(&geometry);
    if(initSSList.end() != initSSList.find(key)) return;
    initSSList.insert(make_pair(key,geometry.getOrCreateStateSet()));

    osg::ref_ptr<osg::StateSet> ss = new osg::StateSet;
    osg::ref_ptr<LineWidth> _wf_lw = new osg::LineWidth;
    _wf_lw->setWidth(1.0f);

    osg::ref_ptr<Material> _wf_mat = new osg::Material;
    _wf_mat->setColorMode(osg::Material::OFF);
    _wf_mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    _wf_mat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    _wf_mat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    _wf_mat->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f,1.0f,1.0f,1.0f));

    osg::ref_ptr<osg::PolygonMode> polymode = new osg::PolygonMode;
    polymode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
    ss->setAttributeAndModes(polymode, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
    ss->setAttributeAndModes(_wf_lw, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
    ss->setAttributeAndModes(_wf_mat, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
    ss->setMode(GL_LIGHTING, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
    ss->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OVERRIDE|osg::StateAttribute::OFF);
    geometry.setStateSet(ss);
}

UnScribedNodeVisitor::UnScribedNodeVisitor() : NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN) {}
UnScribedNodeVisitor::~UnScribedNodeVisitor() {
    initSSList.clear();
}

void UnScribedNodeVisitor::apply(Geometry& geometry) {
    auto key = reinterpret_cast<unsigned long long>(&geometry);
    auto it = initSSList.find(key);
    if(initSSList.end() == it) return;
    auto ss = it->second;
    geometry.setStateSet(ss);
    initSSList.erase(it);
}
