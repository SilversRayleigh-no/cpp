#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QObject>
#include "MyWidgetInterface.h"
#include <QDebug>
#include <QQmlEngine>
#include <QQuickView>
class MyWidget : public QObject, public MyWidgetInterface
{
    Q_OBJECT
public:
    static MyWidget* getInstance(int scrType);
public:
    explicit MyWidget(int scrType, QObject* parent = nullptr);
    void initialize(ICallbackInterface* cb) override;
    QQmlComponent* getComponent() override;

//    QString getString() override;
//    void setString(QString str) override;

private:
    static MyWidget* m_instance;

    QQuickItem* m_parent;
    QQmlComponent* m_qmlComponent;
    ICallbackInterface* m_callback;
//    QString m_str;
};

#endif // MYWIDGET_H
