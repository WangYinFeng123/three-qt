#ifndef PLACEEXTENSION_H
#define PLACEEXTENSION_H

#include "extension/threedextension.h"
#include <QString>

class PlaceExtension : public ThreeDExtension
{
public:
    PlaceExtension();
    virtual ~PlaceExtension();
    void placeByMouse(QString modelFilePath);
    QString place(QString modelFilePath,float x=0,float y=0,float z=0);
    void removeModel(QString modelID);
protected:
    virtual void* getMetadata();
};

#endif // PLACEHANDLER_H
