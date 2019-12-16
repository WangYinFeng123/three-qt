#ifndef PICKEXTENSION_H
#define PICKEXTENSION_H
#include "extension/threedextension.h"

#include <functional>
using std::function;

#include <QMap>
#include <QString>

class PickExtension : public ThreeDExtension
{
public:
    PickExtension();
    virtual ~PickExtension();
    void setHoveredEvent(function<void(QMap<QString,QString>)> onHovered);
    void setPickedEvent(function<void(QMap<QString,QString>)> onPicked);
    void setCanceledEent(function<void()> onCanceled);
protected:
    virtual void* getMetadata();
};

#endif // PICKEXTENSION_H
