#ifndef PLUGINCARD_INTERFACE_H
#define PLUGINCARD_INTERFACE_H

#include <QObject>
#include <QQuickView>
#include <QtCore/qglobal.h>

class PluginCardInterface{
public:
    virtual QQmlComponent* getPluginCard() = 0;
    virtual bool initializePluginCard(QQuickView *rootView, QObject* parent) = 0;
};

extern "C" Q_DECL_EXPORT PluginCardInterface* getAWObject(int scrType = 0);

#endif // PLUGINCARD_INTERFACE_H
