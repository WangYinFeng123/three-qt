#include "animationextension.h"
#include "event-handlers/animationhandler.h"

#include <osg/Node>
using osg::Node;
#include <osg/NodeVisitor>
using osg::NodeVisitor;
#include <osg/Geometry>
using osg::Geometry;
#include <QString>

struct Metadata {
    ref_ptr<AnimationHandler>* handler;
};

AnimationExtension::AnimationExtension() : ThreeDExtension(new Metadata)
#define md reinterpret_cast<Metadata*>(metadata)
{
    md->handler = new ref_ptr<AnimationHandler>(new AnimationHandler);
}

AnimationExtension::~AnimationExtension() {
    delete md->handler;
    delete md;
}

QList<QString> AnimationExtension::animations(QMap<QString,QString> details)
{
    long long modelID = details["id"].toLongLong();
    QString name = details["name"].toLower();
    Node* model = reinterpret_cast<Node*>(modelID);
    list<string> amNames = md->handler->get()->animations(model);
    QList<QString> amNamesJson;

    for(list<string>::iterator i=amNames.begin();amNames.end()!=i;i++) {
        string amName = *i;
        amNamesJson.push_back(QString::fromUtf8(amName.data()));
    }

    return amNamesJson;
}

void AnimationExtension::play(QMap<QString,QString> details,QString name) {
    long long modelID = details["id"].toLongLong();
    Node* model = reinterpret_cast<Node*>(modelID);

    md->handler->get()->play(model,name.toUtf8().data());
}

void AnimationExtension::stop(QMap<QString,QString> details,QString name) {
    long long modelID = details["id"].toLongLong();
    Node* model = reinterpret_cast<Node*>(modelID);
    md->handler->get()->stop(model,name.toUtf8().data());
}

void AnimationExtension::stopAll(QMap<QString,QString> details) {
    long long modelID = details["id"].toLongLong();
    Node* model = reinterpret_cast<Node*>(modelID);
    md->handler->get()->stopAll(model);
}

void AnimationExtension::update(QMap<QString,QString> details,QString name,double time) {
    long long modelID = details["id"].toLongLong();
    Node* model = reinterpret_cast<Node*>(modelID);
    md->handler->get()->update(model,name.toUtf8().data(),time);
}

void* AnimationExtension::getMetadata() {
    return NULL;
}
