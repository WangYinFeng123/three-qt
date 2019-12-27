#include "picker.h"
#include "threewidget.h"

#include <iostream>
#include <sstream>
#include <set>
#include <mutex>
using namespace std;

#include <osg/Geometry>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/BlendFunc>
#include <osg/AutoTransform>
#include <osg/PositionAttitudeTransform>
using namespace osg;

#include <osgText/Text>
using namespace osgText;

namespace ThreeQt {

struct Picker::Finder : public NodeVisitor {
    Finder() : NodeVisitor(TRAVERSE_ALL_CHILDREN),precise(true),outMt(nullptr) {}
    virtual void apply(PositionAttitudeTransform& node) {
        auto name = node.getName();

        if(precise) {
            if(name == inName) {
                if(outMt == nullptr) {
                    outMt = &node;
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
};

struct Picker::Plugin {
    Editor* ep;
    Controller* cp;
    Board* bop;
    Picker* pip;
    ref_ptr<Group> picks;
    function<void(set<string> name)> pickedEventHandler;
    function<void(pair<string,string> name,vec3 pos)> changedEventHandler;
    function<void()> changedFinishedEventHandler;

    //当前模式
    string currentMode;

    //移动模式
    bool boxToChoose;
    string namePointed;
    map<string,string> modelNamesPicked;
    vec2 leftTopNormalized,leftTop;

    //吸附模式
    bool absorbable,absorbing;
    vec3 beginPosAbsorbed;
    string modelNameAbsorbed,absorptionName;

    //Ctrl选择模式
    bool additional;

    function<void(bool,int)> keyboardHandler() {
        return [&](bool pressed,int key) {
            if(key == 0x53/*osgGA::GUIEventAdapter::KEY_S*/) {
                if(currentMode != "" && currentMode != "absorbable") return; //同一时间只允许一种模式
                cout << "absorption mode:" << pressed << endl;
                if(pressed) {
                    currentMode = "absorbable";
                } else {
                    pip->modelRemove(absorptionName);
                    currentMode = "";
                }

                absorbable = pressed;
                cp->setMouseOverEventHandler(pressed ? mouseOverHandler() : function<void(vec2 xy)>());
            }

            if(key == 0x1000021/*osgGA::GUIEventAdapter::KEY_Control_L*/) {
                if(currentMode != "" && currentMode != "additional") return; //同一时间只允许一种模式
                cout << "additional mode:" << pressed << endl;
                if(pressed) {
                    currentMode = "additional";
                } else {
                    currentMode = "";
                }

                additional = pressed;
            }
        };
    }

    function<void(vec2 xy)> mouseOverHandler() {
        return [&](vec2 xy) {
            pip->modelRemove(absorptionName);
            absorptionName = "";

            auto it = ep->intersectWithVertex(xy,0b10);

            if(!modelNamesPicked.empty() && modelNamesPicked.end() == find_if(modelNamesPicked.begin(),modelNamesPicked.end(),[&](const pair<string,string>& kv) {
                return kv.first == get<0>(it);
            })) return;

            beginPosAbsorbed = get<1>(it);
            modelNameAbsorbed = get<0>(it);
            absorptionName = pip->markDraw(beginPosAbsorbed);
        };
    };

    function<bool(Controller::MouseButton,Controller::MouseEventType,vec2,vec2)> mouseClickHandler() {
        return [=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
            if(mb == Controller::Left && met == Controller::Push) {
                auto kv = ep->intersect(xy,0b10);
                namePointed = get<0>(kv);
                boxToChoose = namePointed.empty();

                if(boxToChoose) {   //鼠标不在物体上
                    leftTopNormalized = xyNormalized;
                    leftTop = xy;
                } else if(!namePointed.empty()) { //鼠标在物体上
                    if(modelNamesPicked.end() == modelNamesPicked.find(namePointed)) {   //没有在选中的物体上
                        if(!additional) pip->clear();           //不是附加模式，则取消之前选择的物体
                        auto pos = ep->modelTrans(namePointed);
                        auto r = ep->modelRotate(namePointed);
                        auto s = ep->modelScale(namePointed);
                        auto radius = ep->modelBound(namePointed).second;
                        auto pickName = namePointed;
                        pickName.erase(pickName.find("\nEditor::Model"), string::npos);
                        pickName = pickName + "\nPicker::Model";
                        pip->pickDraw(pickName,pos,radius);
                        pip->modelRotate(pickName,get<0>(r),get<1>(r));
                        pip->modelScale(pickName,s);

                        modelNamesPicked.insert({namePointed,pickName}); //选中当前物体

                        //发送选择事件
                        set<string> names;
                        for(auto kv : modelNamesPicked) names.insert(kv.first);
                        if(pickedEventHandler) pickedEventHandler(names);

                        absorbing = absorbable;
                    }
                    else { //有在选中的物体上
                        absorbing = absorbable; //判断是否吸附

                        if(additional) { //如果是附加选择模式，则取消选择
                            pip->modelRemove(modelNamesPicked[namePointed]);
                            modelNamesPicked.erase(namePointed);
                        }
                    }
                }

                for(auto kv : modelNamesPicked) ep->modelMask(kv.first,0b100); //禁止物体进行交运算
            }
            else if(mb == Controller::Left && met == Controller::Drag) {
                if(boxToChoose) { //画框框
                    bop->clear();
                    bop->planeDraw(leftTopNormalized,xyNormalized);
                } else { //移动已选择的物体
                    if(additional) {
                    } else {
                        if(absorbing) {
                            auto kv = ep->intersectWithVertex(xy,0b10);
                            auto end = get<1>(kv);
                            if(get<0>(kv).empty()) end = get<1>(ep->intersect(xy,0b01));
                            auto begin = beginPosAbsorbed;
                            vec3 offset {get<0>(end) - get<0>(begin),get<1>(end) - get<1>(begin), get<2>(end) - get<2>(begin)};

                            for(auto kv : modelNamesPicked) {
                                auto modelPos = ep->modelTrans(kv.first);
                                modelPos = {
                                    get<0>(modelPos) + get<0>(offset),
                                    get<1>(modelPos) + get<1>(offset),
                                    get<2>(modelPos) + get<2>(offset)
                                };

                                //ep->modelTrans(kv.first,modelPos);
                                //pip->modelTrans(kv.second,modelPos);
                                if(changedEventHandler) changedEventHandler({kv.first,kv.second},modelPos);
                            }

                            beginPosAbsorbed = end;
                        } else {
                            auto begin = ep->modelTrans(namePointed);
                            auto end = get<1>(ep->intersect(xy,0b11));
                            vec3 offset {get<0>(end) - get<0>(begin),get<1>(end) - get<1>(begin), get<2>(end) - get<2>(begin)};

                            for(auto kv : modelNamesPicked) {
                                auto modelPos = ep->modelTrans(kv.first);
                                modelPos = {
                                    get<0>(modelPos) + get<0>(offset),
                                    get<1>(modelPos) + get<1>(offset),
                                    get<2>(modelPos) + get<2>(offset)
                                };

                                //ep->modelTrans(kv.first,modelPos);
                                //pip->modelTrans(kv.second,modelPos);
                                if(changedEventHandler) changedEventHandler({kv.first,kv.second},modelPos);
                            }
                        }
                    }

                    //发送选择事件
                    set<string> names;
                    for(auto kv : modelNamesPicked) names.insert(kv.first);
                }
            }
            else if(met == Controller::Release) {
                for(auto kv : modelNamesPicked) ep->modelMask(kv.first,0b10); //允许物体进行交运算

                if(mb == Controller::Left && boxToChoose) { //选择物体
                    if(absorbing) {  //吸附时
                        absorbing = false;
                    } else {
                        bop->clear();
                        if(!additional) pip->clear();           //不是附加模式，则取消之前选择的物体

                        if(get<0>(leftTop) > get<0>(xy)) swap(get<0>(leftTop),get<0>(xy));
                        if(get<1>(leftTop) < get<1>(xy)) swap(get<1>(leftTop),get<1>(xy));
                        if(get<0>(leftTopNormalized) > get<0>(xyNormalized)) swap(get<0>(leftTopNormalized),get<0>(xyNormalized));
                        if(get<1>(leftTopNormalized) < get<1>(xyNormalized)) swap(get<1>(leftTopNormalized),get<1>(xyNormalized));

                        auto modelNamesIntersected = ep->planeIntersect(leftTop,xy,0b10);
                        for(auto namePointed : modelNamesIntersected) {
                            if(modelNamesPicked.end() != modelNamesPicked.find(namePointed)) {
                                pip->modelRemove(modelNamesPicked[namePointed]); //取消选择
                                modelNamesPicked.erase(namePointed);
                                continue;
                            }

                            cout << namePointed << endl;
                            auto pos = ep->modelTrans(namePointed);
                            auto r = ep->modelRotate(namePointed);
                            auto s = ep->modelScale(namePointed);
                            auto radius = ep->modelBound(namePointed).second;
                            auto pickName = namePointed;
                            pickName.erase(pickName.find("\nEditor::Model"), string::npos);
                            pickName = pickName + "\nPicker::Model";
                            pip->pickDraw(pickName,pos,radius);
                            pip->modelRotate(pickName,get<0>(r),get<1>(r));
                            pip->modelScale(pickName,s);
                            modelNamesPicked.insert({namePointed,pickName}); //选中当前物体
                        }

                        //发送选择事件
                        set<string> names;
                        for(auto kv : modelNamesPicked) names.insert(kv.first);
                        if(pickedEventHandler) pickedEventHandler(names);
                    }
                } else {
                    if(changedFinishedEventHandler) changedFinishedEventHandler();
                    absorbing = false;
                }
            }

            return false;
        };
    }
};

Picker::Picker(Editor* ep)
{
    md = new Plugin;
    md->ep = ep;
    md->cp = new Controller(ep->owner());
    md->bop = new Board(ep->owner());
    md->pip = this;
    md->picks = new Group();
    md->additional = md->absorbable = md->absorbing = false;

    ep->owner()->worldScene->addChild(md->picks);

    md->cp->setKeyboardEventhandler(md->keyboardHandler());
    md->cp->setMouseClickEventHandler(md->mouseClickHandler());
}

Picker::~Picker()
{
    for(auto kv : md->modelNamesPicked) md->ep->modelMask(kv.first,0b10); //允许物体进行交运算
    md->ep->owner()->worldScene->removeChild(md->picks);
    delete md->cp;
    delete md->bop;
    delete md;
}

string Picker::markDraw(vec3 xyz) {
    auto ps = new DrawElementsUInt(PrimitiveSet::LINES);
    ps->push_back(0);
    ps->push_back(1);
    ps->push_back(2);
    ps->push_back(3);

    auto v = new Vec3Array();
    v->push_back(Vec3(-8,8,0));
    v->push_back(Vec3(8,-8,0));
    v->push_back(Vec3(8,8,0));
    v->push_back(Vec3(-8,-8,0));

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
    ss->setMode(GL_LIGHTING, StateAttribute::OFF);
    geode->addDrawable(geom);

    auto mt = new MatrixTransform();
    mt->setMatrix(Matrix::translate(Vec3d{get<0>(xyz),get<1>(xyz),get<2>(xyz)}));

    auto ar = new AutoTransform;
    ar->setAutoRotateMode(AutoTransform::ROTATE_TO_SCREEN);
    ar->setAutoScaleToScreen(true);
    ar->addChild(geode);
    mt->addChild(ar);

    stringstream fmt; fmt << "pick" << endl
                          << hex << mt << endl
                          << "Picker::Model";

    mt->setName(fmt.str());
    md->picks->addChild(mt);
    return fmt.str();
}

map<string,string> Picker::picks() {
    return md->modelNamesPicked;
}

void Picker::setPickedEventHandler(function<void(set<string> name)> f) {
    md->pickedEventHandler = f;
}

void Picker::setChangedEventHandler(function<void(pair<string,string> name,vec3 pos)> f) {
    md->changedEventHandler = f;
}

void Picker::setChangedFinishedEventHandler(function<void()> f) {
    md->changedFinishedEventHandler = f;
}

void Picker::modelTrans(string name,vec3 pos) {
    Finder nv; nv.inName = name; md->picks->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to transform the model because the name not found`!");
    nv.outMt->setPosition({ get<0>(pos), get<1>(pos), get<2>(pos)} );
}

void Picker::modelScale(string name,vec3 ratio) throw(exception) {}

void Picker::modelAxis(string name,vec3 axis,double degrees) throw (exception) {
    Finder nv; nv.inName = name; md->picks->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to rotate the model because the name not found!");
    nv.outMt = dynamic_cast<PositionAttitudeTransform*>(nv.outMt->getChild(0));
    nv.outMt->setAttitude({ DegreesToRadians(degrees), Vec3(get<0>(axis), get<1>(axis), get<2>(axis)) });
}

void Picker::modelRotate(string name,vec3 axis,double degrees) throw (exception) {
    Finder nv; nv.inName = name; md->picks->accept(nv);
    if(nullptr == nv.outMt) throw exception("failed to rotate the model because the name not found!");
    nv.outMt->setAttitude({ DegreesToRadians(degrees), Vec3(get<0>(axis), get<1>(axis), get<2>(axis)) });
}

void Picker::clear() {
    md->picks->removeChild(0,md->picks->getNumChildren());
    md->modelNamesPicked.clear();
}

void Picker::modelRemove(string name) throw(exception) {
    for(int i=0;i < md->picks->getNumChildren();i++) {
        if(name == md->picks->getChild(i)->getName()) {
            md->picks->removeChild(i);
            break;
        }
    }
}

void Picker::pickDraw(string name,vec3 pos, float r) {
    auto geom = new Geometry();
    Vec3 center(0,0,0);
    Vec3 x(r,0,0);
    Vec3 y(0,r,0);
    Vec3 z(0,0,r);
    auto fontSize = r / 3;

    auto v = new Vec3Array();
    auto c = new Vec4Array();
    auto i = 0;

    v->push_back(center);
    v->push_back(x);
    c->push_back(Vec4(1.0f,0.0f, 0.0f, 0.8f));
    c->push_back(Vec4(1.0f,0.0f, 0.0f, 0.8f));
    geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, i, 2));
    i+=2;

    v->push_back(center);
    v->push_back(y);
    c->push_back(Vec4(0.0f,1.0f, 0.0f, 0.8f));
    c->push_back(Vec4(0.0f,1.0f, 0.0f, 0.8f));
    geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, i, 2));
    i+=2;

    v->push_back(center);
    v->push_back(z);
    c->push_back(osg::Vec4(0.0f,0.0f, 1.0f, 0.8f));
    c->push_back(osg::Vec4(0.0f,0.0f, 1.0f, 0.8f));
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, i, 2));
    i+=2;

    geom->setVertexArray(v);
    geom->setColorArray(c);
    geom->setColorBinding(Geometry::BIND_PER_VERTEX);

    auto xAxis = new Text;
    xAxis->setText("X");
    xAxis->setColor(Vec4(1,0,0,.8));
    xAxis->setAxisAlignment(Text::SCREEN);
    xAxis->setCharacterSize(fontSize);
    xAxis->setPosition(x);

    auto yAxis = new Text;
    yAxis->setText("Y");
    yAxis->setColor(Vec4(0,1,0,.8));
    yAxis->setAxisAlignment(Text::SCREEN);
    yAxis->setCharacterSize(fontSize);
    yAxis->setPosition(y);

    auto zAxis = new Text;
    zAxis->setText("Z");
    zAxis->setColor(Vec4(0,0,1,.8));
    zAxis->setAxisAlignment(Text::SCREEN);
    zAxis->setCharacterSize(fontSize);
    zAxis->setPosition(z);

    auto geode = new Geode();
    geode->addDrawable(geom);
    geode->addDrawable(xAxis);
    geode->addDrawable(yAxis);
    geode->addDrawable(zAxis);

    auto ss = geode->getOrCreateStateSet();
    ss->setMode(GL_DEPTH_TEST,StateAttribute::OFF);
    ss->setMode(GL_LIGHTING, StateAttribute::OFF);
    ss->setAttribute(new LineWidth(0.5f), StateAttribute::ON);

    auto axisModel = new PositionAttitudeTransform;
    axisModel->addChild(geode);

    auto mt = new PositionAttitudeTransform;
    mt->addChild(axisModel);
    mt->setPosition({get<0>(pos),get<1>(pos),get<2>(pos)});
    mt->setNodeMask(0x0b1000);
    mt->setName(name);
    md->picks->addChild(mt);
}

}
