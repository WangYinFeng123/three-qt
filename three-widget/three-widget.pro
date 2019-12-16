#-------------------------------------------------
#
# Project created by QtCreator 2019-10-10T14:40:23
#
#-------------------------------------------------

QT       += core gui network opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = three-widget
TEMPLATE = lib
VERSION = 2.1.2
DEFINES += QT5
#DEFINES += QOPENGLWIDGET
#DEFINES += OSGEARTH

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
           GLOBAL_COMPANY=\\\"csnc\\\" \
           GLOBAL_NAME=\\\"config\\\" \
           GLOBAL_MODELDIRECTORYPATH=\\\"modelDirectoryPath\\\" \
           TW_LIBRARY

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    plugins/controls.cpp \
    plugins/observer.cpp \
    teleportmanipulator.cpp \
    threeearthwidget.cpp \
    threewidget.cpp \
    interfaces.cpp \
    plugins/basic.cpp \
    plugins/authorization.cpp \
    plugins/animations.cpp \
    plugins/shadow.cpp \
    threemanipulator.cpp

HEADERS += \
    plugins/controls.h \
    plugins/observer.h \
    teleportmanipulator.h \
    threeearthwidget.h \
    threewidget.h \
    interfaces.h \
    plugins/basic.h \
    plugins/authorization.h \
    plugins/animations.h \
    plugins/shadow.h \
    threemanipulator.h \
    three-widget_global.h

INCLUDEPATH += \
            $$PWD/../OpenSceneGraph/include\
#unix:!mac: $$PWD/../OpenSceneGraph/build-gcc4.4.5-libc2.11/include \
unix:!mac:  $$PWD/../OpenSceneGraph/build-gcc9-libc2.29/include \
win32:      $$PWD/../OpenSceneGraph/build-win-vs2013x64/include

#unix:!mac:LIBS += -lxml2 -L$$PWD/../OpenSceneGraph/build-gcc4.4.5-libc2.11/lib -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText
unix:!mac:LIBS += -lxml2 -L$$PWD/../OpenSceneGraph/build-gcc9-libc2.29/lib -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText
#unix:!mac:LIBS += -L$$PWD/../OpenSceneGraph-Earth/build-gcc9-libc2.29/lib -losgEarth -losgEarthUtil
win32:LIBS     += -L$$PWD/../OpenSceneGraph/build-win-vs2013x64/lib -lAdvapi32 -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JsonCpp/release/ -lJsonCpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JsonCpp/debug/ -lJsonCpp
else:unix:!macx: LIBS += -L$$PWD/../JsonCpp/ -lJsonCpp

INCLUDEPATH += $$PWD/../JsonCpp
DEPENDPATH += $$PWD/../JsonCpp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../JsonCpp/release/libJsonCpp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../JsonCpp/debug/libJsonCpp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../JsonCpp/release/JsonCpp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../JsonCpp/debug/JsonCpp.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../JsonCpp/libJsonCpp.a

# compatible
SOURCES += \
    three-d-widget/threedwidget.cpp \
    three-d-widget/node-visitors/modelnodevisitor.cpp \
    three-d-widget/manipulators/defaultmanipulator.cpp \
    three-d-widget/event-handlers/animationhandler.cpp \
    three-d-widget/extension/animationextension.cpp \
    three-d-widget/shaders/shadowmap.cpp \
    three-d-widget/component3DInterface.cpp \
    three-d-widget/form/relavancedialog.cpp \
    three-d-widget/extension/threedextension.cpp \

HEADERS += \
    three-d-widget/threedwidget.h \
    three-d-widget/node-visitors/modelnodevisitor.h\
    three-d-widget/manipulators/defaultmanipulator.h \
    three-d-widget/event-handlers/animationhandler.h \
    three-d-widget/extension/threedextension.h \
    three-d-widget/extension/animationextension.h \
    three-d-widget/shaders/shadowmap.h \
    three-d-widget/component3DInterface.h \
    three-d-widget/form/relavancedialog.h \

FORMS += \
    three-d-widget/form/relavancedialog.ui

INCLUDEPATH += $$PWD/three-d-widget
