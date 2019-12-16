#ifndef THREEDPLUGIN_H
#define THREEDPLUGIN_H

#include "component3DInterface.h"
using NCI::NC3DPlayerWidget;

#include "extension/threedextension.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QtGlobal>
#include <QMap>
#include <QList>
#include <QString>

class ThreeDWidget : public NC3DPlayerWidget
{
    Q_OBJECT
public:
    bool configure(std::string& configInfo, bool isOnline );
    void setQueqryEnable(bool enable);

public Q_SLOTS:
    void updateModelStatus();
    void requestOid(QString,QString&,QString&);

public:
    ThreeDWidget(QWidget* parent=NULL);
    virtual ~ThreeDWidget();
    bool openScene(QString path,std::string fileName="",bool enableShadow=false);
    void lookingFor(QString name);
    void closeScene();
    void resetPosition();
    QList<QMap<QString,QString> > sceneDetails();
    void addExtension(ThreeDExtension&);
    void removeExtension(ThreeDExtension&);
    void watermark(bool enable);

public:
    virtual void resizeGL(int,int);
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void wheelEvent(QWheelEvent*);

private:
    void* metadata;
};

#endif // THREEDPLUGIN_H
