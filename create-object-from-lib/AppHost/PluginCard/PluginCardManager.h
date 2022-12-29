#ifndef PLUGINCARDMANAGER_H
#define PLUGINCARDMANAGER_H

#include <QObject>
#include <QQuickView>
#include <QLibrary>
#include <QQmlComponent>
#include "PluginCard/common/plugincardinterface.h"
#include <QDebug>

class PluginCardManager : public QObject
{
public:
    explicit PluginCardManager(QQuickView* rootview, QObject* parent = nullptr);

    QQmlComponent* getPluginCard(void);

private:
    PluginCardInterface    *m_pPluginCardIface;
    QLibrary               m_lib;
    QQmlComponent          *m_QQmlComponent;

    bool initializePluginCard(QQuickView *rootview, QObject *parent);
    bool load();
};

typedef PluginCardInterface* (*CARDiface)(int);

#endif // PLUGINCARDMANAGER_H
