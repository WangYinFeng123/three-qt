#include "shadowmap.h"
#include <iostream>
using namespace std;

#include <osg/Timer>
#include <osg/CullFace>
#include <osg/Vec3>
#include <osg/LightSource>
#include <osg/Light>
#include <osg/Uniform>
#include <osg/NodeVisitor>
#include <osg/Shader>
#include <osg/ComputeBoundsVisitor>
#include <osg/ShapeDrawable>
#include <osg/ref_ptr>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/Quat>
#include <osg/BoundingSphere>
#include <osg/PolygonOffset>
#include <osg/Vec3f>
#include <osg/TexMat>
#include <osg/Vec4>
#include <osg/Math>
using namespace osg;

#include <osgShadow/ShadowedScene>
using osgShadow::ShadowedScene;

static const char fragmentShaderSource_noBaseTexture[] =
    "uniform sampler2DShadow osgShadow_shadowTexture; \n"
    "uniform vec2 osgShadow_ambientBias; \n"
    "\n"
    "void main(void) \n"
    "{ \n"
    "    gl_FragColor = gl_Color * (osgShadow_ambientBias.x + shadow2DProj( osgShadow_shadowTexture, gl_TexCoord[0] ) * osgShadow_ambientBias.y); \n"
    "}\n";

static const char fragmentShaderSource_withBaseTexture[] =
    "uniform sampler2D osgShadow_baseTexture; \n"
    "uniform sampler2DShadow osgShadow_shadowTexture; \n"
    "uniform vec2 osgShadow_ambientBias; \n"
    "\n"
    "void main(void) \n"
    "{ \n"
    "    vec4 color = gl_Color * texture2D( osgShadow_baseTexture, gl_TexCoord[0].st ); \n"
    "    gl_FragColor = color * (osgShadow_ambientBias.x + shadow2DProj( osgShadow_shadowTexture, gl_TexCoord[1] ) * osgShadow_ambientBias.y); \n"
    "}\n";

const char* vs = "\
                 uniform vec3 lightPos;\
                 varying vec3 lightDir,eyeDir;\
                 void main()\
                 {\
                     eyeDir = normalize(gl_NormalMatrix * gl_Normal);\
                     lightDir = normalize(gl_NormalMatrix * lightPos);\
                     gl_TexCoord[0] = gl_MultiTexCoord0;\
                     gl_FrontColor = gl_Color;\
                     gl_Position = ftransform();\
                 }";

const char* fs = "\
                 uniform sampler2D osgShadow_baseTexture;\
                 uniform sampler2DShadow osgShadow_shadowTexture;\
                 uniform vec2 osgShadow_ambientBias;\
                 varying vec3 lightDir,eyeDir;\
                 void main()\
                 {\
                     float diff = max(dot(lightDir,eyeDir),0.0) + 0.3;\
                     diff = max(diff,0.3);\
                     vec4 color = diff * (gl_FrontMaterial.diffuse + gl_FrontMaterial.ambient + gl_FrontMaterial.emission);\
                     vec4 texel = texture2D(osgShadow_baseTexture, gl_TexCoord[0].st);\
                     if(texel.rgb != vec3(0,0,0)) {\
                        color *= texel;\
                     }\
                     if (diff != 0.0)\
                     {\
                        vec3 r = reflect(-lightDir,eyeDir);\
                        float spec = pow(max(dot(eyeDir, r),0.0),gl_FrontMaterial.shininess);\
                        color += spec * gl_FrontMaterial.specular;\
                     }\
                     gl_FragColor = color;\
                 }";

static int ReceivesShadowTraversalMask = 0x1 << 3;
static int CastsShadowTraversalMask = 0x1 << 4;

struct Metadata
{
    ref_ptr<LightSource> ls;
    ref_ptr<Group> worldScene;
    ref_ptr<PositionAttitudeTransform> sun;
};

struct LightPosCallback : public Uniform::Callback {
    float degrees;
    Timer* timer;
    Metadata* _md;
    bool trun;

    LightPosCallback(Metadata* _md) : degrees(0.0f),timer(new Timer()),_md(_md) {
        timer->setStartTick();
        trun = false;
    }

    ~LightPosCallback() {
        delete timer;
    }

    virtual void operator()(Uniform* uniform, NodeVisitor*) {
        if(!uniform) return;
        double seconds = timer->time_s();

        if(seconds < 0.1) return;
        timer->setStartTick();

        //if(_md->worldScene->getNumChildren() != _md->worldScene->getChildIndex(_md->sun)) _md->worldScene->removeChild(_md->sun);
        BoundingSphere bound = _md->worldScene->getBound();
        //if(_md->worldScene->getNumChildren() == _md->worldScene->getChildIndex(_md->sun)) _md->worldScene->addChild(_md->sun);

        Vec3 bc = bound.center();
        float br = bound.radius() * 2.0;
        float height = bound.radius() * 2.0;

        if(trun) {
            degrees -= 1;
            if(degrees < 0.0f) {
                trun = !trun;
            }
        } else {
            degrees += 1;
            if(degrees > 90.0f) {
                trun = !trun;
            }
        }

        float x = br * sin(DegreesToRadians(degrees));
        float y = br * cos(DegreesToRadians(degrees));

        Vec3 pos = Vec3(x,height,y);
        _md->sun->setPosition(pos + bc);
        _md->ls->getLight()->setPosition(Vec4(pos,0.));
        Vec3 lightDir = -pos;
        lightDir.normalize();
        _md->ls->getLight()->setDirection(lightDir);
        Vec3 lightPos = Vec3(x,-y,height);
        uniform->set( lightPos);
    }
};

ShadowMap2::ShadowMap2(bool enableShadow) : metadata(new Metadata),light(!enableShadow)
#define md reinterpret_cast<Metadata*>(metadata)
{
    sun = new PositionAttitudeTransform;
    //sun->addChild(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), 5000.0f)));
}

ShadowMap2::~ShadowMap2() {
    delete md;
}

void ShadowMap2::setLightSource(osg::LightSource* light) {
    osgShadow::ShadowMap::setLight(light);
    md->ls = light;
    md->worldScene = getShadowedScene();
    getShadowedScene()->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
    getShadowedScene()->setReceivesShadowTraversalMask(CastsShadowTraversalMask);
    md->sun = sun;
    ref_ptr<Uniform> lightPosUniform = new Uniform("lightPos",Vec3(0.0,1000.0,0.0));
    LightPosCallback* lpc = new LightPosCallback(md);
    lightPosUniform->setUpdateCallback(lpc);
    getShadowedScene()->getOrCreateStateSet()->addUniform(lightPosUniform);
 }

void ShadowMap2::createShaders()
{
    // if we are not given shaders, use the default
    if( _shaderList.empty() )
    {
        if (_shadowTextureUnit==0)
        {
            osg::Shader* fragment_shader = new osg::Shader(osg::Shader::FRAGMENT, fragmentShaderSource_noBaseTexture);
            _shaderList.push_back(fragment_shader);
        }
        else
        {
            if(light) {
                _shaderList.push_back(new osg::Shader(osg::Shader::VERTEX, vs));
                _shaderList.push_back(new osg::Shader(osg::Shader::FRAGMENT, fs));
            } else {
                _shaderList.push_back(new osg::Shader(osg::Shader::FRAGMENT, fragmentShaderSource_withBaseTexture));
            }
        }
    }
}
