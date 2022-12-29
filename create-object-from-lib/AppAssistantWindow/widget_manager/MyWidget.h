#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QObject>
#include <QString>
#include "../import_widget/MyWidgetInterface.h"
#include <QLibrary>
#include <QDebug>
#include <QSharedPointer>


typedef MyWidgetInterface* (*GetObjectFunction)(int);

class WidgetPlugin : public QObject, public MyWidgetInterface
{
    Q_OBJECT
public:
    explicit WidgetPlugin(QString pluginFolder);

    void initialize(ICallbackInterface* cb) override{
        m_callback = cb;
        if(m_widgetObj != nullptr)
            m_widgetObj->initialize(cb);
    }

    QQmlComponent* getComponent() override{
        if(m_widgetObj != nullptr){
            return m_widgetObj->getComponent();
        }
    }
//    QString getString() override;
//    void setString(QString str="") override;

    bool loadPlugin();

private:
    MyWidgetInterface* m_widgetObj;
    ICallbackInterface* m_callback;
    QLibrary m_lib;
};

typedef QSharedPointer<WidgetPlugin> WidgetPluginPtr;

#endif // MYWIDGET_H
