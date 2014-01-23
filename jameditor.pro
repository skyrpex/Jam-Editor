#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T19:16:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jameditor
TEMPLATE = app
CONFIG += C++11

SOURCES += main.cpp\
        mainwindow.cpp \
    qxtimelineeditor/MimeData.cpp \
    qxtimelineeditor/MyView.cpp \
    qxtimelineeditor/QxTimeLineEditor.cpp \
    timelineeditor.cpp \
    timelinewidget.cpp \
    animation.cpp \
    importer.cpp \
    keyframe.cpp \
    canvas.cpp \
    hitbox.cpp \
    keyframeitem.cpp

HEADERS  += mainwindow.h \
    qxtimelineeditor/Constants.hpp \
    qxtimelineeditor/MimeData.hpp \
    qxtimelineeditor/MyView.hpp \
    qxtimelineeditor/QxTimeLineEditor.hpp \
    qxtimelineeditor/QxTimeLineEditor_p.hpp \
    timelineeditor.h \
    timelinewidget.h \
    animation.h \
    importer.h \
    keyframe.h \
    canvas.h \
    hitbox.h \
    keyframeitem.h

FORMS    += mainwindow.ui \
    timelinewidget.ui \
    importer.ui \
    canvas.ui

include(qxmesh/QxMesh.pri)

RESOURCES += \
    qxtimelineeditor/images.qrc
