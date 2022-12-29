#ifndef MYWIDGETINTERFACE_H
#define MYWIDGETINTERFACE_H
#include <QString>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlComponent>
class ICallbackInterface{
public:
    virtual void callBackToApp()          = 0;
    virtual QQuickItem* getRootObject()   = 0;
    virtual QQmlContext* getRootContext() = 0;
};

class MyWidgetInterface;
extern "C" Q_DECL_EXPORT MyWidgetInterface* getObject(int scrType = 0);

class MyWidgetInterface {
public:
    virtual void initialize(ICallbackInterface* cb) = 0;
    virtual QQmlComponent* getComponent()           = 0;
//    virtual QString getString()                     = 0;
//    virtual void setString(QString str = "")        = 0;
};

#endif // MYWIDGETINTERFACE_H
