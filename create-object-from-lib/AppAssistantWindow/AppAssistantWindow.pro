#-------------------------------------------------
#
# Project created by QtCreator 2022-12-20T13:07:59
#
#-------------------------------------------------

QT       += core gui quick

TARGET = AppAssistantWindow
TEMPLATE = lib

AW_NAME=AssistantWindow

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        AssistantEngine.cpp \
        controller/InputEventController.cpp \
#        main.cpp \
        widget_manager/MyWidget.cpp \
        widget_manager/WidgetManager.cpp

qmlfiles.files += $$PWD/qml
qmlfiles.path += /app/plugins/$$AW_NAME

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /app/plugins/$$AW_NAME
!isEmpty(target.path): INSTALLS += target qmlfiles

HEADERS += \
    AssistantEngine.h \
    controller/InputEventController.h \
    controller/plugincard_interface.h \
    import_widget/MyWidgetInterface.h \
    widget_manager/MyWidget.h \
    widget_manager/WidgetManager.h
