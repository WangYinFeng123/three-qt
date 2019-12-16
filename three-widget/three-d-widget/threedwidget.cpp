#include "threedwidget.h"
#include "node-visitors/modelnodevisitor.h"
#include "manipulators/defaultmanipulator.h"

#include <QDir>
#include <QStringList>
#include <QProcess>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
using namespace osgViewer;

#include <osgGA/OrbitManipulator>
using namespace osgGA;

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/Options>
using namespace osgDB;

#include <osg/PositionAttitudeTransform>
#include <osg/Group>
#include <osg/Timer>
#include <osg/CullFace>
#include <osg/Depth>
using namespace osg;

#include <osgText/Text>
using namespace osgText;

#include <osgShadow/ShadowedScene>
#include "shaders/shadowmap.h"
using osgShadow::ShadowedScene;

#include <osgViewer/Viewer>
using osgViewer::Viewer;
using osgViewer::View;
#include <osgUtil/LineSegmentIntersector>
using osgUtil::LineSegmentIntersector;
using osgUtil::Intersector;
#include <osgUtil/IntersectVisitor>
using osgUtil::IntersectionVisitor;

#include <string>
using std::string;

struct Metadata
{
    ref_ptr<GraphicsWindowEmbedded> gw;
    ref_ptr<Viewer> viewer;
    ref_ptr<DefaultManipulator> om;
    ref_ptr<Group> worldScene;
    ref_ptr<Group> initWorld;
    ref_ptr<Geode> bubbles;
    ref_ptr<Camera> camera;
    ref_ptr<StateSet> stateSet;
    ref_ptr<Program> program;
    ref_ptr<LightSource> ls;
    ref_ptr<PositionAttitudeTransform> ground;
};

ThreeDWidget::ThreeDWidget(QWidget* parent) : NC3DPlayerWidget(parent)
  , metadata(new Metadata)
#define md reinterpret_cast<Metadata*>(metadata)
{
    setMouseTracking(true);
    DisplaySettings* ds = DisplaySettings::instance();
    GraphicsContext::Traits* t = new GraphicsContext::Traits;
    t->x = 0;
    t->y = 0;
    t->width = width();
    t->height = height();
    t->doubleBuffer = true;
    t->alpha = ds->getMinimumNumAccumAlphaBits();
    t->stencil = ds->getMinimumNumStencilBits();
    t->sampleBuffers = ds->getMultiSamples();
    t->samples = ds->getNumMultiSamples();

    md->gw = new GraphicsWindowEmbedded(t);
    md->viewer  = new Viewer();
    md->worldScene = new Group();
    md->worldScene->setName("world");
    //md->bubbles = new Geode;

    md->initWorld = new Group();
    md->initWorld->setName("init");
    //md->initWorld->addChild(md->bubbles);

    md->ls = new LightSource;
    md->ls->getLight()->setLightNum(0);
    md->ls->getLight()->setName("I am Light");
    Vec3 pos = Vec3(10000.0,10000.0,0.0);
    md->ls->getLight()->setPosition(Vec4(pos,0.0));
    Vec3 dir = -pos;
    dir.normalize();
    md->ls->getLight()->setDirection(dir);
    md->ls->getLight()->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    md->ls->getLight()->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    md->ls->getLight()->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

    md->initWorld->addChild(md->ls);
    md->initWorld->addChild(md->worldScene);
    watermark(true);

    md->om = new DefaultManipulator();
    md->om->setAllowThrow(false);
    md->om->setHomePosition(Vec3(500,500,500),Vec3(0,0,0),Vec3(0,1,0));
    md->om->home(0);

    md->viewer->setThreadingModel(ViewerBase::AutomaticSelection);
    md->viewer->setCameraManipulator(md->om,false);
    md->viewer->setSceneData(md->initWorld);
    md->camera = md->viewer->getCamera();
    md->camera->setGraphicsContext(md->gw);
    md->camera->setViewport(new Viewport(0, 0, width(), height()));
    md->camera->setProjectionMatrixAsPerspective(35, 1. * width() / height(), 1, 1000.0);
    md->camera->setClearColor(Vec4(0.05098,0.160784,(double)89/255,1));

//    class PickHandler : public GUIEventHandler
//    {
//    public:
//        PickHandler() {}
//        virtual ~PickHandler() {}
//        virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor*) {
//            Group* scene = dynamic_cast<Group*>(obj);

//            switch(ea.getEventType()) {
//            case GUIEventAdapter::MOVE: {
//                osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//                LineSegmentIntersector::Intersections lis;
//                if(!view->computeIntersections(ea.getX(),ea.getY(),lis,0x2)) {
//                    if(text.valid()) scene->removeChild(text);
//                    break;
//                }

//                osgUtil::LineSegmentIntersector::Intersection li = *lis.begin();
//                Vec3 xyz = li.getWorldIntersectPoint();

//                BubbleTextVisitor btv;
//                btv.pos = xyz;
//                btv.center = li.drawable->getBound().center();
//                scene->accept(btv);

//                QString fontFilePath = ThreeDExtension::settings.value("fontFilePath").toString();

//                scene->removeChild(text);
//                text = new Text();
//                text->setText(btv.name,String::ENCODING_UTF8);
//                text->setFont(osgText::readFontFile(fontFilePath.toLocal8Bit().data()));
//                text->setAutoRotateToScreen(true);
//                text->setCharacterSizeMode(Text::SCREEN_COORDS);
//                text->setAlignment(Text::CENTER_BOTTOM);
//                text->setDrawMode(Text::TEXT | Text::FILLEDBOUNDINGBOX);
//                text->setPosition(xyz);
//                text->setColor(Vec4(1,1,0,0.8));
//                StateSet* ss = text->getOrCreateStateSet();
//                ss->setMode( StateAttribute::LIGHT, osg::StateAttribute::OFF );
//                ss->setAttributeAndModes( new osg::Depth(osg::Depth::LEQUAL, 0.0, 0.0));
//                text->setNodeMask(0x1);
//                scene->addChild(text);
//                break;}
//            default:break;
//            }

//            return false;
//        }

//        ref_ptr<Text> text;
//    };

//    md->initWorld->addEventCallback(new PickHandler);
}

ThreeDWidget::~ThreeDWidget() {
    delete md;
}

//兼容代码 >>
QString changeFileExt(QString fileName,QString suffix) {
    QString str=fileName;
    QStringList list = str.split(".");
    list[list.length()-1]=suffix;
    str = list.join(".");
    return str;
};

bool ThreeDWidget::openScene(QString path,string fileName,bool enableShadow) {
    closeScene();

    QFile outFile(changeFileExt(path,"FBX"));
    QStringList s = path.split('.');
    if(0 == s.size()) return false;
    bool isNc = false;
    if(s[s.size()-1] == "nc" || s[s.size()-1] == "NC") {
        isNc=true;
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray  buff =  file.readAll();
        buff.remove(0,32);
        file.close();

        outFile.open(QIODevice::WriteOnly);
        outFile.write(buff);
        outFile.flush();
        outFile.close();
        path = outFile.fileName();
    }

    if(!fileName.empty()) {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
        osg::ref_ptr<osg::Image> image = osgDB::readImageFile(fileName);
        texture->setImage( image.get() );

        osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f) );
        quad->getOrCreateStateSet()->setTextureAttributeAndModes( 0,texture.get());

        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        geode->addDrawable( quad.get() );

        osg::ref_ptr<osg::Camera> camera = new osg::Camera;
        camera->setClearMask(0);
        camera->setCullingActive( false );
        camera->setAllowEventFocus( false );
        camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
        camera->setRenderOrder( osg::Camera::POST_RENDER );
        camera->setProjectionMatrix( osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0) );
        camera->addChild( geode.get() );

        StateSet* ss = camera->getOrCreateStateSet();
        ss->setMode( StateAttribute::LIGHT, osg::StateAttribute::OFF );
        ss->setAttributeAndModes( new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));
        camera->setNodeMask(0x1);
        md->worldScene->addChild(camera);
    }//<<

    Options* op = new Options();
    op->setObjectCacheHint(Options::CACHE_NONE);
    ref_ptr<Node> scene = readRefNodeFile(path.toLocal8Bit().data(),op);

    //兼容代码>>
    if(isNc) {
        outFile.remove();
        QStringList sl;
        sl.push_back(path.replace(".fbx",".fbm",Qt::CaseInsensitive));
        sl.push_back("-rf");
        QProcess::execute("rm.exe",sl);
    }
    //<<

    if(NULL == scene) return false;
    md->worldScene->addChild(scene);

    resetPosition();
    return true;
}

void ThreeDWidget::closeScene() {
    md->worldScene->removeChild(0,md->worldScene->getNumChildren());
    //md->bubbles->removeChild(0,md->bubbles->getNumChildren());
}

void ThreeDWidget::lookingFor(QString name) {
    if(md->stateSet.valid()) md->stateSet->removeAttribute(md->program);
    SearchNameVisitor nv;
    nv.inName = name.toUtf8().data();
    md->worldScene->accept(nv);
    if(NULL == nv.outNode) return;

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

    struct ColorCallback : public Uniform::Callback {
        ColorCallback() : incRed(false) {}
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


    md->stateSet = nv.outNode->getOrCreateStateSet();
    md->program = new Program;
    Shader* shaderV = new Shader(Shader::VERTEX,vs);
    Shader* shaderF = new Shader(Shader::FRAGMENT,fs);
    md->program->addShader(shaderV);
    md->program->addShader(shaderF);
    Uniform* mainColor = new Uniform("mainColor",Vec4(1.0,0.5,0.5,0.5));
    mainColor->setUpdateCallback(new ColorCallback);
    md->stateSet->addUniform(mainColor);
    md->stateSet->setAttributeAndModes(md->program);
    if(0 == nv.outNode->getNumChildren()) return;

    BoundingSphere b = nv.outNode->getBound();
    Vec3 center = nv.outNode->getChild(0)->getBound().center() * nv.outNode->getWorldMatrices()[0];
    float distance = b.radius() * 4;
    md->om->setCenter(center);
    md->om->setDistance(distance);
}

void ThreeDWidget::resetPosition() {
    BoundingSphere bound = md->worldScene->getBound();
    Vec3 bc = bound.center();
    float br = bound.radius() * 1.5;
    md->om->setHomePosition(Vec3(br,br,br) + bc,bc,Vec3(0,1,0));
    md->om->home(0);
}

QList<QMap<QString,QString> > ThreeDWidget::sceneDetails() {
    QList<QMap<QString,QString> > details;

    for(int i=0;i < md->worldScene->getNumChildren();i++) {
        QMap<QString,QString> detail;
        Node* scene = md->worldScene->getChild(i);
        detail["id"] = QString::number(reinterpret_cast<long long>(scene));
        detail["name"] = QString::fromUtf8(scene->getName().data());
        detail["class"] = scene->className();
        detail["library"] = scene->libraryName();
        details.push_back(detail);
    }
    return details;
}

void ThreeDWidget::addExtension(ThreeDExtension& ext) {
    void* extMd = ext.getMetadata();
    if(extMd == NULL) return;
    ref_ptr<GUIEventHandler> handler = *reinterpret_cast<ref_ptr<GUIEventHandler>*>(extMd);
    md->worldScene->addEventCallback(handler);
}

void ThreeDWidget::removeExtension(ThreeDExtension& ext) {
    void* extMd = ext.getMetadata();
    if(extMd == NULL) return;
    ref_ptr<GUIEventHandler> handler = *reinterpret_cast<ref_ptr<GUIEventHandler>*>(ext.getMetadata());
    if(handler != NULL) md->worldScene->removeEventCallback(handler);
}

void ThreeDWidget::watermark(bool enable) {
    QString flag = ThreeDExtension::settings.value("flag").toString();
    QString fontFilePath = ThreeDExtension::settings.value("fontFilePath").toString();

    Text* text = new Text();
    text->setText(flag.toUtf8().data(),String::ENCODING_UTF8);
    text->setFont(osgText::readFontFile(fontFilePath.toLocal8Bit().data()));
    text->setColor(Vec4(1,1,1,0.5));
    text->setAlignment(Text::LEFT_BOTTOM);
    Geode* watermark = new Geode();
    watermark->addDrawable(text);

    Camera* camera = new Camera();
    camera->setProjectionMatrixAsOrtho2D(0,1280,0,800);
    camera->setReferenceFrame(Transform::ABSOLUTE_RF);
    camera->setViewMatrix(Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(Camera::POST_RENDER);
    camera->setAllowEventFocus(false);
    camera->addChild(watermark);
    md->initWorld->addChild(camera);
}

void ThreeDWidget::resizeGL(int width, int height)
{
    md->gw->getEventQueue()->windowResize(0,0,width,height);
    md->gw->resized(0,0,width,height);
}

void ThreeDWidget::paintGL()
{
    if (md->viewer.valid()) {
        md->viewer->frame();
    }
    update();
}

void ThreeDWidget::mousePressEvent(QMouseEvent *ev)
{
    md->gw->getEventQueue()->mouseButtonPress(ev->x(), ev->y(), ev->button() == Qt::RightButton ? 3 : ev->button() == Qt::MidButton ? 2 : ev->button() == Qt::LeftButton ? 1 : 0);
}

void ThreeDWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    md->gw->getEventQueue()->mouseButtonRelease(ev->x(), ev->y(), ev->button() == Qt::RightButton ? 3 : ev->button() == Qt::MidButton ? 2 : ev->button() == Qt::LeftButton ? 1 : 0);
}

void ThreeDWidget::mouseMoveEvent(QMouseEvent *ev)
{
    md->gw->getEventQueue()->mouseMotion(ev->x(), ev->y());
}

void ThreeDWidget::wheelEvent(QWheelEvent *ev)
{
    md->gw->getEventQueue()->mouseScroll(ev->delta() < 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN);
}

void ThreeDWidget::keyPressEvent(QKeyEvent* ev)
{
    if(!ev->isAutoRepeat()) md->gw->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol) ev->key());
}

void ThreeDWidget::keyReleaseEvent(QKeyEvent* ev)
{
    if(!ev->isAutoRepeat()) md->gw->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol) ev->key());
}

#undef md
