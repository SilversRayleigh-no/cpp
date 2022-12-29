#-------------------------------------------------
#
# Project created by QtCreator 2022-12-20T09:55:12
#
#-------------------------------------------------

QT       += core quick
QT       -= gui
include(../common.pri)
TARGET = MyWidgetPlugin

WIDGET_NAME=MyWidgetPlugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        MyWidget.cpp \
#        main.cpp

HEADERS += \
    MyWidget.h \
    MyWidgetInterface.h

# Default rules for deployment.
unix:{
    qmlfiles.files += $$PWD/qml
    qmlfiles.path += /app/plugins/$$WIDGET_NAME

    target.path = /app/plugins/$$WIDGET_NAME
    INSTALLS += target qmlfiles
}
#!isEmpty(target.path): INSTALLS += target qmlfiles

