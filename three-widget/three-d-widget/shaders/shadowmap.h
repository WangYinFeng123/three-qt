#ifndef SHADOWMAP2_H
#define SHADOWMAP2_H

#include <osgShadow/ShadowMap>
#include <osgUtil/CullVisitor>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>

class ShadowMap2 : public osgShadow::ShadowMap
{
public:
    ShadowMap2(bool enableShadow = true);
    virtual void createShaders();
    void setLightSource(osg::LightSource* light);

protected:
    virtual ~ShadowMap2();
    osg::ref_ptr<osg::PositionAttitudeTransform> sun;
    bool light;
    void* metadata;
};

#endif // SHADOWMAP2_H
