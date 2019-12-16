#ifndef ANIMATIONEXTENSION_H
#define ANIMATIONEXTENSION_H
#include "threedextension.h"
#include <QMap>
#include <QList>
#include <QString>

class AnimationExtension : public ThreeDExtension
{
public:
    AnimationExtension();
    virtual ~AnimationExtension();
    QList<QString> animations(QMap<QString,QString> details);
    void play(QMap<QString,QString> details,QString name);
    void stop(QMap<QString,QString> details,QString name);
    void stopAll(QMap<QString,QString> details);
    void update(QMap<QString,QString> details,QString name,double time);
protected:
    virtual void* getMetadata();
};

#endif // ANIMATIONEXTENSION_H
