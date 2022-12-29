#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QObject>
#include "../import_widget/MyWidgetInterface.h"
#include "MyWidget.h"
class WidgetManager : public QObject
{
    Q_OBJECT
public:
    explicit WidgetManager(ICallbackInterface* cb, QObject* parent = nullptr);
    void installWidget(){
        WidgetPluginPtr plugin = m_listWidget.at(0);
        plugin->loadPlugin();
        plugin->initialize(m_cb);
    }

    void loadWidget(const QString& widgetFolder){
        WidgetPluginPtr plugin = WidgetPluginPtr(new WidgetPlugin(widgetFolder));
        m_listWidget.append(plugin);
    }

    Q_INVOKABLE QObject* getComponentWidget(){
        WidgetPluginPtr plugin = m_listWidget.at(0);
        QQmlComponent* com = plugin->getComponent();
        return com == nullptr ? nullptr : qobject_cast<QObject*>(com);
    }

//    void setDataForWidget(){
//        WidgetPluginPtr plugin = m_listWidget.at(0);
//        plugin->setString("le ngoc hai");
//    }

//    QString getDataForWidget(){
//        WidgetPluginPtr plugin = m_listWidget.at(0);
//        return plugin->getString();
//    }

private:
    ICallbackInterface* m_cb;
    QList<WidgetPluginPtr> m_listWidget;
};

#endif // WIDGETMANAGER_H
