#include "recorder.h"

#include <osg/Node>
using namespace osg;

#include <iostream>
#include <list>
using namespace std;

namespace ThreeQt {

struct Recorder::Plugin {
    Editor* ep;
    list<ref_ptr<Node>> ss;
};

Recorder::Recorder(Editor* ep) {
    md = new Plugin;
    md->ep = ep;
}

Recorder::~Recorder() {
    delete md;
}

void Recorder::snapshot() {
    cout << "snapshot" << endl;
    auto node = reinterpret_cast<Node*>(md->ep->sceneRoot())->clone(CopyOp::DEEP_COPY_NODES);
    ref_ptr<Node> scene = dynamic_cast<Node*>(node);
    md->ss.push_back(scene);

    if(md->ss.size() > 10) {
        md->ss.pop_front();
    }
}

void Recorder::restore() {
    if(md->ss.size() <= 1) {
        cout << "snapshots is empty!" << endl;
        return;
    }

    cout << "restore" << endl;
    md->ss.pop_back();
    auto scene = md->ss.back();
    md->ss.pop_back();
    md->ep->sceneRoot(scene.get());
    snapshot();
}


}
