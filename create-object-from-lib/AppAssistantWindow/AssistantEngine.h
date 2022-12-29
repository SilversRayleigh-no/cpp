#ifndef ASSISTANTENGINE_H
#define ASSISTANTENGINE_H

#include <QObject>
#include "import_widget/MyWidgetInterface.h"
#include <widget_manager/WidgetManager.h>
#include <QQmlEngine>
#include <QQuickView>
#include "controller/InputEventController.h"
#include "controller/plugincard_interface.h"

class AssistantEngine : public QObject, public ICallbackInterface, public PluginCardInterface
{
    Q_OBJECT
public:
    explicit AssistantEngine(int _scrType = 4);
    static AssistantEngine* getInstance(int _scrType);

    // ICallbackInterface
    void callBackToApp() override {}
    QQmlContext* getRootContext() override;
    QQuickItem* getRootObject() override;

    // PluginCardInterface
    QQmlComponent* getPluginCard() override;
    bool initializePluginCard(QQuickView *rootView, QObject* parent) override;

    //
    void init_widget(int _scrType);
    WidgetManager* getWidget();

    QQmlEngine* getEngine();

public:
    void init_inputController();

private:
    WidgetManager* m_pWidget;
    static AssistantEngine* m_instance;

    QQuickView* m_pRootView;
    InputEventController* m_pInputEvtCtrl;
    QQmlComponent* m_pQmlComponent;
};

#endif // ASSISTANTENGINE_H
