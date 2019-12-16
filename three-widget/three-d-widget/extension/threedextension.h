#ifndef THRREDEXTENSION_H
#define THRREDEXTENSION_H

#include <QSettings>

class ThreeDExtension
{
    friend class ThreeDWidget;
public:
    static QSettings settings;

public:
    explicit ThreeDExtension(void* metadata =0);
    virtual ~ThreeDExtension();
protected:
    virtual void* getMetadata();
    void* metadata;
};

#endif // THRREDEXTENSION_H
