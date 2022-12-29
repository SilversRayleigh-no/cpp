#ifndef WIDGETGLOBAL_IMPORT_H
#define WIDGETGLOBAL_IMPORT_H
#include <QtCore/qglobal.h>
#include "MyWidgetInterface.h"

#if defined(WIDGETPLUGIN_LIBRARY)
#   define WIDGETPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#   define WIDGETPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

//extern "C" WIDGETPLUGINSHARED_EXPORT MyWidgetInterface* getObject(int scrType = 0);
#endif // WIDGETGLOBAL_IMPORT_H
