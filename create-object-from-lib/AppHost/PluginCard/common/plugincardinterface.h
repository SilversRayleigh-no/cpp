#ifndef PLUGINCARDINTERFACE_H
#define PLUGINCARDINTERFACE_H

#include <QObject>
#include <QQuickView>
#include <QtCore/qglobal.h>

class PluginCardInterface{
public:
    virtual QQmlComponent* getPluginCard() = 0;
    virtual bool initializePluginCard(QQuickView *rootView, QObject* parent) = 0;
};

extern "C" Q_DECL_IMPORT PluginCardInterface* getAWObject(int scrType = 0);
#endif // PLUGINCARDINTERFACE_H
