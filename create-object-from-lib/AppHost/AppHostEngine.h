#ifndef APPHOSTENGINE_H
#define APPHOSTENGINE_H

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QQuickView>
#include "PluginCard/PluginCardManager.h"
#include <QQmlContext>

class AppHostEngine : public QObject
{
    Q_OBJECT
public:
    explicit AppHostEngine(QGuiApplication* parent = nullptr);
    static AppHostEngine* getInstance(QGuiApplication* app);

    void init();

    void initViewer();
    int exec();

private:
    static AppHostEngine* m_instance;

    QGuiApplication* mApp;
    QQuickView* mRootView;
    PluginCardManager* mPluginCardManager;
};

#endif // APPHOSTENGINE_H
