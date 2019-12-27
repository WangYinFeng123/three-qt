QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
           TW_LIBRARY

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    interfaces.cpp \
    main.cpp \
    mainwindow.cpp \
    pathconfigform.cpp \
    plugins/basic.cpp \
    plugins/board.cpp \
    plugins/controller.cpp \
    plugins/editor.cpp \
    plugins/observer.cpp \
    plugins/picker.cpp \
    plugins/placer.cpp \
    plugins/recorder.cpp \
    plugins/shadow.cpp \
    plugins/skybox.cpp \
    threewidget.cpp

HEADERS += \
    interfaces.h \
    mainwindow.h \
    pathconfigform.h \
    plugins/basic.h \
    plugins/board.h \
    plugins/controller.h \
    plugins/editor.h \
    plugins/observer.h \
    plugins/picker.h \
    plugins/placer.h \
    plugins/recorder.h \
    plugins/shadow.h \
    plugins/skybox.h \
    three-widget_global.h \
    threewidget.h

FORMS += \
    mainwindow.ui \
    pathconfigform.ui

INCLUDEPATH += \
            $$PWD/../OpenSceneGraph/include \
unix:!mac:  $$PWD/../OpenSceneGraph/build-gcc9-libc2.29/include \
win32:      $$PWD/../OpenSceneGraph/build-win-vs2017x64/include

unix:!mac:LIBS += -lxml2 -L$$PWD/../OpenSceneGraph/build-gcc9-libc2.29/lib -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText
win32:LIBS     += -L$$PWD/../OpenSceneGraph/build-win-vs2017x64/lib -lAdvapi32 -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgManipulator -losgAnimation -losgShadow -losgText

RESOURCES += \
    rc.qrc

RC_ICONS = app.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
