QT       += core gui opengl xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = three-earth-test
TEMPLATE = app
DEFINES += QT5
#DEFINES += QOPENGLWIDGET
DEFINES += OSGEARTH

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
           GLOBAL_COMPANY=\\\"csnc\\\" \
           GLOBAL_NAME=\\\"config\\\" \
           GLOBAL_MODELDIRECTORYPATH=\\\"modelDirectoryPath\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
            $$PWD/../OpenSceneGraph/include\
#unix:!mac: $$PWD/../OpenSceneGraph/build-gcc4.4.5-libc2.11/include\
unix:!mac:  $$PWD/../OpenSceneGraph/build-gcc9-libc2.29/include\
win32:      $$PWD/../OpenSceneGraph/build-win-vs2013x64/include

#unix:!mac:LIBS += -lxml2 -L$$PWD/../OpenSceneGraph/build-gcc4.4.5-libc2.11/lib -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText -losgEarth -losgEarthUtil
unix:!mac:LIBS += -lxml2 -L$$PWD/../OpenSceneGraph/build-gcc9-libc2.29/lib -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText
unix:!mac:LIBS += -L$$PWD/../OpenSceneGraph-Earth/build-gcc9-libc2.29/lib -losgEarth -losgEarthUtil
win32:LIBS     += -L$$PWD/../OpenSceneGraph/build-win-vs2013x64/lib -lAdvapi32 -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText -losgEarth -losgEarthUtil

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../three-widget/release -lthree-widget2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../three-widget/debug -lthree-widget2
else:unix:!macx: LIBS += -L$$PWD/../three-widget -lthree-widget

INCLUDEPATH += $$PWD/../three-widget
DEPENDPATH += $$PWD/../three-widget

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
