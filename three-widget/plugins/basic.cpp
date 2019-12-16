#include "basic.h"
#include "threewidget.h"
#if defined(OSGEARTH)
#include "threeearthwidget.h"
#endif

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

#include <set>
using namespace std;

#include <QSettings>

namespace Basic {
    static QSettings settings(GLOBAL_COMPANY,GLOBAL_NAME);
    struct Basic_Plugin {
        ThreeWidget* tw;
        ref_ptr<MatrixTransform> mtScene;
        ref_ptr<Node> scene;
        ref_ptr<StateSet> lookingModelStateSet;
        ref_ptr<Node> showingModel;
        ref_ptr<Program> program;
        ref_ptr<Camera> background;
        ref_ptr<Group> bubbles;
    };

    struct _NameVisitor : public NodeVisitor {
        _NameVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
        virtual void apply(MatrixTransform& node) {
            if(!node.getName().empty()) {
                outNames.insert(node.getName());
                outNodes.insert(&node);
            }
            traverse(node);
        }

        set<string> outNames;
        set<MatrixTransform*> outNodes;
    };

    struct Basic_LookingForVisitor : public NodeVisitor {
        Basic_LookingForVisitor() : NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
        virtual void apply(MatrixTransform& node) {
            if(node.getName() == inName && 0 < node.getBound().radius()) {
                outNode = &node;
            }

            traverse(node);
        }

        string inName;
        MatrixTransform* outNode;
    };

    struct _HeightLightCallback : public Uniform::Callback {
        _HeightLightCallback() : incRed(false) {}
        virtual void operator()(Uniform* uniform, NodeVisitor*) {
            if(!uniform) return;

            Vec4 color;
            uniform->get(color);

            if(incRed) {
                if(color.y() < 1.0) color.y() += 0.01;
                else incRed = false;
            } else {
                if(color.y() > 0.0) color.y() -= 0.01;
                else incRed = true;
            }

            uniform->set(color);
        }

        bool incRed;
    };

    Plugin* CreateThreePlugin(ThreeWidget* tw) {
        Basic_Plugin* p = new Basic_Plugin;
        p->tw = tw;
        p->mtScene = new MatrixTransform;

        p->background = new osg::Camera;
        p->background->setClearMask(0);
        p->background->setCullingActive( false );
        p->background->setAllowEventFocus( false );
        p->background->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
        p->background->setRenderOrder( osg::Camera::POST_RENDER );
        p->background->setProjectionMatrix( osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0) );

        StateSet* ss = p->background->getOrCreateStateSet();
        ss->setMode( StateAttribute::LIGHT, osg::StateAttribute::OFF );
        ss->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));

        p->tw->worldScene->addChild(p->background);
        p->bubbles = new Group();
        p->tw->initScene->addChild(p->bubbles);
        return reinterpret_cast<Plugin*>(p);
    }

    void DestoryThreePlugin(Plugin* plugin) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        p->tw->worldScene->removeChild(p->background);
        delete p;
    }

    void AddScene(Basic::Plugin* plugin,string modelPath) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        p->scene = readRefNodeFile(modelPath);
        p->mtScene->addChild(p->scene);
        p->tw->worldScene->addChild(p->mtScene);

        BoundingSphere bound = p->tw->worldScene->getBound();
        Vec3 bc = bound.center();
        float br = bound.radius() * 1.5;
        p->tw->tm->setHomePosition(Vec3(br,-br,br) + bc,bc,Vec3(0,0,1));
        p->tw->tm->home(0);
    }

    void OpenScene(Basic::Plugin* plugin,string modelPath) {
        CloseScene(plugin);
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        p->scene = readRefNodeFile(modelPath);
        p->mtScene->addChild(p->scene);
        p->tw->worldScene->addChild(p->mtScene);

        BoundingSphere bound = p->tw->worldScene->getBound();
        Vec3 bc = bound.center();
        float br = bound.radius() * 1.5;
        p->tw->tm->setHomePosition(Vec3(br,-br,br) + bc,bc,Vec3(0,0,1));
        p->tw->tm->home(0);
    }

    void CloseScene(Basic::Plugin* plugin) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        p->mtScene->removeChild(0,p->mtScene->getNumChildren());
        p->bubbles->removeChild(0,p->bubbles->getNumChildren());
    }

    void AxisRotate(Plugin* plugin,float x,float y,float z,double degress) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        p->mtScene->setMatrix(Matrix::rotate(DegreesToRadians(degress),Vec3(x,y,z)));
    }

    set<string> Models(Basic::Plugin* plugin) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        _NameVisitor nv;
        p->mtScene->accept(nv);
        return nv.outNames;
    }

    void HeightLight(Plugin* plugin,string name,bool enable) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        if(name.empty()) return;
        if(!enable) {
            if(p->lookingModelStateSet.valid()) p->lookingModelStateSet->removeAttribute(p->program);
            return;
        }

        Basic_LookingForVisitor nv;
        nv.inName = name;
        p->tw->worldScene->accept(nv);
        if(NULL == nv.outNode) return;
        if(0 == nv.outNode->getNumChildren()) return;

        char vs[] = "\
                varying vec3 normal;\
                void main() {\
                    normal = normalize(gl_NormalMatrix * gl_Normal);\
                    gl_Position = ftransform();\
                }";
        char fs[] = "\
                uniform vec4 mainColor;\
                varying vec3 normal;\
                void main() {\
                    gl_FragColor = mainColor;\
                    gl_FragDepth = 0.0;\
                }";

        p->lookingModelStateSet = nv.outNode->getOrCreateStateSet();
        p->program = new Program;
        Shader* shaderV = new Shader(Shader::VERTEX,vs);
        Shader* shaderF = new Shader(Shader::FRAGMENT,fs);
        p->program->addShader(shaderV);
        p->program->addShader(shaderF);
        Uniform* mainColor = new Uniform("mainColor",Vec4(1.0,0.5,0.5,0.5));
        mainColor->setUpdateCallback(new _HeightLightCallback);
        p->lookingModelStateSet->addUniform(mainColor);
        p->lookingModelStateSet->setAttributeAndModes(p->program);
    }

    void SetBackground(Plugin* plugin,string imagePath) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        if(!imagePath.empty()) {
            osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
            osg::ref_ptr<osg::Image> image = osgDB::readImageFile(imagePath);
            texture->setImage(image.get());

            osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f) );
            quad->getOrCreateStateSet()->setTextureAttributeAndModes( 0,texture.get());

            osg::ref_ptr<osg::Geode> geode = new osg::Geode;
            geode->addDrawable( quad.get());
            p->background->addChild(geode.get());
        } else {
            p->background->removeChild(0,p->background->getNumChildren());
        }
    }

    void SetBackground(Plugin* plugin,float x,float y,float z,float w) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        Camera* c = p->tw->viewer->getCamera();
        c->setClearColor(Vec4(x,y,z,w));
    }

    void SetHandleFrame(Plugin* plugin,bool enable) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        if(p->tw->frameHandle == enable) return;
        p->tw->frameHandle = enable;
        if(!enable) RunFrame(plugin);
    }

    void RunFrame(Plugin* plugin) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        if(p->tw->viewer.valid() && p->tw->isValid()) {
            p->tw->makeCurrent();
            p->tw->viewer->frame();
            p->tw->doneCurrent();
        }

        p->tw->update();
    }

    void BoundBox(Plugin* plugin,float center[3],float& radius) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        BoundingSphere b = p->tw->worldScene->getBound();
        center[0] = b.center()[0];
        center[1] = b.center()[1];
        center[2] = b.center()[2];
        radius = b.radius();
    }

    void Bubbles(Plugin* plugin,bool enable) {
        Basic_Plugin* p = reinterpret_cast<Basic_Plugin*>(plugin);
        p->bubbles->removeChild(0,p->bubbles->getNumChildren());
        if(enable) {
            QString fontFilePath = settings.value("fontFilePath").toString();

            _NameVisitor nv;
            p->tw->worldScene->accept(nv);

            for(set<MatrixTransform*>::iterator it = nv.outNodes.begin();it != nv.outNodes.end();it++) {
                MatrixTransform* node = *it;
                Text* text = new Text();
                text->setNodeMask(0x1);
                text->setText(node->getName(),String::ENCODING_UTF8);
                text->setFont(osgText::readFontFile(fontFilePath.toLocal8Bit().data()));
                text->setColor(Vec4(1,1,0,1));
                text->setCharacterSize(40);
                text->setAxisAlignment(TextBase::SCREEN);
                text->setCharacterSizeMode(Text::SCREEN_COORDS);
                text->setAlignment(Text::CENTER_BOTTOM);

                BoundingSphere b = node->getBound();
                if(0 == node->getNumChildren()) continue;
                Vec3 center = node->getChild(0)->getBound().center() * node->getWorldMatrices()[0];
                center.z() += b.radius();
                text->setPosition(center);
                Geode* gtext = new Geode();
                gtext->addDrawable(text);
                LOD* lod = new LOD();
                lod->addChild(gtext,0, b.radius() * 7);
                p->bubbles->addChild(lod);
            }
      }
}

#if defined (OSGEARTH)
    struct _Basic_EarthPlugin {
        ThreeEarthWidget* tew;
    };

    EarthPlugin* CreateThreePlugin(ThreeEarthWidget* tew) {
        _Basic_EarthPlugin* p = new _Basic_EarthPlugin;
        p->tew = tew;
        return reinterpret_cast<EarthPlugin*>(p);
    }

    void DestoryThreePlugin(EarthPlugin* plugin) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);
        delete p;
    }

    void SetHandleFrame(EarthPlugin* plugin,bool enable) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);
        if(p->tew->frameHandle == enable) return;
        p->tew->frameHandle = enable;
        if(!enable) RunFrame(plugin);
    }

    void RunFrame(EarthPlugin* plugin) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);

        if(p->tew->viewer.valid() && p->tew->isValid()) {
            p->tew->makeCurrent();
            p->tew->viewer->frame();
            p->tew->doneCurrent();
        }

        p->tew->update();
    }


    void LookingFor(EarthPlugin* plugin,double longitude,double latitude,double pitch,double range,double duration) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);
        osgEarth::Viewpoint vp("", longitude, latitude, 0.0, 0.0, pitch, range);
        p->tew->om->setViewpoint(vp,duration);
    }

    void Home(EarthPlugin* plugin) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);
        p->tew->om->home(0);
    }

    void SetHomePosition(EarthPlugin* plugin,double longitude,double latitude,double pitch,double range) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);
        osgEarth::Viewpoint vp("", longitude, latitude, 0.0, 0.0, pitch, range);
        p->tew->om->setHomeViewpoint(vp);
    }

    void CameraPosition(EarthPlugin* plugin,double &longitude,double &latitude,double &pitch,double &range) {
        _Basic_EarthPlugin* p = reinterpret_cast<_Basic_EarthPlugin*>(plugin);
        osgEarth::Viewpoint vp = p->tew->om->getViewpoint();
        longitude = vp.focalPoint()->x();
        latitude = vp.focalPoint()->y();
        pitch = vp.pitch()->getValue();
        range = vp.range()->getValue();
    }

#endif
}
