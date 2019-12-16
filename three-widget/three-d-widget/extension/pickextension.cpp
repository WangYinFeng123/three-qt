#include "pickextension.h"
#include "event-handlers/pickhandler.h"

struct Metadata {
    ref_ptr<PickHandler>* pickHandler;
};

PickExtension::PickExtension() : ThreeDExtension(new Metadata)
#define md reinterpret_cast<Metadata*>(metadata)
{
    md->pickHandler = new ref_ptr<PickHandler>(new PickHandler());
}

void PickExtension::setHoveredEvent(function<void(QMap<QString,QString>)> onHovered) {
    md->pickHandler->get()->hoveredModel = [=](map<string,string> details) {
        QMap<QString,QString> args;
        for(auto i=details.begin();details.end() !=i;i++) {
            auto obj = *i;
            args.insert(QString::fromUtf8(obj.first.data()),QString::fromUtf8(obj.second.data()));
        }
        onHovered(args);
    };
}

void PickExtension::setPickedEvent(function<void(QMap<QString,QString>)> onPicked) {
    md->pickHandler->get()->pickedModel = [=](map<string,string> details) {
        QMap<QString,QString> args;
        for(auto i=details.begin();details.end() !=i;i++) {
            auto obj = *i;
            args.insert(QString::fromUtf8(obj.first.data()),QString::fromUtf8(obj.second.data()));
        }
        onPicked(args);
    };
}

void PickExtension::setCanceledEent(function<void()> onCanceled) {
    md->pickHandler->get()->canceled = onCanceled;
}

PickExtension::~PickExtension() {
    delete md->pickHandler;
    delete md;
}

void* PickExtension::getMetadata() {
    return md->pickHandler;
}
