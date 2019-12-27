#include "placer.h"

#include <iostream>
#include <bitset>
using namespace std;

namespace ThreeQt {

struct Placer::Plugin {
    Editor* ep;
    Controller* cp;
    string modelNamePlaced;
    function<void()> placedEventhandler;

    function<bool(vec2)> mouseOverHandler() {
        return [=](auto xy) {
            auto kv = ep->intersect(xy,0b11);
            try {
                ep->modelTrans(modelNamePlaced,get<1>(kv));
            } catch(...) {}
            return true;
        };
    }

    function<bool(Controller::MouseButton,Controller::MouseEventType,vec2,vec2)> mouseClickhandler() {
        return [=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
            if(met != Controller::Push) return false;
            switch(mb) {
            case Controller::Left:{
                auto newModelName = ep->modelClone(modelNamePlaced);
                ep->modelMask(newModelName,0b10);
                ep->modelMask(modelNamePlaced,0);
                placedEventhandler();
                ep->modelMask(modelNamePlaced,0b100);
                break;}
            }

            return true;
        };
    }
};

Placer::Placer(Editor* ep)
{
    md = new Plugin;
    md->ep = ep;
    md->cp = new Controller(ep->owner());

    md->cp->setMouseOverEventHandler(md->mouseOverHandler());
    md->cp->setMouseClickEventHandler(md->mouseClickhandler());
}

Placer::~Placer()
{
    try {
        md->ep->modelRemove(md->modelNamePlaced);
    } catch(...) {}

    md->cp->setMouseOverEventHandler(function<bool(vec2)>());
    md->cp->setMouseClickEventHandler(function<bool(Controller::MouseButton,Controller::MouseEventType,vec2,vec2)>());
    delete md;
}

void Placer::modelPlaced(string modelPath) {
    try {
        md->ep->modelRemove(md->modelNamePlaced);
    } catch (exception ex) {}

    md->modelNamePlaced = md->ep->modelAdd(modelPath,0b100);
    md->ep->modelAxis(md->modelNamePlaced,{1,0,0},90);
}

void Placer::modelPlacedByName(string name) {
    md->modelNamePlaced = md->ep->modelClone(name);
    md->ep->modelMask(md->modelNamePlaced,0b100);
}

void Placer::setPlacedEventHandler(decltype (Plugin::placedEventhandler) f) {
    md->placedEventhandler = f;
}

}
