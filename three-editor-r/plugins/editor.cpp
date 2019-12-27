#include "editor.h"
#include "threewidget.h"

#include <fstream>
#include <sstream>
#include <bitset>
using namespace std;

#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/BlendFunc>
#include <osg/AutoTransform>
#include <osg/PositionAttitudeTransform>
using namespace osg;

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
using namespace osgDB;

#include <osgUtil/PolytopeIntersector>
using namespace osgUtil;

#include <osgManipulator/TranslateAxisDragger>
using namespace osgManipulator;

#include <osgText/Text>
using namespace osgText;

namespace ThreeQt {

struct Editor::Finder : public NodeVisitor {
    Finder() : NodeVisitor(TRAVERSE_ALL_CHILDREN),precise(true),outMt(nullptr) {}
    virtual void apply(PositionAttitudeTransform& node) {
        auto name = node.getName();

        if(precise) {
            if(outMt != nullptr) return;
            if(outMtCached != nullptr && outMtCached->getName() == inName) { //缓存上一次查找，用来快速索引
                outMt = outMtCached;
                return;
            }

            if(name == inName) {
                if(outMt == nullptr) {
                    outMt = &node;
                    outMtCached = &node;
                    return;
                }
            }
        } else {
            if(0 == name.find(inName)) {
                if(outMt == nullptr) {
                    outMt = &node;
                    return;
                }
            }
        }

        traverse(node);
    }

    bool precise;
    string inName;
    PositionAttitudeTransform* outMt;
    static PositionAttitudeTransform* outMtCached;
};

PositionAttitudeTransform* Editor::Finder::outMtCached = nullptr;

struct Editor::Plugin {
    ThreeWidget* tw;
    ref_ptr<Group> scene;
};

Editor::Editor(ThreeWidget* tw) {
    md = new Plugin;
    md->tw = tw;

    md->scene = new Group();
    tw->worldScene->addChild(md->scene);
}

Editor::~Editor() {
    md->tw->worldScene->removeChild(md->scene);
    delete md;
}

ThreeWidget* Editor::owner() { return md->tw; }

void Editor::sceneOpen(string scenePath) throw(exception) {
    auto scene = readRefNodeFile(scenePath);
    if(!scene.valid()) throw exception("failed to open scene!");
    md->tw->worldScene->replaceChild(md->scene,scene);
    md->scene = scene->asGroup();
}

void Editor::sceneSave(string scenePath) throw(exception) {
    auto res = writeNodeFile(*md->scene,scenePath,new osgDB::Options("Compressor=zlib"));
    if(!res) throw exception("failed to save scene!");
}

void Editor::sceneExport(string scenePath) throw(exception) {
    auto mt = new MatrixTransform();
    mt->setMatrix(Matrix::rotate(DegreesToRadians(-90.0),Vec3(1,0,0)));
    mt->addChild(md->scene);
    auto res = writeNodeFile(*mt,scenePath,new osgDB::Options("Compressor=zlib"));
    if(!res) throw exception("failed to export scene!");
}

bool Editor::modelNameRepeat(string name) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    return nullptr != nv.outMt;
}

string Editor::modelName(unsigned long long seed) {
    string name;

    do {
        stringstream fmt;
        fmt << "model" << endl
            << hex << seed++ << endl
            << "Editor::Model";
        name = fmt.str();
    } while(modelNameRepeat(name));

    return name;
}

string Editor::modelAdd(string modelPath,unsigned int mask) throw(exception) {
    auto model = readRefNodeFile(modelPath);
    if(!model.valid()) throw exception("failed to add model because the file not read!");
    model->setName("");
    auto name = modelName(reinterpret_cast<unsigned long long>(&model));
    auto axisModel = new PositionAttitudeTransform;
    axisModel->addChild(model);
    //axisModel->setNodeMask(mask);

    auto mtModel = new PositionAttitudeTransform;
    mtModel->addChild(axisModel);
    mtModel->setName(name);
    mtModel->setNodeMask(mask);
    md->scene->addChild(mtModel);
    return name;
}

void Editor::modelRemove(string name,bool precise) throw(exception) {
    Finder nv; nv.precise=precise; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to remove model because the name not found!");
    md->scene->removeChild(nv.outMt);
}

string Editor::modelClone(string name) throw(exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to clone model because the name not found!");
    ref_ptr<Node> model = dynamic_cast<Node*>(nv.outMt->clone(CopyOp::DEEP_COPY_NODES));
    auto newName = modelName(reinterpret_cast<unsigned long long>(model.get()));
    model->setName(newName);
    md->scene->addChild(model);
    return newName;
}

void Editor::modelMask(string name,unsigned int mask) throw(exception) {
    Node* outMt = nullptr;
    for(unsigned int i=0;i < md->scene->getNumChildren();i++) {
        outMt = md->scene->getChild(i);
        if(name == outMt->getName()) break;
        outMt = nullptr;
    }

    if(nullptr == outMt) throw exception("failed to mask model because the name not found!");
    outMt->setNodeMask(mask);
}

unsigned int Editor::modelMask(string name) throw(exception) {
    Node* outMt = nullptr;
    for(unsigned int i=0;i < md->scene->getNumChildren();i++) {
        outMt = md->scene->getChild(i);
        if(name == outMt->getName()) break;
        outMt = nullptr;
    }

    if(nullptr == outMt) throw exception("failed to mask model because the name not found!");
    return outMt->getNodeMask();
}

void Editor::modelRename(string name,string newName) throw(exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to rename the model because the name not found!", 1);
    if(modelNameRepeat(newName)) throw exception("failed to rename the model because the name repeated!", 2);
    nv.outMt->setName(newName);
}

pair<vec3,float> Editor::modelBound(string name) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to bound the model because the name not found!", 1);
    auto b = nv.outMt->getBound();
    return { {b.center()[0],b.center()[1],b.center()[2]}, b.radius()};
}

void Editor::modelScale(string name,vec3 ratio) throw(exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to scale model because the name not found!");
    nv.outMt->setScale({ get<0>(ratio), get<1>(ratio), get<2>(ratio) });
}

vec3 Editor::modelScale(string name) throw(exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to scale model because the name not found!");
    auto ratio = nv.outMt->getScale();
    return { ratio[0], ratio[1], ratio[2] };
}

void Editor::modelAxis(string name,vec3 axis,double degrees) throw (exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to rotate the model because the name not found!");
    nv.outMt = dynamic_cast<PositionAttitudeTransform*>(nv.outMt->getChild(0));
    nv.outMt->setAttitude({ DegreesToRadians(degrees), Vec3(get<0>(axis), get<1>(axis), get<2>(axis)) });
}

void Editor::modelRotate(string name,vec3 axis,double degrees) throw (exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to rotate the model because the name not found!");
    nv.outMt->setAttitude({ DegreesToRadians(degrees), Vec3(get<0>(axis), get<1>(axis), get<2>(axis)) });
}

tuple<vec3,double> Editor::modelRotate(string name) throw (exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to rotate the model because the name not found!");
    auto q = nv.outMt->getAttitude();
    double angle;
    Vec3 axis;
    q.getRotate(angle,axis);
    return { { axis[0], axis[1], axis[2]} ,RadiansToDegrees(angle)};
}

void Editor::modelTrans(string name,vec3 pos) throw (exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to transform the model because the name not found`!");
    nv.outMt->setPosition({ get<0>(pos), get<1>(pos), get<2>(pos)} );
}

vec3 Editor::modelTrans(string name) throw (exception) {
    Finder nv; nv.inName = name; md->scene->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to transform the model because the name not found`!");
    auto pos = nv.outMt->getPosition();
    return {pos[0],pos[1],pos[2]};
}

tuple<string,vec3,vec3> Editor::intersect(vec2 xy, unsigned int mask) {
    LineSegmentIntersector::Intersections lis;
    if(!md->tw->viewer->computeIntersections(get<0>(xy),get<1>(xy),lis,mask)) return {"",{0,0,0},{0,0,0}};

    string name;
    Vec3 worldPoint,localPoint;
    for(auto li : lis) {
        auto np = li.nodePath;
        for(auto n : np) {
            if(string::npos == n->getName().find("\nEditor::Model")) continue;
            name = n->getName();
            break;
        }

        worldPoint = li.getWorldIntersectPoint();
        localPoint = li.getLocalIntersectPoint();
        if(!name.empty()) break;
    }

    return {
        name,
        {worldPoint[0],worldPoint[1],worldPoint[2]},
        {localPoint[0],localPoint[1],localPoint[2]}
    };
}

tuple<string,vec3,vec3> Editor::intersectWithVertex(vec2 xy, unsigned int mask) {
    LineSegmentIntersector::Intersections lis;
    if(!md->tw->viewer->computeIntersections(get<0>(xy),get<1>(xy),lis,mask)) return {"",{0,0,0},{0,0,0}};

    string name;
    Vec3 worldPoint,localPoint;
    LineSegmentIntersector::Intersection hit;

    for(auto li : lis) {
        auto np = li.nodePath;
        for(auto n : np) {
            if(string::npos == n->getName().find("\nEditor::Model")) continue;
            name = n->getName();
            break;
        }

        hit = li;
        worldPoint = li.getWorldIntersectPoint();
        localPoint = li.getLocalIntersectPoint();
        if(!name.empty()) break;
    }

    auto point = worldPoint;
    auto score = DBL_MAX;

    auto geometra = dynamic_cast<Geometry*>(hit.drawable.get());
    auto vertexs =  dynamic_cast<Vec3Array*>(geometra->getVertexArray());
    Vec3 vertexPicked;

    for(auto v : *vertexs) {
        for(auto wm : hit.drawable->getWorldMatrices()) {
            auto mv = (v * wm);
            auto sample = point - mv;
            auto difference = sample.normalize();

            if(difference < score) {
                score = difference;
                vertexPicked = mv;
            }
        }
    }

    return {name,{vertexPicked[0],vertexPicked[1],vertexPicked[2]},{0,0,0}};
}

set<string> Editor::planeIntersect(vec2 lt,vec2 rd,unsigned int mask) {
    set<string> names;

    auto picker = new PolytopeIntersector(Intersector::WINDOW,get<0>(lt),get<1>(rd),get<0>(rd),get<1>(lt));
    IntersectionVisitor iv(picker);
    iv.setTraversalMask(mask);

    auto camera = md->tw->viewer->getCamera();
    camera->accept(iv);

    if (picker->containsIntersections()) {
        auto lis = picker->getIntersections();
        for(auto li : lis) {
            NodePath np = li.nodePath;
            for(auto n : np) {
                auto name = n->getName();
                if(string::npos == name.find("\nEditor::Model")) continue;
                names.insert(name);
                break;
            }
        }
    }

    return names;
}

void* Editor::sceneRoot() {
    return md->scene.get();
}

void Editor::sceneRoot(void* scene) {
    md->tw->worldScene->replaceChild(md->scene,reinterpret_cast<Group*>(scene));
    md->scene = reinterpret_cast<Group*>(scene);
}

set<string> Editor::models() {
    set<string> names;
    for(int i=0;i < md->scene->getNumChildren();i++) names.insert(md->scene->getChild(i)->getName());
    return names;
}

string Editor::lineDraw(vec3 beginPos,vec3 endPos,int width) {
    ref_ptr<Geode> geode = new Geode();
    ref_ptr<Vec3Array> vetexs = new Vec3Array();
    ref_ptr<Geometry> geometry = new Geometry();

    vetexs->push_back(Vec3(get<0>(beginPos), get<1>(beginPos),get<2>(beginPos)));
    vetexs->push_back(Vec3(get<0>(endPos), get<1>(endPos), get<2>(endPos)));
    geometry->setVertexArray(vetexs);

    auto stateset = geode->getOrCreateStateSet();
    auto lineWidth = new LineWidth(4.0f);

    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    stateset->setAttribute(lineWidth);
    geometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, 2));

    auto colors = new Vec4Array;
    colors->push_back(Vec4(1.0f,0.0f,0.0f,0.5f)); // white
    colors->push_back(Vec4(1.0f,0.0f,0.0f,0.5f)); // white
    geometry->setColorArray(colors, osg::Array::BIND_PER_VERTEX);
    geode->addDrawable(geometry);

    auto axisModel = new PositionAttitudeTransform;
    axisModel->addChild(geode);

    auto mtModel = new PositionAttitudeTransform;
    mtModel->addChild(axisModel);
    auto c = mtModel->getBound().center();
    mtModel->setPivotPoint(c);
    mtModel->setPosition(c);

    stringstream fmt; fmt << "line" << endl
                          << hex << mtModel << endl
                          << "Editor::Model";

    mtModel->setName(fmt.str());
    md->scene->addChild(mtModel);
    return fmt.str();
}

string Editor::lineDraw(vec3 begin,vec3 end) {
    auto sd = new Geode;
    auto square = new osg::Geometry();

    auto v_square = new Vec3Array();
    v_square->push_back(Vec3(get<0>(begin),get<1>(begin),get<2>(begin)));
    v_square->push_back(Vec3(get<0>(end),get<1>(end),get<2>(end)));
    v_square->push_back(Vec3(get<0>(end),get<1>(end),get<2>(end) + 1000));
    v_square->push_back(Vec3(get<0>(begin),get<1>(begin),get<2>(begin) + 1000));

    square->setVertexArray(v_square);
    square->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS,0,4));

    auto colors = new Vec4Array;
    colors->push_back(Vec4(1.0f,0.0f,0.0f,1.0f)); // white
    colors->push_back(Vec4(1.0f,0.0f,0.0f,1.0f)); // white
    colors->push_back(Vec4(1.0f,0.0f,0.0f,1.0f)); // white
    colors->push_back(Vec4(1.0f,0.0f,0.0f,1.0f)); // white

    square->setColorArray(colors, Array::BIND_PER_VERTEX);

    auto blendFunc = new BlendFunc();
    blendFunc->setSource(BlendFunc::SRC_ALPHA);
    blendFunc->setDestination(BlendFunc::ONE_MINUS_CONSTANT_ALPHA);

    auto ss = sd->getOrCreateStateSet();
    ss->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    sd->addDrawable(square);

    auto axisModel = new PositionAttitudeTransform;
    axisModel->addChild(sd);

    auto mtModel = new PositionAttitudeTransform;
    mtModel->addChild(axisModel);
    auto c = mtModel->getBound().center();
    mtModel->setPivotPoint(c);
    mtModel->setPosition(c);

    stringstream fmt; fmt << "line" << endl
                          << hex << mtModel << endl
                          << "Editor::Model";

    mtModel->setName(fmt.str());
    md->scene->addChild(mtModel);
    return fmt.str();
}

}
