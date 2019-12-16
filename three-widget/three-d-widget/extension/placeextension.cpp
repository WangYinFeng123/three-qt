#include "placeextension.h"
#include "event-handlers/placehandler.h"
#include <osg/Node>
using osg::Node;
#include <osgDB/ReadFile>
using osgDB::readNodeFile;
#include <osg/Matrix>
using osg::Matrix;

struct Metadata {
    ref_ptr<PlaceHandler>* handler;
};

PlaceExtension::PlaceExtension() : ThreeDExtension (new Metadata)
#define md reinterpret_cast<Metadata*>(metadata)
{
    md->handler = new ref_ptr<PlaceHandler>(new PlaceHandler);
}

PlaceExtension::~PlaceExtension() {
    delete md->handler;
    delete md;
}

void PlaceExtension::placeByMouse(QString modelFilePath) {
    md->handler->get()->placeByMouse(readNodeFile(modelFilePath.toLocal8Bit().data()));
}

QString PlaceExtension::place(QString modelFilePath,float x,float y,float z) {
    auto mt = new MatrixTransform();
    mt->setMatrix(Matrix::translate(x,y,z));
    mt->addChild(readNodeFile(modelFilePath.toLocal8Bit().data()));
    md->handler->get()->place(mt);

    return QString::number(reinterpret_cast<long long>(mt));
}

void PlaceExtension::removeModel(QString modelID) {
    md->handler->get()->remove(reinterpret_cast<Node*>(modelID.toInt()));
}

void* PlaceExtension::getMetadata() {
    return md->handler;
}
