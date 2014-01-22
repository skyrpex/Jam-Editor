QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QxTimeLineEditor
TEMPLATE = app


SOURCES += main.cpp \
    MyView.cpp \
    QxTimeLineEditor.cpp \
    MimeData.cpp

HEADERS  += \
    MyView.hpp \
    Constants.hpp \
    QxTimeLineEditor.hpp \
    QxTimeLineEditor_p.hpp \
    MimeData.hpp

RESOURCES += \
    images.qrc
